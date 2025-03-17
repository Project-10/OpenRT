// Blinn shader class
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#include "ShaderScene.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Blinn Shader Class ================================
	/**
	 * @brief Blinn shader
	 * @details Blinn is a bit faster approximation for Phong shader model.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderBlinn : public CShaderScene
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 * @param ka The ambient coefficient
		 * @param kd The diffuse reflection coefficient
		 * @param ks The specular refelection coefficient
		 * @param ke The shininess exponent (should be 4 times larger than for Phong to have the same highlight)
		 */
		DllExport CShaderBlinn(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke)
			: CShaderScene(scene, color)
			, m_ka(ka)
			, m_kd(kd)
			, m_ke(4 * ke)
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
		 * @param ke The shininess exponent (should be 4 times larger than for Phong to have the same highlight)
		 */
		DllExport CShaderBlinn(const CScene& scene, const ptr_texture_t pTexture, float ka, float kd, float ks, float ke)
			: CShaderScene(scene, pTexture)
			, m_ka(ka)
			, m_kd(kd)
			, m_ke(4 * ke)
		{}
		DllExport virtual ~CShaderBlinn(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override;

		
	private:
		float m_ka;    				///< The ambient coefficient
		float m_kd;    				///< The diffuse reflection coefficient
		float m_ke;    				///< The shininess exponent
	};
}
