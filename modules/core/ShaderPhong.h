// Phong shader class
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#include "ShaderScene.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Phong Shader Class ================================
	/**
	 * @brief Phong shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderPhong : public CShaderScene
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 * @param ka The ambient coefficient
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular reflection coefficient
		 * @param ke The shininess exponent
		 */
		DllExport CShaderPhong(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke)
			: CShaderScene(scene, color)
			, m_ka(ka)
			, m_kd(kd)
			, m_ke(ke)
		{
			setSpecularLevel(ks);
		}
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
			: CShaderScene(scene, pTexture)
			, m_ka(ka)
			, m_kd(kd)
			, m_ke(ke)
		{
			setSpecularLevel(ks);
		}
		DllExport virtual ~CShaderPhong(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override;
	
		
	private:
		float m_ka;    				///< The ambient coefficient
		float m_kd;    				///< The diffuse reflection coefficients
		float m_ke;    				///< The shininess exponent
	};
}
