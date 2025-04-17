// General shader class
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "ShaderScene.h"
#include "Sampler.h"

namespace rt {
	class CScene;
	// ================================ General Shader Class ================================
	/**
	 * @brief Flat shader class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CShaderGeneral : public CShaderScene
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 * @param ka The ambient coefficient
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular refelection coefficient
		 * @param ke The shininess exponent
		 * @param km The perfect reflection (mirror) coefficient
		 * @param kt The perfect transmission coefficient
		 * @param refractiveIndex The refractive index of the medium (\a e.g. for glass use 1.517)
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading
		 */
		DllExport CShaderGeneral(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke, float km, float kt, float refractiveIndex, ptr_sampler_t pSampler = nullptr )
			: CShaderScene(scene, color, pSampler)
			, m_ka(ka)
			, m_kd(kd)
			, m_ke(ke)
			, m_km(km)
			, m_kt(kt)
			, m_refractiveIndex(refractiveIndex)
		{}
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 * @param ka The ambient coefficient
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular refelection coefficient
		 * @param ke The shininess exponent
		 * @param km The perfect reflection (mirror) coefficient
		 * @param kt The perfect transmission coefficient
		 * @param refractiveIndex The refractive index of the medium (\a e.g. for glass use 1.517)
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading
		 */
		DllExport CShaderGeneral(const CScene& scene, const ptr_texture_t pTexture, float ka, float kd, float ks, float ke, float km, float kt, float refractiveIndex, ptr_sampler_t pSampler = nullptr)
			: CShaderScene(scene, pTexture, pSampler)
			, m_ka(ka)
			, m_kd(kd)
			, m_ke(ke)
			, m_km(km)
			, m_kt(kt)
			, m_refractiveIndex(refractiveIndex)
		{}
		DllExport virtual ~CShaderGeneral(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override;
	
	
	private:
		float m_ka;    				///< The ambient coefficient
		float m_kd;    				///< The diffuse reflection coefficients
		float m_ke;    				///< The shininess exponent
		float m_km;					///< The perfect reflection (mirror) coefficient
		float m_kt;					///< The perfect transmission coefficient
		
		float m_refractiveIndex;	///< The refractive index for transmitted rays
	};
}
