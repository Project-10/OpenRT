#include "ShaderPhong.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderPhong::shade(const Ray& ray) const
	{
		Vec3f res(0, 0, 0);

		Vec3f ambientColor	= getAmbientColor(ray);
		Vec3f diffuseColor	= getDiffuseColor(ray);
		float ks 			= getSpecularLevel(ray);

		Vec3f faceNormal	= ray.hit->getNormal(ray);							// face normal
		Vec3f shadingNormal = ray.hit->getShadingNormal(ray);					// shading normal
		
		
		auto du = getBump(ray);
		if (du) {
			auto  dp = ray.hit->dp(ray.hitPoint());
			Vec3f dpdu = dp.first;
			Vec3f dpdv = dp.second;

			shadingNormal += getBumpAmount() * (du.value().first * dpdv.cross(shadingNormal) - du.value().second * dpdu.cross(shadingNormal));
			shadingNormal = normalize(shadingNormal);
		}

		bool inside = false;
		if (faceNormal.dot(ray.dir) > 0) {
			shadingNormal = -shadingNormal;										// turn shading normal to front
			inside = true;
		}


		Ray reflected = (ks > 0) ? ray.reflected(shadingNormal) : ray;		// reflection vector

#ifdef DEBUG_MODE
		res = inside ? RGB(255, 0, 0) : RGB(0, 0, 255);
#endif

		// ------ ambient ------
		if (m_ka > 0)
			res += m_ka * m_scene.getAmbientColor().mul(ambientColor);

		// ------ diffuse and/or specular ------
		if (m_kd > 0 || m_ke > 0) {
			Ray I(ray.hitPoint(shadingNormal));												// shadow ray

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
							float cosLightNormal = I.dir.dot(shadingNormal);
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
		
		return res;
	}
}
