#pragma once

#include "IShader.h"
#include "Sampler.h"

namespace rt {
	class CScene;

	class CShaderChrome : public IShader
	{
	public:
		DllExport CShaderChrome(const CScene& scene, ptr_sampler_t pSampler = nullptr)
			: m_scene(scene)
			, m_pSampler(pSampler)
		{}
		DllExport virtual ~CShaderChrome(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override;
		
		
	private:
		const CScene& 	m_scene;		///< Reference to the scene object
		ptr_sampler_t	m_pSampler;		///< Pointer to the sampler to be used for perturbing the shape normal during shading
	};
}



