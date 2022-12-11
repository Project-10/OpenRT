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
		 * @param amplitude Amplitude of the noise.
		 * @param frequency Frequency of the noise.
		 */
		DllExport CTextureWood(const CGradient& gradient, unsigned int seed, float period, float amplitude = 1.0f, float frequency = 1.0f)
			: m_gradient(gradient)
			, m_noise(seed)
			, m_period(period)
			, m_amplitude(amplitude)
			, m_frequency(frequency)
		{}
		DllExport virtual ~CTextureWood(void) = default;
     
		DllExport Vec3f	getTexel(const Ray& ray) const override;
     
     
	private:
		CGradient		m_gradient;		///< The color gradient for the wood
		CPerlinNoise	m_noise;		///< The Perlin Noise
		float			m_period;		///< The number of annual rings per one unit of WCS
		float			m_amplitude;	///< Amplitude of the noise
		float			m_frequency;	///< Frequency of the noise
	};
}
