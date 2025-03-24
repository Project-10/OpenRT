#include "ShaderChrome.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderChrome::shade(const Ray& ray) const 
	{
		Vec3f res = Vec3f::all(0);

		Vec3f normal = ray.hit->getShadingNormal(ray);									// shading normal

		size_t nSamples = getSampler() ? getSampler()->getNumSamples() : 1;
		size_t k = 0;
		for (size_t s = 0; s < nSamples; s++) {
			Vec3f n = normal;
			if (getSampler()) {
				Vec2f sample = getSampler()->getNextSample();
				Vec3f hemisphereSample = CSampler::uniformSampleHemisphere(sample, 25);
				n = CSampler::transformSampleToWCS(hemisphereSample, n);
			}

			Ray reflected = ray.reflected(n);
			if (reflected.dir.dot(normal) < -0.001f) 
				continue;

			res += reflected.reTrace(getScene());
			k++;
		}
		if (k != 0)
			res = (1.0f / k) * res;
		
		const float q = 0.8f;
		res = q * res + (1 - q) * getDiffuseColor(ray);
		
		return res;
	}
}
