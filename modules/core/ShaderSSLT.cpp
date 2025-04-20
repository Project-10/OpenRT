#include "ShaderSSLT.h"
#include "Scene.h"
#include "Ray.h"

namespace rt
{
	Vec3f CShaderSSLT::shade(const Ray& ray) const
	{
		Vec3f diffuseColor = getDiffuseColor(ray);
		Vec3f n = ray.hit->getShadingNormal(ray);		// shading normal		

		// Gathering incoming light (incident radiance)
		Vec3f incident_radiance = eval_IR_LS(ray);
		Vec3f res = diffuseColor.mul(incident_radiance);
		
		if (ray.dir.dot(n) < 0 && ray.counter % 2 == 0) {						// entering the surface
			
			// ray into the object will stochastically bended
			size_t nSamples = getSampler() ? getSampler()->getNumSamples() : 1;
			for (size_t s = 0; s < nSamples; s++) {
				Vec3f dir = n;
				if (getSampler()) {
					Vec2f sample = getSampler()->getNextSample(s);
					Vec3f hemisphereSample = CSampler::uniformSampleHemisphere(sample, 2);
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

	//Vec3f CShaderSSLT::shade(const Ray& ray) const
	//{
	//	Vec3f diffuseColor = getDiffuseColor(ray);
	//	float opacity = getOpacity(ray);

	//	// Gathering incoming light (incident radiance)
	//	Vec3f incident_radiance = eval_IR_LS(ray);

	//	Ray R(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
	//	Vec3f res = R.reTrace(getScene());

	//	Vec3f n = ray.hit->getShadingNormal(ray);				// shading normal		
	//	if (ray.dir.dot(n) < 0) { // entering the surface
	//		const double k = 0.35;
	//		const double f = k * R.t; // linear
	//		//const double f = k * R.t * R.t;
	//		const double alpha = MIN(1, f);

	//		return alpha * diffuseColor.mul(incident_radiance) + (1 - alpha) * res;
	//	}
	//	else return res;
	//	//
	//	//return opacity * diffuseColor + (1.0f - opacity) * res;

	//	opacity = 1.0f; // for debugging
	//	res = opacity * diffuseColor.mul(incident_radiance);

	//	return res;
	//}
}
