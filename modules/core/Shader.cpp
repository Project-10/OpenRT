#include "Shader.h"
#include "Scene.h"
#include "ray.h"

namespace rt {
	const static Vec3f exitColor	 = RGB(0.4f, 0.4f, 0.4f);	// errors area
	const static Vec3f ambientColor	 = RGB(1, 1, 1);			// ambient radiance
	const static Vec3f specularColor = RGB(1, 1, 1);			// white highlight;

	Vec3f CShader::shade(const Ray& ray) const
	{
		Vec3f res(0, 0, 0);

		Vec3f color = CShaderFlat::shade(ray);

		Vec3f normal = ray.hit->getNormal(ray);									// shading normal
		bool inside = false;
		if (normal.dot(ray.dir) > 0) {
			normal = -normal;													// turn normal to front
			inside = true;
		}

#ifdef DEBUG_MODE
		color = inside ? RGB(1, 0, 0) : RGB(0, 0, 1);
#endif

		size_t nNormalSamples = m_pSampler ? m_pSampler->getNumSamples() : 1;
		for (size_t ns = 0; ns < nNormalSamples; ns++) {

			// Distort the normal vector
			Vec3f n = normal;
			if (m_pSampler) {
				n = CSampler3f::getHemisphereSample(m_pSampler->getNextSample(), n, 10);
			}

			// Needed by   ks, km, kt
			Ray reflected = (m_ks > 0 || m_km > 0 || m_kt > 0) ? ray.reflected(n) : ray;	// reflection vector

			// ------ ambient ------
			if (m_ka > 0)
				res += m_ka * ambientColor.mul(color);

			// ------ diffuse and/or specular ------
			if (m_kd > 0 || m_ke > 0) {
				Ray I(ray.hitPoint());

				for (auto& pLight : m_scene.getLights()) {
					Vec3f L = Vec3f::all(0);
					const size_t nSamples = pLight->getNumberOfSamples();
					for (size_t s = 0; s < nSamples; s++) {
						// get direction to light, and intensity
						I.hit = ray.hit;	// TODO: double check
						auto radiance = pLight->illuminate(I);
						if (radiance && (!pLight->shadow() || !m_scene.occluded(I))) {
							// ------ diffuse ------
							if (m_kd > 0) {
								float cosLightNormal = I.dir.dot(n);
								if (cosLightNormal > 0)
									L += m_kd * cosLightNormal * color.mul(radiance.value());
							}
							// ------ specular ------
							if (m_ks > 0) {
								float cosLightReflect = I.dir.dot(reflected.dir);
								if (cosLightReflect > 0)
									L += m_ks * powf(cosLightReflect, m_ke) * specularColor.mul(radiance.value());
							}
						}
					} // s
					res += (1.0f / nSamples) * L;
				} // pLight
			}

			// ------ reflection ------
			if (m_km > 0) 
				res += m_km * reTrace(reflected);

			// ------ refraction ------
			if (m_kt > 0) {
				Ray refracted = ray.refracted(n, inside ? m_refractiveIndex : 1.0f / m_refractiveIndex).value_or(reflected);
				res += m_kt * reTrace(refracted);
			}
		} // ns
		
		res = (1.0f / nNormalSamples) * res;
		return res;
	}

	Vec3f CShader::reTrace(const Ray& ray) const
	{
		return ray.counter >= maxRayCounter ? exitColor : m_scene.rayTrace(lvalue_cast(Ray(ray.org, ray.dir, ray.counter)));
	}

	std::optional<Ray> CShader::interaction(Ray &ray){
		Vec3f normal = ray.hit->getNormal(ray);									// shading normal
		bool inside = false;
		if (normal.dot(ray.dir) > 0) {
			normal = -normal;													// turn normal to front
			inside = true;
		}
		Vec3f n = normal;
		if (m_pSampler) {
				n = CSampler3f::getHemisphereSample(m_pSampler->getNextSample(), n, 1);
			}
		Ray reflected = (m_ks > 0 || m_km > 0 || m_kt > 0) ? ray.reflected(n) : ray;

		// TODO use russian roulette to decide wht to do if both reflection and refraction
		ray.brdf = 1;
		// ------ refraction ------
		if (m_kt > 0) {
			Ray refracted = ray.refracted(n, inside ? m_refractiveIndex : 1.0f / m_refractiveIndex).value_or(reflected);
			refracted.brdf =m_kt;
			refracted.hit = nullptr;
			return refracted;
		}
		// ------ reflection ------
		if (m_km > 0)
			reflected.brdf =m_km;
			reflected.hit = nullptr;
			return reflected;

        return std::nullopt;
	}

	Vec3f CShader::shadePhoton(Photon& photon){
		Vec3f res(0, 0, 0);
		Vec3f color = CShaderFlat::shadePhoton(photon);
		Ray ray(photon.hit,photon.dir);
		ray.hit = photon.prim;
		Vec3f normal = ray.hit->getNormal(ray);									// shading normal
		bool inside = false;
		if (normal.dot(ray.dir) > 0) {
			normal = -normal;													// turn normal to front
			inside = true;
		}

#ifdef DEBUG_MODE
		color = inside ? RGB(1, 0, 0) : RGB(0, 0, 1);
#endif

		// Distort the normal vector
		Vec3f n = normal;
		if (m_pSampler) {
			n = CSampler3f::getHemisphereSample(m_pSampler->getNextSample(), n, 10);
		}

		// Needed by   ks, km, kt
		Ray reflected = ray.reflected(n);// reflection vector

		// ------ ambient ------
		if (m_ka > 0)
			res += m_ka * ambientColor.mul(color);

		// ------ diffuse and/or specular ------
			// ------ diffuse ------
		if (m_kd > 0)
		{
			float cosLightNormal = abs(photon.dir.dot(-n));
			if (cosLightNormal > 0)
				res += m_kd * cosLightNormal * color.mul(photon.radiance);
		}
		// ------ specular ------
		if (m_ks > 0)
		{
			float cosLightReflect = abs(photon.dir.dot(reflected.dir));
			if (cosLightReflect > 0)
				res += m_ks * powf(cosLightReflect, m_ke) * specularColor.mul(photon.radiance);
		}
		// ------ refraction ------
		photon.brdf = 1.0f;
		if (m_kt > 0) {
			photon.brdf *= m_kt;
			// res*= m_kt;
		}
		// ------ reflection ------
		if (m_km > 0)
			photon.brdf *= m_km;
			// res*= m_km;

		// ------ reflection ------
		photon.radiance = res;
		photon.radiance = photon.radiance / pow(norm(photon.org - photon.hit),1); //REVIEW
		return ray.reflected(n).dir; ;

	}
}

