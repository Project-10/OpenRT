// Blinn shader class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Phong Shader Class ================================
	/**
	 * @brief Phong shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CShaderBlinn : public CNewShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular reflection coefficient
		 * @param ke The shininess exponent
		 */
		DllExport CShaderBlinn(const CScene& scene, const Vec3f& color, float kd, float ks, float ke);
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular refelection coefficient
		 * @param ke The shininess exponent
		 */
		DllExport CShaderBlinn(const CScene& scene, const ptr_texture_t pTexture, float kd, float ks, float ke);
		DllExport virtual ~CShaderBlinn(void) = default;
	};
}
