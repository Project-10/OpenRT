// Flat Shader class
// Written by Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "IShader.h"
#include "Texture.h"

namespace rt {
	// ================================ Flat Shader Class ================================
	/**
	 * @brief Flat shader class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderFlat : public IShader
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free and light-source-free shader
		 * @param color The color of the object
		 */
		DllExport CShaderFlat(const Vec3f& color) : m_color(color) {}
		/**
		 * @brief Constructor
		 * @details This is a light-source-free shader
		 * @param pTexture Pointer to the texture
		 */
		DllExport CShaderFlat(const ptr_texture_t pTexture) : m_pTexture(pTexture) {}
		DllExport virtual ~CShaderFlat(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;


	private:
		const Vec3f 		m_color;
		const ptr_texture_t m_pTexture	= nullptr;
	};
}
