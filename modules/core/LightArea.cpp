#include "LightArea.h"
#include "Ray.h"
#include "random.h";

namespace rt {
	std::optional<Vec3f> CLightArea::illuminate(Ray& ray) const
	{
		Vec2f sample = m_pSampler ? m_pSampler->getNextSample() : Vec2f(random::U<float>(), random::U<float>());
		Vec3f org = m_org + sample.val[0] * m_edge1 + sample.val[1] * m_edge2;	// a random point on the surface of the light source

		// ray towards point light position
		ray.dir = org - ray.org;
		ray.t = norm(ray.dir);
		ray.dir = normalize(ray.dir);
		ray.hit = nullptr;

		double cosN = -ray.dir.dot(m_normal);
		if (cosN > 0)	return getIntensity() * (m_area * cosN / (ray.t * ray.t));
		else			return std::nullopt;
	}
}