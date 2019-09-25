#pragma once

#include "ShaderFlat.h"

namespace rt {
	class CScene;

	class CShaderPhong : public CShaderFlat
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene Reference to the scene
		 * @param color The color of the object
		 * @param ka The ambient coefficient
		 * @param kd The diffuse reflection coefficients
		 * @param ks The specular refelection coefficients
		 * @param ke The shininess exponent
		 */
		CShaderPhong(CScene& scene, Vec3f color, float ka, float kd, float ks, float ke)
			: CShaderFlat(color)
			, m_scene(scene)
			, m_ka(ka)
			, m_kd(kd)
			, m_ks(ks)
			, m_ke(ke)
		{}
		virtual ~CShaderPhong(void) = default;

		virtual Vec3f Shade(const Ray& ray) const override
		{
			// --- PUT YOUR CODE HERE ---
			return RGB(0, 0, 0);
		}

		
	private:
		CScene& m_scene;
		float 	m_ka;    ///< ambient coefficient
		float 	m_kd;    ///< diffuse reflection coefficients
		float 	m_ks;    ///< specular refelection coefficients
		float 	m_ke;    ///< shininess exponent
	};
}
