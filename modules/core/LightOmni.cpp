#include "LightOmni.h"
#include "Ray.h"

namespace rt {
	std::optional<Vec3f> CLightOmni::illuminate(Ray& ray)
	{
		// ray towards point light position
		ray.dir	= m_org - ray.org;
		ray.t	= norm(ray.dir);
		ray.dir = normalize(ray.dir);
		ray.hit = nullptr;
		double attenuation = 1 / (ray.t * ray.t);
		return attenuation * m_intensity;
	}
}