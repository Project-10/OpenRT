#include "LightSky.h"
#include "Ray.h"

namespace rt{
	std::optional<Vec3f> CLightSky::illuminate(Ray& ray) 
	{
		ray.t = 0;
		Vec3f normal = ray.hit->getNormal(ray);												// normal to the object from which the ray was casted
		ray.dir = CSampler3f::getHemisphereSample(m_pSampler->getNextSample(), normal, 1);	// sample the hemisphere in respect to the object's normal

		// ray towards point light position
		ray.t = m_maxDistance;
		ray.hit = nullptr;

		float cosN = ray.dir.dot(normal);													// angle between the object's normal and sample ray
		if (cosN > 0)	return m_intensity / cosN;
		else			return std::nullopt;
	}
}