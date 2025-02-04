#include "LightSky.h"
#include "Sampler.h"
#include "Ray.h"

namespace rt{
	std::optional<Vec3f> CLightSky::illuminate(Ray& ray) const
	{
		ray.t = 0;
		Vec3f normal = ray.hit->getNormal(ray);												// normal to the object from which the ray was casted
		
		Vec2f squareSample		= m_pSampler->getNextSample();
		Vec3f hemisphereSample	= CSampler::cosineSampleHemisphere(squareSample);		
		//Vec3f hemisphereSample	= CSampler::uniformSampleHemisphere(squareSample);
		ray.dir					= CSampler::transformSampleToWCS(hemisphereSample, normal);	// sample the hemisphere in respect to the object's normal

		// ray towards point light position
		ray.t = m_maxDistance;
		ray.hit = nullptr;

		float cosN = ray.dir.dot(normal);													// angle between the object's normal and sample ray
		if (cosN > 0)	return getIntensity() / cosN;
		else			return std::nullopt;
	}
}