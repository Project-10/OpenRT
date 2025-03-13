#include "ShaderDiffuse.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderDiffuse::shade(const Ray& ray) const
	{
		Vec3f res(0, 0, 0);

		Vec3f diffuseColor = getDiffuseColor(ray);
		float opacity = getOpacity(ray);

		Vec3f faceNormal = ray.hit->getNormal(ray);							// face normal
		Vec3f shadingNormal = ray.hit->getShadingNormal(ray);				// shading normal


		auto du = getBump(ray);
		if (du) {
			auto  dp = ray.hit->dp(ray.hitPoint());
			Vec3f dpdu = dp.first;
			Vec3f dpdv = dp.second;

			shadingNormal += getBumpAmount() * (du.value().first * dpdv.cross(shadingNormal) - du.value().second * dpdu.cross(shadingNormal));
			shadingNormal = normalize(shadingNormal);
		}

		bool inside = false;
		if (faceNormal.dot(ray.dir) > 0) {
			shadingNormal = -shadingNormal;								// turn shading normal to front
			inside = true;
		}

#ifdef DEBUG_MODE
		res = inside ? RGB(255, 0, 0) : RGB(0, 0, 255);
#endif
		// ------ opacity ------
		if (opacity < 1) {
			Ray R(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
			res += (1.0f - opacity) * R.reTrace(m_scene);
		}

		// ------ diffuse ------
		Ray shadowRay(ray.hitPoint(shadingNormal));						// shadow ray

		for (auto& pLight : m_scene.getLights()) {
			Vec3f L = Vec3f::all(0);
			const size_t nSamples = pLight->getNumSamples();
			for (size_t s = 0; s < nSamples; s++) {

				// get direction to light, and intensity
				shadowRay.hit = ray.hit;	// Needed for the skylight
				auto radiance = pLight->illuminate(shadowRay);
				if (radiance) {
					// Check shadow (light sourse is occluded)
					float k_occlusion = pLight->shadow() ? m_scene.evalOcclusion(shadowRay) : 1.0f;
					if (k_occlusion < Epsilon) continue;

					// ------ diffuse ------
					float cosLightNormal = shadowRay.dir.dot(shadingNormal);
					if (cosLightNormal > 0)
						L += opacity * cosLightNormal * k_occlusion * diffuseColor.mul(radiance.value());
				}
			} // s
			res += (1.0f / nSamples) * L;
		} // pLight

		return res;
	}
}
