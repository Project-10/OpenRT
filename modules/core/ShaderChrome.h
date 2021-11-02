// Chrome shader experimental class
// Written by Sergey G. Kosov in 2020 for Project X
#pragma once

#include "Shader.h"
#include "Sampler.h"

namespace rt {
	class CScene;
	// ================================ Chrome Shader Class ================================
	/**
	 * @brief Chrome shader
	 * @details This is an experimental class as a preparation step fpr path-tracing
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderChrome : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading
		 */
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



