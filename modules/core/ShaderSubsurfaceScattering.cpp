#include "ShaderSubsurfaceScattering.h"
#include "Scene.h"
#include "Ray.h"

Vec3f rt::CShaderSubsurfaceScattering::shade(const Ray& ray) const
{
	Vec3f diffuseColor = getDiffuseColor(ray);
	Vec3f n = ray.hit->getShadingNormal(ray);		// shading normal		
	Vec3f p = ray.hitPoint(n);

	// Gathering incoming light (incident radiance)
	Vec3f incident_radiance = eval_IR_LS(p, n);
	Vec3f res = InvPif * diffuseColor.mul(incident_radiance);
		
	if (ray.dir.dot(n) < 0 && ray.counter % 2 == 0) {						// entering the surface
			
		// ray into the object will stochastically bended
		size_t nSamples = getSampler() ? getSampler()->getNumSamples() : 1;
		for (size_t s = 0; s < nSamples; s++) {
			Vec3f dir = n;
			if (getSampler()) {
				Vec2f sample = getSampler()->getNextSample(s);
				Vec3f hemisphereSample = CSampler::uniformSampleHemisphere(sample, 0.7f);
				dir = CSampler::transformSampleToWCS(hemisphereSample, n);
			}

			// prepare the ray into the object
			Ray R(ray.hitPoint(-n), -dir, ray.ndc, ray.counter);
				
			Vec3f L = R.reTrace(getScene());			// color of the back-side of the object

			// Attenuate 				
			const double k = 0.15;
			const double f = k * R.t;					// linear
			//const double f = k * R.t * R.t;
			const double alpha = MIN(1, f);				// attenuation factor

			res += (1.0 - alpha) / nSamples * L;
		}
	}

	return res;
}



