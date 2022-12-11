//  Created by Mahmoud El Bergui on 21.04.22.
#pragma once

#include "Texture.h"
#include "Gradient.h"
#include "PerlinNoise.h"

namespace rt {
	/**
	* @brief Marble procedural texture class
	* @details This class is based on the stripes (@ref CTextureStripes) class
	* @ingroup moduleTexture
	* @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	*/
	class CTextureMarble : public CTexture {
	public:
		/**  
		 * @brief Marble texture contructor
		 * @param gradient Marble color
		 * @param seed The seed for the random number generator, allows to generate unique textures
		 * @param period The number of stripes per 1 unit of WCS
		 * @param amplitude Amplitude of the noise.
		 * @param frequency The frequency determines a scaling value to be applied to point \p p before calling the noise function.
		 * @param numOctaves The number of octaves determines how many times the noise function is called.
		 * @param gain Gain is a value in the range (0; 1) that controls how quickly the later octaves "die out". Something around \b 0.5 is pretty conventional here.
		 * @param lacunarity Lacunarity is a value greater than 1 that controls how much finer a scale each subsequent octave should use. Something around \b 2.0 is a conventional choice.
 		 */
		DllExport CTextureMarble(const CGradient& gradient, unsigned int seed, float period, float amplitude = 1.0f, float frequency = 1.0f, size_t numOctaves = 1, float gain = 0.5f, float lacunarity = 2.0f)
			: m_gradient(gradient)
			, m_noise(seed)
			, m_period(period)
			, m_amplitude(amplitude)
			, m_frequency(frequency)
			, m_numOctaves(numOctaves)
			, m_gain(gain)
			, m_lacunarity(lacunarity)
		{}
		DllExport virtual ~CTextureMarble(void) = default;
     
		DllExport Vec3f	getTexel(const Ray& ray) const override;
    
     
	private:
		CGradient		m_gradient;		///< The color gradient for the wood
		CPerlinNoise	m_noise;		///< The Perlin Noise
		float			m_period;		///< The period of the noise
		
		float			m_amplitude;	///< Amplitude of the noise
		float			m_frequency;	///< Frequency of the noise
		size_t			m_numOctaves;	///< Noise octaves
		float			m_gain;			///< Noise gain
		float			m_lacunarity;	///< Noise lacunarity
	};
}
