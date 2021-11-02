// Eyelight class
// Written by Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "Shader.h"

namespace rt {
	// ================================ Flat Shader Class ================================
	/**
	 * @brief Eye-light shader class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderEyelight : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free and light-source-free shader
		 * @param color The color of the object
		 */
		DllExport CShaderEyelight(const Vec3f& color = RGB(0.5f, 0.5f, 0.5f))
			: CShader(color)
		{}
		/**
		 * @brief Constructor
		 * @details This is a light-source-free shader
		 * @param pTexture Pointer to the texture
		 */
		DllExport CShaderEyelight(const ptr_texture_t pTexture)
			: CShader(pTexture)
		{}
		DllExport virtual ~CShaderEyelight(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;
	};
}
