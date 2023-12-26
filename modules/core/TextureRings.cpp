#include "TextureRings.h"
#include "Ray.h"

namespace rt{
	/// @todo Play with the direction of the rings
	Vec3f CTextureRings::getTexel(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hit 
			? ray.hit->wcs2ocs(ray.hitPoint())						// Hitpoint in OCS
			: Vec3f(2 * ray.ndc[0] - 1, 2 * ray.ndc[1] - 1, 0);		// or NDC for background

		const Vec3f dir = Vec3f(1, 1, 0);							// Orintation of the rings
		const Vec3f proj = hitPoint.mul(dir);						// Projection of the hitpoint to the directional vector
		
		float value = m_period * static_cast<float>(norm(proj));

		if (m_pNoise) {
			const Vec3f proj = hitPoint.mul(dir + Vec3f::all(0.05f));
			value += m_pNoise->eval_fbm(proj);
		}

		value = fmodf(1.0f + value, 1.0f);
		
		return m_gradient.getColor(value);
	}
}
