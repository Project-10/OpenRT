#include "LightSky.h"
#include "Sampler.h"
#include "Ray.h"
#include "random.h"

namespace rt{
	std::optional<Vec3f> CLightSky::illuminate(Ray& shadowray, const Vec3f& point, const Vec3f& normal, size_t s) const
	{
		Vec2f sample = m_pSampler ? m_pSampler->getNextSample(s) : Vec2f(random::U<float>(), random::U<float>());
		Vec3f hemisphereSample	= CSampler::cosineSampleHemisphere(sample);
		//Vec3f hemisphereSample	= CSampler::uniformSampleHemisphere(sample);

		shadowray = Ray(
			point,
			CSampler::transformSampleToWCS(hemisphereSample, normal)	// sample the hemisphere in respect to the object's normal
		);
		shadowray.t = m_maxDistance;

		float cosN = shadowray.dir.dot(normal);							// angle between the object's normal and sample ray
		if (cosN > 0)	return getIntensity() / cosN;
		else			return std::nullopt;
	}
}