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

		Vec3f faceNormal	= ray.hit->getNormal(ray);							// face normal
		Vec3f shadingNormal = ray.hit->getShadingNormal(ray);					// shading normal
		bool inside = false;
		if (faceNormal.dot(ray.dir) > 0) {
			shadingNormal = -shadingNormal;										// turn normal to front
			inside = true;
		}


		size_t nNormalSamples = m_pSampler ? m_pSampler->getNumSamples() : 1;
		for (size_t ns = 0; ns < nNormalSamples; ns++) {

			// Distort the normal vector
			Vec3f n = shadingNormal;
			if (m_pSampler) {
				n = CSampler::transformSampleToWCS(CSampler::uniformSampleHemisphere(m_pSampler->getNextSample(), 10), n);
			}

			// Needed by ks, km, kt
			Ray reflected = (ks > 0 || m_km > 0 || m_kt > 0) ? ray.reflected(n) : ray;	// reflection vector

			// ------ ambient ------
			if (m_ka > 0)
				res += m_ka * m_scene.getAmbientColor().mul(ambientColor);

			// ------ diffuse and/or specular ------
			if (m_kd > 0 || m_ke > 0) {
				Ray I(ray.hitPoint(shadingNormal));

				for (auto& pLight : m_scene.getLights()) {
					Vec3f L = Vec3f::all(0);
					const size_t nSamples = pLight->getNumSamples();
					for (size_t s = 0; s < nSamples; s++) {
						// get direction to light, and intensity
						I.hit = ray.hit;	// TODO: double check
						auto radiance = pLight->illuminate(I);
						if (radiance && (!pLight->shadow() || !m_scene.if_intersect(I))) {
							// ------ diffuse ------
							if (m_kd > 0) {
								float cosLightNormal = I.dir.dot(n);
								if (cosLightNormal > 0)
									L += m_kd * cosLightNormal * diffuseColor.mul(radiance.value());
							}
							// ------ specular ------
							if (ks > 0) {
								float cosLightReflect = I.dir.dot(reflected.dir);
								if (cosLightReflect > 0)
									L += ks * powf(cosLightReflect, m_ke) * radiance.value();
							}
						}
					} // s
					res += (1.0f / nSamples) * L;
				} // pLight
			}

			// ------ reflection ------
			std::optional<Vec3f> reflection = std::nullopt;		// reflected color
			if (m_km > 0) {
				reflection = reflected.reTrace(m_scene);
				res += m_km * reflection.value();
			}

			// ------ refraction ------
			if (m_kt > 0) {
				auto refracted = ray.refracted(n, inside ? m_refractiveIndex : 1.0f / m_refractiveIndex);
				if (refracted) 			res += m_kt * refracted.value().reTrace(m_scene);
				else if (reflection)	res += m_kt * reflection.value();
				else 					res += m_kt * reflected.reTrace(m_scene);	
			}
		} // ns
		
		res = (1.0f / nNormalSamples) * res;
		return res;
	}
}

