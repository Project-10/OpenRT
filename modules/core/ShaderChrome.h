#pragma once

#include "IShader.h"
#include "Sampler3f.h"

namespace rt {
	class CShaderChrome : public IShader
	{
	public:
		DllExport CShaderChrome(CScene& scene, ptr_sampler_t pSampler = nullptr)
			: m_scene(scene)
			, m_pSampler(pSampler)
		{}
		DllExport virtual ~CShaderChrome(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override
		{		
			// TODO: elaborate on this
			return Vec3f::all(0);
			
			
			//Vec3f res = Vec3f::all(0);
			//
			//Vec3f normal = ray.hit->getNormal(ray);								// shading normal
			//if (normal.dot(ray.dir) > 0) normal = -normal;						// turn normal to front
			//
			//size_t nSamples = m_pSampler ? m_pSampler->getNumSamples() : 1;
			//for (size_t s = 0; s < nSamples; s++) {
			//	
			//	Vec3f n = normal;
			//	if (m_pSampler) {
			//		n = CSampler3f::getHemisphereSample(m_pSampler->getNextSample(), n, 10);
			//	}
			//		
			//	Ray I = ray.reflected(n);	// reflection vector
			//	//I.counter = std::max(maxRayCounter - 1, I.counter);
			//	res += I.counter >= maxRayCounter ? Vec3f::all(0.4f) : m_scene.rayTrace(I);
			//}
			//res = (1.0f / nSamples) * res;
			//return res;

		}
		

		
		
	private:
		CScene& 		m_scene;
		ptr_sampler_t	m_pSampler;
	};
}



