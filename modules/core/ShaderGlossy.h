// Chrome shader class
// Written by Dr. Sergey G. Kosov in 2025 for Open RT
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Glossy Shader Class ================================
	/**
	 * @brief Glossy reflection shader class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CShaderGlossy : public CNewShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color Reflection color - Color of the surface, or physically speaking, the probability that light is reflected for each wavelength.
		 * @param roughness Input for the surface roughness resulting in sharp to blurry reflections. Zero gives perfect sharp reflection.
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading.
		 */
		DllExport CShaderGlossy(const CScene& scene, const Vec3f& color = RGB(255, 255, 255), float roughness = 0.0f, ptr_sampler_t pSampler = nullptr);
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Reflection color map - Pointer to the texture
		 * @param roughness Input for the surface roughness resulting in sharp to blurry reflections. Zero gives perfect sharp reflection.
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading.
		 */
		DllExport CShaderGlossy(const CScene& scene, const ptr_texture_t pTexture, float roughness = 0.0f, ptr_sampler_t pSampler = nullptr);
		DllExport virtual ~CShaderGlossy(void) = default;
	};
}
