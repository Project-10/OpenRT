// General shader class
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "ShaderFlat.h"
#include "Sampler.h"

namespace rt {
	class CScene;
	
	class CShader : public CShaderFlat
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 * @param kd The diffuse reflection coefficients
		 * @param ks The specular refelection coefficients
		 * @param ke The shininess exponent
		 * @param km The perfect reflection (mirror) coefficient
		 * @param kt The perfect transmission coefficient
		 * @param refractiveIndex The refractive index of the medium (for glass use 1.517)
		 */
		DllExport CShader(CScene& scene, Vec3f color, float ka, float kd, float ks, float ke, float km, float kt, float refractiveIndex, std::shared_ptr<CSampler> pSampler = std::make_shared<CSamplerStratified>(1, false) )
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
		DllExport virtual ~CShader(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override;
	
	
	private:
		
		
	private:
		CScene& m_scene;
		
		float m_ka;    				///< The ambient coefficient
		float m_kd;    				///< The diffuse reflection coefficients
		float m_ks;    				///< The specular refelection coefficients
		float m_ke;    				///< The shininess exponent
		float m_km;					///< The perfect reflection (mirror) coefficient
		float m_kt;					///< The perfect transmission coefficient
		
		float m_refractiveIndex;	///< The refractive index for transmitted rays
		
		std::shared_ptr<CSampler>	m_pSampler;
	};


	class CShaderGlass : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param refractiveIndex The refractive index of the medium (for glass use 1.517)
		 */
		DllExport CShaderGlass(CScene& scene, float refractiveIndex) : CShader(scene, Vec3f::all(0), 0, 0, 0, 0, 0, 1, refractiveIndex) {}
		DllExport virtual ~CShaderGlass(void) = default;
	};


	class CShaderMirror : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 */
		DllExport CShaderMirror(CScene& scene) : CShader(scene, Vec3f::all(0), 0, 0, 0, 0, 1, 0, 0) {}
		DllExport virtual ~CShaderMirror(void) = default;
	};

	
	class CShaderPhong : public CShader
	{
	public:
		DllExport CShaderPhong(CScene& scene, Vec3f color, float ka, float kd, float ks, float ke)
			: CShader(scene, color, ka, kd, ks, ke, 0, 0, 0) {}
		DllExport virtual ~CShaderPhong(void) = default;
	};
}
