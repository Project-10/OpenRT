#include "ShaderScene.h"
#include "Scene.h"
#include "Ray.h"
#include "random.h"


Vec3f rt::CShaderScene::eval_IR_LS(const Ray& ray) const {
	Vec3f res(0, 0, 0);

	Vec3f n = ray.hit->getShadingNormal(ray);				// shading normal

	Ray shadowRay(ray.hitPoint(n));
	for (auto& pLight : m_scene.getLights()) {
		Vec3f L = Vec3f::all(0);
		const size_t nSamples = pLight->getNumSamples();
		for (size_t s = 0; s < nSamples; s++) {
			shadowRay.hit = ray.hit;	// Needed for the skylight
			auto radiance = pLight->illuminate(shadowRay);
			if (radiance) {
				// Check shadow (light sourse is occluded)
				float k_occlusion = pLight->shadow() ? m_scene.evalOcclusion(shadowRay) : 1.0f;
				if (k_occlusion < Epsilon) continue;

				float cosLightNormal = shadowRay.dir.dot(n);
				if (cosLightNormal > 0)
					L += cosLightNormal * k_occlusion * radiance.value();
			}
		}
		res += (1.0f / nSamples) * L;
	}
	return res;
}

Vec3f rt::CShaderScene::eval_IR_all(const Ray& ray) const {
	Vec3f res(0, 0, 0);

	Vec3f n = ray.hit->getShadingNormal(ray);				// shading normal

	const size_t nSamples = m_pSampler ? m_pSampler->getNumSamples() : 1;
	for (size_t s = 0; s < nSamples; s++) {
		Vec2f sample = m_pSampler ? m_pSampler->getNextSample() : Vec2f(random::U<float>(), random::U<float>());
		Vec3f hemisphereSample = CSampler::cosineSampleHemisphere(sample);
		//Vec3f hemisphereSample = CSampler::uniformSampleHemisphere(sample);
		Vec3f dir = CSampler::transformSampleToWCS(hemisphereSample, n);	// sample the hemisphere in respect to the object's normal

		Ray r(ray.hitPoint(n), dir, ray.ndc, ray.counter);
		res += r.reTrace(m_scene);
	}
	res *= Pif / nSamples;

	return res;
}

