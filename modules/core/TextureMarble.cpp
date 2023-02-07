//  Created by Mahmoud El Bergui on 21.04.22.

#include "TextureMarble.h"
#include "PerlinNoise.h"
#include "Ray.h"

namespace rt{
	Vec3f CTextureMarble::getTexel(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hit
			? ray.hit->wcs2ocs(ray.hitPoint())							// Hitpoint in OCS
			: Vec3f(2 * ray.ndc[0] - 1, 2 * ray.ndc[1] - 1, 0);			// or NDC for background

		const Vec3f dir = normalize(Vec3f(1, 1, 0));					// orintation of the stripes
		const Vec3f proj = hitPoint.mul(dir);							// projection of the hitpoint to the directional vector

		float value = m_period * static_cast<float>(sum(proj)[0]);
		//value += m_noise.eval_fbm(hitPoint, m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);	// add noise to value;

		float qx = m_pNoise->eval_fbm(hitPoint + Vec3f(0.0f, 0.0f, 0.0f));
		float qy = m_pNoise->eval_fbm(hitPoint + Vec3f(5.2f, 1.3f, 1.7f));
		float qz = m_pNoise->eval_fbm(hitPoint + Vec3f(9.2f, 8.3f, 2.8f));
		Vec3f q(qx, qy, qz);
		
		float rx = m_pNoise->eval_fbm(hitPoint + 4 * q + Vec3f(1.7f, 9.2f, 3.4f));
		float ry = m_pNoise->eval_fbm(hitPoint + 4 * q + Vec3f(8.3f, 2.8f, 1.7f));
		float rz = m_pNoise->eval_fbm(hitPoint + 4 * q + Vec3f(4.2f, 2.3f, 9.4f));
		Vec3f r(rx, ry, rz);
		
		value += m_pNoise->eval_fbm(hitPoint + 4 * r);

		value = 0.5f + 0.5f * sinf(value);
		//value = abs(sinf(value));
		
		return m_gradient.getColor(value);
	}
}
