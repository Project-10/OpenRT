// Diffuse shader class
// Written by Dr. Sergey G. Kosov in 2025 for Project X
#include "Shader.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Diffuse Shader Class ================================
	/**
	 * @brief Diffuse shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderDiffuse : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 */
		DllExport CShaderDiffuse(const CScene& scene, const Vec3f& color)
			: CShader(color)
			, m_scene(scene)
		{ }
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 */
		DllExport CShaderDiffuse(const CScene& scene, const ptr_texture_t pTexture)
			: CShader(pTexture)
			, m_scene(scene)
		{ }
		DllExport virtual ~CShaderDiffuse(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;


	private:
		const CScene& m_scene;		///< Reference to the scene object
	};
}
