// Glass shader class
// Written by Dr. Sergey G. Kosov in 2025 for Open RT
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Glass Shader Class ================================
	/**
	 * @brief Glass shader
	 * @details Fully transparent shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CShaderGlass : public CNewShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param refractiveIndex The refractive index of the medium (for glass use 1.517)
		 */
		DllExport CShaderGlass(const CScene& scene, float refractiveIndex);
		DllExport virtual ~CShaderGlass(void) = default;
	};
}