// Principled  shader class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#pragma once

#include "NewShader.h"

namespace rt{
	class CShaderPrincipled : public CNewShader {
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular refelection coefficient
		 * @param ke The shininess exponent
		 * @param kr The perfect reflection coefficient
		 * @param kt The perfect transmission coefficient
		 * @param refractiveIndex The refractive index of the medium (\a e.g. for glass use 1.517)
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading
		 */
		DllExport CShaderPrincipled(const CScene& scene, const Vec3f& color, float kd, float ks, float ke, float kr, float kt, float refractiveIndex, ptr_sampler_t pSampler = nullptr);
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular refelection coefficient
		 * @param ke The shininess exponent
		 * @param kr The perfect reflection coefficient
		 * @param kt The perfect transmission coefficient
		 * @param refractiveIndex The refractive index of the medium (\a e.g. for glass use 1.517)
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading
		 */
		DllExport CShaderPrincipled(const CScene& scene, const ptr_texture_t pTexture, float kd, float ks, float ke, float kr, float kt, float refractiveIndex, ptr_sampler_t pSampler = nullptr);

		DllExport virtual ~CShaderPrincipled(void) = default;


		
	private:
	};
}