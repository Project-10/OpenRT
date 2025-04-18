// Chrome shader class
// Written by Dr. Sergey G. Kosov in 2025 for Open RT
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;
	class CShaderChrome : public CNewShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading
		 */
		DllExport CShaderChrome(const CScene& scene, ptr_sampler_t pSampler = nullptr);
		DllExport virtual ~CShaderChrome(void) = default;
	};
}
