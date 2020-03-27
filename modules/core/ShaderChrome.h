#pragma once

#include "IShader.h"
#include "Sampler3f.h"

namespace rt {
	class CShaderChrome : public IShader
	{
	public:
		DllExport CShaderChrome(CScene& scene, std::shared_ptr<CSampler3f> dSampler = nullptr)
			: m_scene(scene)
			, m_dSampler(dSampler)
		{}
		DllExport virtual ~CShaderChrome(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override
		{		
			Vec3f res = Vec3f::all(0);
			
			Vec3f normal = ray.hit->getNormal(ray);								// shading normal
			if (normal.dot(ray.dir) > 0) normal = -normal;						// turn normal to front
			
			size_t nSamples = m_dSampler ? m_dSampler->getNumSamples() : 1;
			for (size_t s = 0; s < nSamples; s++) {
				
				Vec3f n = normal;
				if (m_dSampler) {
					n = m_dSampler->getNextSample(n);
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
		std::shared_ptr<CSampler3f>	m_dSampler;
	};
}



