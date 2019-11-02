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
		DllExport CShaderPhong(CScene& scene, Vec3f color, float ka, float kd, float ks, float ke)
			: CShaderFlat(color)
			, m_scene(scene)
			, m_ka(ka)
			, m_kd(kd)
			, m_ks(ks)
			, m_ke(ke)
		{}
		DllExport virtual ~CShaderPhong(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override
		{
			Vec3f res				= Vec3f::all(0);
			
			Vec3f ambientIntensity	= Vec3f::all(1);
			Vec3f color				= CShaderFlat::shade();
			Vec3f ambientColor		= m_ka * color;
			Vec3f diffuseColor		= m_kd * color;
			Vec3f specularColor		= m_ks * RGB(1, 1, 1); // white highlight;
			
			res += ambientColor.mul(ambientIntensity);
			
			return res;
		}

		
	private:
		CScene& m_scene;
		float 	m_ka;    ///< ambient coefficient
		float 	m_kd;    ///< diffuse reflection coefficients
		float 	m_ks;    ///< specular refelection coefficients
		float 	m_ke;    ///< shininess exponent
	};
}
