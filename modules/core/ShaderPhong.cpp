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
		bool inside = false;
		if (faceNormal.dot(ray.dir) > 0) {
			shadingNormal = -shadingNormal;										// turn shading normal to front
			inside = true;
		}
		
		Ray reflected = (ks > 0) ? ray.reflected(shadingNormal) : ray;		// reflection vector

		float bump = getBump(ray);
		if (bump != 0) {
			Vec3f ocs = ray.hit->wcs2ocs(ray.hitPoint());
			float x = ocs[0];
			float y = ocs[1];
			float z = ocs[2];
			float r = norm(ocs);
			float cos_phi = x / r;
			float sin_phi = z / r;
			float sin_theta = sqrtf(x*x + z*z) / r;

			const Vec3f dpdu = 2 * Pif * Vec3f(-z, 0, x);
			const Vec3f dpdv = Pif * Vec3f(y * cos_phi, -r * sin_theta, y * sin_phi);
			
			float dddu = getBumpU(ray);
			float dddv = getBumpV(ray);

			shadingNormal += 0.005f * (dddv * dpdu.cross(shadingNormal) + dddu * dpdv.cross(shadingNormal));
			shadingNormal = normalize(shadingNormal);
		}

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
