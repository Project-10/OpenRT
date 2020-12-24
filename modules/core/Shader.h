// General shader class
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "ShaderFlat.h"
#include "Sampler.h"

namespace rt {
	class CScene;
	// ================================ General Shader Class ================================
	/**
	 * @brief Flat shader class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShader : public CShaderFlat
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
		DllExport CShader(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke, float km, float kt, float refractiveIndex, ptr_sampler_t pSampler = nullptr )
			: CShaderFlat(color)
			, m_scene(scene)
			, m_ka(ka)
			, m_kd(kd)
			, m_ks(ks)
			, m_ke(ke)
			, m_km(km)
			, m_kt(kt)
			, m_refractiveIndex(refractiveIndex)
			, m_pSampler(pSampler)
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
		DllExport CShader(const CScene& scene, const ptr_texture_t pTexture, float ka, float kd, float ks, float ke, float km, float kt, float refractiveIndex, ptr_sampler_t pSampler = nullptr)
			: CShaderFlat(pTexture)
			, m_scene(scene)
			, m_ka(ka)
			, m_kd(kd)
			, m_ks(ks)
			, m_ke(ke)
			, m_km(km)
			, m_kt(kt)
			, m_refractiveIndex(refractiveIndex)
			, m_pSampler(pSampler)
		{}
		DllExport virtual ~CShader(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override;
	
	
	private:
		const CScene& m_scene;		///< Reference to the scene object
		
		float m_ka;    				///< The ambient coefficient
		float m_kd;    				///< The diffuse reflection coefficients
		float m_ks;    				///< The specular refelection coefficients
		float m_ke;    				///< The shininess exponent
		float m_km;					///< The perfect reflection (mirror) coefficient
		float m_kt;					///< The perfect transmission coefficient
		
		float m_refractiveIndex;	///< The refractive index for transmitted rays
		
		ptr_sampler_t	m_pSampler;	///< Pointer to the sampler to be used for perturbing the shape normal during shading
	};

	// ================================ Glass Shader Class ================================
	/**
	 * @brief Glass shader 
	 * @details Fully transparent shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderGlass : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param refractiveIndex The refractive index of the medium (for glass use 1.517)
		 */
		DllExport CShaderGlass(const CScene& scene, float refractiveIndex) : CShader(scene, Vec3f::all(0), 0, 0, 0, 0, 0, 1, refractiveIndex) {}
		DllExport virtual ~CShaderGlass(void) = default;
	};

	// ================================ Mirror Shader Class ================================
	/**
	 * @brief Mirror shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderMirror : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 */
		DllExport CShaderMirror(const CScene& scene) : CShader(scene, Vec3f::all(0), 0, 0, 0, 0, 1, 0, 0) {}
		DllExport virtual ~CShaderMirror(void) = default;
	};

	// ================================ Phong Shader Class ================================
	/**
	 * @brief Phong shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderPhong : public CShader
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
		 */
		DllExport CShaderPhong(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke)
			: CShader(scene, color, ka, kd, ks, ke, 0, 0, 0) {}
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 * @param ka The ambient coefficient
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular refelection coefficient
		 * @param ke The shininess exponent
		 */
		DllExport CShaderPhong(const CScene& scene, const ptr_texture_t pTexture, float ka, float kd, float ks, float ke)
			: CShader(scene, pTexture, ka, kd, ks, ke, 0, 0, 0) {}
		DllExport virtual ~CShaderPhong(void) = default;
	};
}
