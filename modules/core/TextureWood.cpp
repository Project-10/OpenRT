//  Created by Mahmoud El Bergui on 21.04.22.

#include "TextureWood.h"
#include "Ray.h"

namespace rt {
	Vec3f CTextureWood::getTexel(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hit->wcs2ocs(ray.hitPoint());			// Hitpoint in OCS
		
		const Vec3f period = m_period * Vec3f(1, 1, 0);				// Orintation of the rings

		// Difference between point and center of the shape
		float value = static_cast<float>(norm(hitPoint.mul(period)));
		
		float amplitude = m_amplitude;
		float frequency = m_frequency;
		// Fractional Brownian Motion function
		for (size_t i = 0; i < 2; i++) {
			value += amplitude * (1.0f + m_noise.eval(hitPoint.mul(frequency * Vec3f(1.0f, 1.0f, 0.05f))));
			amplitude *= 0.5f;
			frequency *= 2.0f;
		}

		value = fmodf(value, 1.0f);
		return m_gradient.getColor(value);
	}
}
