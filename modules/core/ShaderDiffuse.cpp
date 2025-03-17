#include "ShaderDiffuse.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderDiffuse::shade(const Ray& ray) const
	{
		Vec3f res(0, 0, 0);

		Vec3f diffuseColor = getDiffuseColor(ray);
		float opacity = getOpacity(ray);

		Vec3f faceNormal = ray.hit->getNormal(ray);							// face normal
		Vec3f shadingNormal = ray.hit->getShadingNormal(ray);				// shading normal

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
			shadingNormal = -shadingNormal;								// turn shading normal to front
			inside = true;
		}

#ifdef DEBUG_MODE
		res = inside ? RGB(255, 0, 0) : RGB(0, 0, 255);
#endif
		// ------ opacity ------
		if (opacity < 1) {
			Ray R(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
			res += (1.0f - opacity) * R.reTrace(getScene());
		}

		// Gathering incoming light (incident radiance)
		Vec3f incident_radiance = eval_IR_LS(ray);
		res += opacity * diffuseColor.mul(incident_radiance);

		return res;
	}
}
