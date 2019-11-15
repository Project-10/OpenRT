#include "Shader.h"
#include "Scene.h"
#include "ray.h"

namespace rt {
	Vec3f CShader::shade(const Ray& ray) const
	{
		Vec3f normal = ray.hit->getNormal(ray.hitPoint());						// shading normal
		bool inside = false;
		if (normal.dot(ray.dir) > 0) {
			normal = -normal;													// turn normal to front
			inside = true;
		}
		
		// Needed by   ks, km, kt
		Ray reflected = (m_ks > 0 || m_km > 0 || m_kt > 0) ? ray.reflected(normal) : ray;	// reflection vector

		Vec3f color	= CShaderFlat::shade(ray);
		Vec3f res 	= Vec3f::all(0);
		
		// ------ ambient ------
		if (m_ka > 0)
			res += m_ka * Vec3f::all(1).mul(color);
		
		// ------ diffuse and/or specular ------
		if (m_kd > 0 || m_ke > 0) {
			Ray I(ray.hitPoint());
			
			for (auto& pLight : m_scene.getLights()) {
				Vec3f L = Vec3f::all(0);
				const size_t nSamples = pLight->getNumberOfSamples();
				for (size_t s = 0; s < nSamples; s++) {
					// get direction to light, and intensity
					auto radiance = pLight->illuminate(I);
					if (radiance && (!pLight->shadow() || !m_scene.occluded(I))) {
						// ------ diffuse ------
						if (m_kd > 0) {
							float cosLightNormal = I.dir.dot(normal);
							if (cosLightNormal > 0)
								L += m_kd * cosLightNormal * color.mul(radiance.value());
						}
						// ------ specular ------
						if (m_ks > 0) {
							float cosLightReflect = I.dir.dot(reflected.dir);
							if (cosLightReflect > 0)
								L += m_ks * powf(cosLightReflect, m_ke) * Vec3f::all(1).mul(radiance.value());
						}
					}
				} // s
				res += (1.0f / nSamples) * L;
			} // pLight
		}
		
		// ------ reflection ------
		if (m_km > 0)
			res += m_km * m_scene.rayTrace(reflected);

		// ------ refraction ------
		if (m_kt > 0) {
			Ray refracted = ray.refracted(normal, inside ? m_refractiveIndex : 1.0f / m_refractiveIndex).value_or(reflected);
			res += m_kt * m_scene.rayTrace(refracted);
		}

		return res;
	}
}

