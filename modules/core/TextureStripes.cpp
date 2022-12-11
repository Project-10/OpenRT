#include "TextureStripes.h"
#include "Ray.h"

namespace rt{
	/// @todo Play with the direction of the stripes
	Vec3f CTextureStripes::getTexel(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hit->wcs2ocs(ray.hitPoint());				// Hitpoint in OCS
		
		// Full form
		const Vec3f dir = normalize(Vec3f(1, 1, 0));					// orintation of the stripes
		const Vec3f proj = hitPoint.mul(dir);							// projection of the hitpoint to the directional vector
		
		float value = m_period * static_cast<float>(sum(proj)[0]);

		//float value = m_period * hitPoint[0];	// Short form
		if (value < 0) value -= 1;				// Making stripes to be odd function (0.1 -> even, -0.1 -> odd)

		return static_cast<int>(value) % 2 == 0 ? RGB(255, 0, 0) : RGB(255, 255, 255);
	}
}
