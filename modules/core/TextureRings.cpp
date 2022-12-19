#include "TextureRings.h"
#include "Ray.h"

namespace rt{
	/// @todo Play with the direction of the rings
	Vec3f CTextureRings::getTexel(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hit->wcs2ocs(ray.hitPoint());			// Hitpoint in OCS

		const Vec3f dir = Vec3f(1, 1, 0);							// Orintation of the rings
		const Vec3f proj = hitPoint.mul(dir);						// Projection of the hitpoint to the directional vector
		
		// Difference between point and center of the shape
		float value = m_period * static_cast<float>(norm(proj));

		value = 0.5f * (1 + sinf(value));
		
		return m_gradient.getColor(value);
	}
}
