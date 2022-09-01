// Flat Shader class
// Written by Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "Shader.h"

namespace rt {
	// ================================ Flat Shader Class ================================
	/**
	 * @brief Flat shader class
	 * @details This shader does not take scene in account. Therefore it is independenta from light sources and cameras.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderFlat : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free and light-source-free shader
		 * @param color The color of the object
		 */
		DllExport CShaderFlat(const Vec3f& color) : CShader(color) {}
		/**
		 * @brief Constructor
		 * @details This is a light-source-free shader
		 * @param pTexture Pointer to the texture
		 */
		DllExport CShaderFlat(const ptr_texture_t pTexture) : CShader(pTexture) {}
		DllExport virtual ~CShaderFlat(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;
	};
}
