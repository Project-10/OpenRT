// Diffuse shader class
// Written by Dr. Sergey G. Kosov in 2025 for Project X
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Diffuse Shader Class ================================
	/**
	 * @brief Diffuse shader
	 * @details The Diffuse shader is used to add Lambertian and Oren-Nayar diffuse reflection.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderDiffuse : public CNewShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color Color of the surface
		 * @param roughness Surface roughness; 0.0 gives standard Lambertian reflection, higher values activate the Oren-Nayar BRDF.
		 */
		DllExport CShaderDiffuse(const CScene& scene, const Vec3f& color, float roughness = 0);
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 * @param roughness Surface roughness; 0.0 gives standard Lambertian reflection, higher values activate the Oren-Nayar BRDF.
		 */
		DllExport CShaderDiffuse(const CScene& scene, const ptr_texture_t pTexture, float sigma = 0);
		DllExport virtual ~CShaderDiffuse(void) = default;
	};
}
