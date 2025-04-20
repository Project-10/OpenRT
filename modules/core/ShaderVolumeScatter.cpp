#include "ShaderVolumeScatter.h"
#include "Scene.h"
#include "Ray.h"

namespace rt
{
	Vec3f CShaderVolumeScatter::shade(const Ray& ray) const
	{
		Vec3f diffuseColor = getDiffuseColor(ray);
		float opacity = getOpacity(ray);

		// Gathering incoming light (incident radiance)
		Vec3f incident_radiance = eval_IR_LS(ray);

		Ray R(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
		Vec3f res = R.reTrace(getScene());

		Vec3f n = ray.hit->getShadingNormal(ray);				// shading normal
		if (ray.dir.dot(n) < 0) { // entering the surface
			const double k = 0.35;	  // dencity
			const double f = k * R.t; // linear
			//const double f = k * R.t * R.t;
			const double alpha = MIN(1, f);

			return alpha * InvPif * diffuseColor.mul(incident_radiance) + (1 - alpha) * res;
		}
		else return res;
		//
		//return opacity * diffuseColor + (1.0f - opacity) * res;

		opacity = 1.0f; // for debugging
		res = opacity * diffuseColor.mul(incident_radiance);

		return res;
	}
}

