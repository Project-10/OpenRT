// Chrome shader class
// Written by Dr. Sergey G. Kosov in 2025 for Open RT
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;
	class CShaderGlossy : public CNewShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color Color of the surface
		 * @param roughness Input for the surface roughness resulting in sharp to blurry reflections.
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading.
		 */
		DllExport CShaderGlossy(const CScene& scene, const Vec3f& color, float roughness, ptr_sampler_t pSampler = nullptr);
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 * @param roughness Input for the surface roughness resulting in sharp to blurry reflections.
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading.
		 */
		DllExport CShaderGlossy(const CScene& scene, const ptr_texture_t pTexture, float roughness, ptr_sampler_t pSampler = nullptr);
		DllExport virtual ~CShaderGlossy(void) = default;
	};
}
