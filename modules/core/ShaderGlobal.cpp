#include "ShaderGlobal.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderGlobal::shade(const Ray& ray) const 
	{
		Vec3f res(0, 0, 0);
		
		Vec3f diffuseColor	= getDiffuseColor(ray);
		Vec3f shadingNormal	= ray.hit->getShadingNormal(ray);							// shading normal
		
		res = diffuseColor * 0.1f;

		// ------ diffuse and/or specular ------
		Ray I(ray.hitPoint(shadingNormal));												// shadow ray

		
		// Gather direct light from the light sources
		Vec3f L = Vec3f::all(0);

		// Direct lightning
		for (auto& pLight : getScene().getLights()) {
			// Direct lightning
			size_t nSamples = pLight->getNumSamples();
			for (size_t s = 0; s < nSamples; s++) {
				// get direction to light, and intensity
				I.hit = ray.hit;	// TODO: double check
				auto radiance = pLight->illuminate(I);
				if (radiance) {
					// Check shadow (light sourse is occluded)
					float k_occlusion = pLight->shadow() ? getScene().evalOcclusion(I) : 1.0f;
					if (k_occlusion < Epsilon) continue;
					
					// ------ diffuse ------
					float cosLightNormal = I.dir.dot(shadingNormal);
					if (cosLightNormal > 0)
						L += (1.0f / nSamples) * cosLightNormal * k_occlusion * radiance.value();
				}
			} // s
		} // pLight

		// Indirect lightning
		size_t nSamples = getSampler() ? getSampler()->getNumSamples() : 1;
		for (size_t s = 0; s < nSamples; s++) {
			Vec3f dir = shadingNormal;
			if (getSampler()) {
				Vec2f sample = getSampler()->getNextSample();
				Vec3f hemisphereSample = CSampler::cosineSampleHemisphere(sample);
				dir = CSampler::transformSampleToWCS(hemisphereSample, shadingNormal);	// sample the hemisphere in respect to the object's normal
			}
			Ray I(ray.hitPoint(shadingNormal), dir, Vec2f::all(0), MAX(ray.counter, maxRayCounter - 2));
			Vec3f l = I.reTrace(getScene());

			L += 0.25f * Pif * (1.0f / nSamples) * l;	// for cosine-weighted
			//float cosLightNormal = dir.dot(shadingNormal);
			//if (cosLightNormal > 0)
			//	L += 2 * Pif * (1.0f / nSamples) * cosLightNormal * l;

		} // s


		res += diffuseColor.mul(L);


		return res;

		return diffuseColor;
	}
}
