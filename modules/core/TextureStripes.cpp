#include "TextureStripes.h"
#include "Ray.h"

namespace rt{
	/// @todo Play with the direction of the stripes
	Vec3f CTextureStripes::getTexel(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hit
			? ray.hit->wcs2ocs(ray.hitPoint())						// Hitpoint in OCS
			: Vec3f(2 * ray.ndc[0] - 1, 2 * ray.ndc[1] - 1, 0);		// or NDC for background
		
		// Full form
		const Vec3f dir = normalize(Vec3f(1, 0, 0));					// Orintation of the stripes
		const Vec3f proj = hitPoint.mul(dir);							// Projection of the hitpoint to the directional vector
		
		float value = m_period * static_cast<float>(sum(proj)[0]);

		if (m_pNoise)
			value += m_pNoise->eval_fbm(hitPoint);

		value = 0.5f * (1 + sinf(value * Pif));
		return m_gradient.getColor(value);
	}
}
