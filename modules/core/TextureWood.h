//  Created by Mahmoud El Bergui on 21.04.22.
#pragma once

#include "Texture.h"
#include "PerlinNoise.h"
#include "Gradient.h"

namespace rt {
	/**
	 * @brief Wood procedural texture class
	 * @ingroup moduleTexture
	 * @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	 */
	class CTextureWood : public CTexture {
	public:
		/**
		 * @brief Constructor
		 * @param gradient Wood color
		 * @param seed The seed for the random number generator, allows to generate unique textures
		 * @param period The number of annual rings per one unit of WCS
		 * @param alpha_lf The power of the low-frequency Perlin noise to the wood texture
		 * @param alpha_hf The power of the high-frequency Perlin noise to the wood texture
		 */
		DllExport CTextureWood(const CGradient& gradient, unsigned int seed, float period = 1.0f, float alpha_lf = 1.5f, float alpha_hf = 0.1f);
		DllExport virtual ~CTextureWood(void) = default;
     
		DllExport Vec3f	getTexel(const Ray& ray) const override;
     
     
	private:
		CGradient		m_gradient;		///< The color gradient for the wood
		CPerlinNoise	m_noise;		///< The Perlin Noise
		Vec3f			m_period;		///< The number of annual rings per one unit of WCS
		Vec3f			m_period_lf;	///< Parameter, which defines the size of the low-frequency Perlin noise
		float			m_alpha_lf;		///< The power of the low-frequency Perlin noise to the wood texture
		Vec3f			m_period_hf;	///< Parameter, which defines the size of the high-frequency Perlin noise
		float			m_alpha_hf;		///< The power of the high-frequency Perlin noise to the wood texture
	};
}
