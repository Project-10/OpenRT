// Diffuse shader class
// Written by Dr. Sergey G. Kosov in 2025 for Project X
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Diffuse Shader Class ================================
	/**
	 * @brief Diffuse shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderDiffuse : public CNewShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 * @param sigma
		 */
		DllExport CShaderDiffuse(const CScene& scene, const Vec3f& color, float sigma = 0);
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 * @param sigma
		 */
		DllExport CShaderDiffuse(const CScene& scene, const ptr_texture_t pTexture, float sigma = 0);
		DllExport virtual ~CShaderDiffuse(void) = default;
	};
}
