#include "ShaderBlinn.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderBlinn::shade(const Ray& ray) const
	{
		Vec3f res(0, 0, 0);

		Vec3f ambientColor	= getAmbientColor(ray);
		Vec3f diffuseColor	= getDiffuseColor(ray);
		float ks			= getSpecularLevel(ray);
		float opacity		= getOpacity(ray);

		Vec3f faceNormal	= ray.hit->getNormal(ray);							// face normal
		Vec3f shadingNormal = ray.hit->getShadingNormal(ray);					// shading normal
		bool inside = false;
		if (faceNormal.dot(ray.dir) > 0) {
			shadingNormal = -shadingNormal;										// turn shading normal to front
			inside = true;
		}

		// ------ opacity ------
		if (opacity < 1) {
			Ray R(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
			res += (1.0f - opacity) * R.reTrace(getScene());
		}

		// ------ ambient ------
		if (m_ka > 0)
			res += m_ka * opacity * getScene().getAmbientColor().mul(ambientColor);

		// ------ diffuse and/or specular ------
		if (m_kd > 0 || m_ke > 0) {
			thread_local Ray I;

			for (auto& pLight : getScene().getLights()) {
				Vec3f L = Vec3f::all(0);
				const size_t nSamples = pLight->getNumSamples();
				for (size_t s = 0; s < nSamples; s++) {
					// get direction to light, and intensity
					//I.hit = ray.hit;	// TODO: double check
					auto radiance = pLight->illuminate(I, ray.hitPoint(shadingNormal), shadingNormal);
					if (radiance) { 
						// Check shadow (light sourse is occluded)
						float k_occlusion = pLight->shadow() ? getScene().evalOcclusion(I) : 1.0f;
						if (k_occlusion < Epsilon) continue;
						
						// ------ diffuse ------
						if (m_kd > 0) {
							float cosLightNormal = I.dir.dot(shadingNormal);
							if (cosLightNormal > 0)
								L += m_kd * opacity * cosLightNormal * k_occlusion * diffuseColor.mul(radiance.value());
						}
						// ------ specular ------
						if (ks > 0) {
							Vec3f H = normalize(I.dir - ray.dir);
							float cosHalfwayNormal = H.dot(shadingNormal);
							if (cosHalfwayNormal > 0)
								L += ks * powf(cosHalfwayNormal, m_ke) * k_occlusion * radiance.value();
						}
					}
				} // s
				res += (1.0f / nSamples) * L;
			} // pLight
		}
		
		return res;
	}
}
