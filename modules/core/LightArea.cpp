#include "LightArea.h"
#include "Ray.h"
#include "random.h"

namespace rt {
	std::optional<Vec3f> CLightArea::illuminate(Ray& shadowray, const Vec3f& point, const Vec3f&, size_t s) const
	{
		Vec2f sample = m_pSampler ? m_pSampler->getNextSample(s) : Vec2f(random::U<float>(), random::U<float>());
		Vec3f org = m_org + sample.val[0] * m_edge1 + sample.val[1] * m_edge2;	// a random point on the surface of the light source

		// ray towards point light position
		shadowray		= Ray(point);
		shadowray.dir	= org - shadowray.org;
		shadowray.t		= norm(shadowray.dir);
		shadowray.dir	= normalize(shadowray.dir);

		double cosN = -shadowray.dir.dot(m_normal);
		if (cosN > 0)	return getIntensity() * (m_area * cosN / (shadowray.t * shadowray.t));
		else			return std::nullopt;
	}
}
