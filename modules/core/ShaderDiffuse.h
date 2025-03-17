// Diffuse shader class
// Written by Dr. Sergey G. Kosov in 2025 for Project X
#include "ShaderScene.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Diffuse Shader Class ================================
	/**
	 * @brief Diffuse shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderDiffuse : public CShaderScene
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 */
		DllExport CShaderDiffuse(const CScene& scene, const Vec3f& color)
			: CShaderScene(scene, color)
		{ }
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 */
		DllExport CShaderDiffuse(const CScene& scene, const ptr_texture_t pTexture)
			: CShaderScene(scene, pTexture)
		{ }
		DllExport virtual ~CShaderDiffuse(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;
	};
}
