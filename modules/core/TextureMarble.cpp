//  Created by Mahmoud El Bergui on 21.04.22.

#include "TextureMarble.h"
#include "PerlinNoise.h"
#include "Ray.h"

namespace rt{
	Vec3f CTextureMarble::getTexel(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hit->wcs2ocs(ray.hitPoint());	// hitpoint in OCS

		const Vec3f dir = normalize(Vec3f(1, 1, 0));					// orintation of the stripes
		const Vec3f proj = hitPoint.mul(dir);							// projection of the hitpoint to the directional vector

		float value = m_period * static_cast<float>(sum(proj)[0]);
		//value += m_noise.eval_fbm(hitPoint, m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);	// add noise to value;

		float qx = m_noise.eval_fbm(hitPoint + Vec3f(0.0f, 0.0f, 0.0f), m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);
		float qy = m_noise.eval_fbm(hitPoint + Vec3f(5.2f, 1.3f, 1.7f), m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);
		float qz = m_noise.eval_fbm(hitPoint + Vec3f(9.2f, 8.3f, 2.8f), m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);
		Vec3f q(qx, qy, qz);
		
		float rx = m_noise.eval_fbm(hitPoint + 4 * q + Vec3f(1.7f, 9.2f, 3.4f), m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);
		float ry = m_noise.eval_fbm(hitPoint + 4 * q + Vec3f(8.3f, 2.8f, 1.7f), m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);
		float rz = m_noise.eval_fbm(hitPoint + 4 * q + Vec3f(4.2f, 2.3f, 9.4f), m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);
		Vec3f r(rx, ry, rz);
		
		value += m_noise.eval_fbm(hitPoint + 4 * r, m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity);

		value = 0.5f + 0.5f * sinf(value);
		//value = abs(sinf(value));
		
		return m_gradient.getColor(value);
	}
}
