#include "ShaderGeneral.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {	
	Vec3f CShaderGeneral::shade(const Ray& ray) const
	{
		Vec3f res(0, 0, 0);

		Vec3f ambientColor	= getAmbientColor(ray);
		Vec3f diffuseColor	= getDiffuseColor(ray);
		float ks 			= getSpecularLevel(ray);
		float opacity		= getOpacity(ray);

		Vec3f faceNormal	= ray.hit->getNormal(ray);							// face normal
		Vec3f shadingNormal = ray.hit->getShadingNormal(ray);					// shading normal
		bool inside = false;
		if (faceNormal.dot(ray.dir) > 0) {
			shadingNormal = -shadingNormal;										// turn normal to front
			inside = true;
		}


		size_t nNormalSamples = getSampler() ? getSampler()->getNumSamples() : 1;
		for (size_t ns = 0; ns < nNormalSamples; ns++) {

			// Distort the normal vector
			Vec3f n = shadingNormal;
			if (getSampler()) {
				n = CSampler::transformSampleToWCS(CSampler::uniformSampleHemisphere(getSampler()->getNextSample(), 10), n);
			}

			// Needed by ks, km, kt
			Ray reflected = (ks > 0 || m_km > 0 || m_kt > 0) ? ray.reflected(n) : ray;	// reflection vector

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
				for (auto& pLight : getScene().getLights()) {
					Vec3f L = Vec3f::all(0);
					const size_t nSamples = pLight->getNumSamples();
					for (size_t s = 0; s < nSamples; s++) {
						// get direction to light, and intensity
						thread_local Ray I;
						auto radiance = pLight->illuminate(I, ray.hitPoint(shadingNormal), shadingNormal);
						if (radiance) {
							// Check shadow (light sourse is occluded)
							float k_occlusion = pLight->shadow() ? getScene().evalOcclusion(I) : 1.0f;
							if (k_occlusion < Epsilon) continue;

							// ------ diffuse ------
							if (m_kd > 0) {
								float cosLightNormal = I.dir.dot(n);
								if (cosLightNormal > 0)
									L += m_kd * opacity * cosLightNormal * k_occlusion * diffuseColor.mul(radiance.value());
							}
							// ------ specular ------
							if (ks > 0) {
								float cosLightReflect = I.dir.dot(reflected.dir);
								if (cosLightReflect > 0)
									L += ks * powf(cosLightReflect, m_ke) * k_occlusion * radiance.value();
							}
						}
					} // s
					res += (1.0f / nSamples) * L;
				} // pLight
			}

			// ------ reflection ------
			std::optional<Vec3f> reflection = std::nullopt;		// reflected color
			if (m_km > 0) {
				reflection = reflected.reTrace(getScene());
				res += m_km * reflection.value();
			}

			// ------ refraction ------
			if (m_kt > 0) {
				auto refracted = ray.refracted(n, inside ? m_refractiveIndex : 1.0f / m_refractiveIndex);
				if (refracted) 			res += m_kt * refracted.value().reTrace(getScene());
				else if (reflection)	res += m_kt * reflection.value();
				else 					res += m_kt * reflected.reTrace(getScene());
			}
		} // ns
		
		res = (1.0f / nNormalSamples) * res;
		return res;
	}
}

