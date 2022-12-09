#include "TextureRings.h"
#include "Ray.h"

namespace rt{
	/// @todo Play with the direction of the rings
	Vec3f CTextureRings::getTexel(const Ray& ray) const
	{
		Vec3f uvw = ray.hit->wcs2ocs(ray.hitPoint());				// Hitpoint in OCS

		const Vec3f period = m_period * Vec3f(1, 1, 0);				// Orintation of the rings
		
		// Difference between point and center of the shape
		float value = static_cast<float>(norm(uvw.mul(period)));

		return static_cast<int>(value) % 2 == 0 ? RGB(255, 0, 0) : RGB(255, 255, 255);
	}
}
