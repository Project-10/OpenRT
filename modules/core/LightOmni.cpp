#include "LightOmni.h"
#include "Ray.h"

namespace rt {
	std::optional<Vec3f> CLightOmni::illuminate(Ray& ray) const
	{
		// shadow ray towards point light position
		ray.dir	= m_org - ray.org;
		ray.t	= norm(ray.dir);
		ray.dir = normalize(ray.dir);
		ray.hit = nullptr;

		return getIntensity() * (1 / (ray.t * ray.t));
	}
}