#pragma once

#include "ShaderFlat.h"

namespace rt {
	class CScene;

	class CShaderPhong : public CShaderFlat
	{
	public:
		/**
		 * @brief Constructor
		 * @details
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
			
			Vec3f normal			= ray.hit->getNormal(ray);									// shading normal
			if (normal.dot(ray.dir) > 0) normal = -normal;										// turn normal to front
			Vec3f reflect			= normalize(ray.dir - 2 * normal.dot(ray.dir) * normal);	// reflection vector

			Vec3f ambientRadiance	= Vec3f::all(1);
			Vec3f color				= CShaderFlat::shade();
			Vec3f ambientColor		= m_ka * color;
			Vec3f diffuseColor		= m_kd * color;
			Vec3f specularColor		= m_ks * RGB(1, 1, 1); // white highlight;
			
			// Ambient term
			res += ambientColor.mul(ambientRadiance);

			Ray I(ray.hitPoint());		// Ray from the hitpoint to the light source 

			for (auto& pLight : m_scene.getLights()) {
				Vec3f L = Vec3f::all(0);
				const size_t nSamples = pLight->getNumberOfSamples();
				for (size_t s = 0; s < nSamples; s++) {
					// get direction to light, and intensity
					auto radiance = pLight->illuminate(I);
					if (radiance && (!pLight->shadow() || !m_scene.occluded(I))) {
						// DIffuse term
						float cosLightNormal = I.dir.dot(normal);
						if (cosLightNormal > 0)
							L += cosLightNormal * diffuseColor.mul(radiance.value());

						// Specular term
						float cosLightReflect = I.dir.dot(reflect);
						if (cosLightReflect > 0)
							L += powf(cosLightReflect, m_ke) * specularColor.mul(radiance.value());
					}
				} // s
				res += (1.0f / nSamples) * L;
			} // pLight
			
			for (int i = 0; i < 3; i++)
				if (res.val[i] > 1) res.val[i] = 1;

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
