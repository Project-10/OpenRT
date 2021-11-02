#include "ShaderChrome.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderChrome::shade(const Ray& ray) const 
	{
		Vec3f res = Vec3f::all(0);

		Vec3f normal = ray.hit->getShadingNormal(ray);									// shading normal

		size_t nSamples = m_pSampler ? m_pSampler->getNumSamples() : 1;
		size_t k = 0;
		for (size_t s = 0; s < nSamples; s++) {

			Vec3f n = normal;
			if (m_pSampler) {
				n = CSampler::transformSampleToWCS(CSampler::uniformSampleHemisphere(m_pSampler->getNextSample(), 25), n);
			}

			Ray reflected = ray.reflected(n);
			if (reflected.dir.dot(normal) < -0.001f) 
				continue;

			res += reflected.reTrace(m_scene);
			k++;
		}
		if (k != 0)
			res = (1.0f / k) * res;
		
		const float q = 0.8f;
		res = q * res + (1 - q) * getColor(ray);
		
		return res;
	}
}
