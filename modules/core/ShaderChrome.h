#pragma once

#include "IShader.h"
#include "Sampler.h"

namespace rt {
	//namespace {
		std::pair<Vec3f, Vec3f> getRandomTangents(Vec3f normal)
		{
			std::pair<Vec3f, Vec3f> res;
			float s1 = random::U<float>();
			float s2 = random::U<float>();
			
			if (fabs(normal.val[0]) > 0.1f)
				res.first = Vec3f(-(s1 * normal.val[1] + s2 * normal.val[2]) / normal.val[0], s1, s2);
			else if (fabs(normal.val[1]) > 0.1f)
				res.first = Vec3f(s1, -(s1 * normal.val[0] + s2 * normal.val[2] / normal.val[1]), s2);
			else
				res.first = Vec3f(s1, s2, -(s1 * normal.val[0] + s2 * normal.val[1]) / normal.val[2]);
			
			res.second = normal.cross(res.first);
			res.first  = normalize(res.first);
			res.second = normalize(res.second);
			return res;
		}
	//}

	class CShaderChrome : public IShader
	{
	public:
		DllExport CShaderChrome(CScene& scene, std::shared_ptr<CSampler> pSampler = nullptr)
			: m_scene(scene)
			, m_pSampler(pSampler)
		{}
		DllExport virtual ~CShaderChrome(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override
		{		
			Vec3f res = Vec3f::all(0);
			
			Vec3f normal = ray.hit->getNormal(ray);						// shading normal
			if (normal.dot(ray.dir) > 0) normal = -normal;						// turn normal to front
			const auto tangents = getRandomTangents(normal);					// two random tangent vectors
			
			size_t nSamples = m_pSampler ? m_pSampler->getNumSamples() : 1;
			for (size_t s = 0; s < nSamples; s++) {
				
				Vec3f n = normal;
				if (m_pSampler) {
					Vec2f sample = m_pSampler->getNextSample();
					Vec3f disp = sample.val[0] * tangents.first + sample.val[1] * tangents.second;
					n = normalize(n + disp);
				}
					
				Ray I = ray.reflected(n);	// reflection vector
				//I.counter = std::max(maxRayCounter - 1, I.counter);
				res += I.counter >= maxRayCounter ? Vec3f::all(0.4f) : m_scene.rayTrace(I);
			}
			res = (1.0f / nSamples) * res;
			return res;

		}
		

		
		
	private:
		CScene& 					m_scene;
		std::shared_ptr<CSampler>	m_pSampler;
	};
}



