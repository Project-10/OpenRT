//  Created by Mahmoud El Bergui on 21.04.22.
#pragma once

#include "Texture.h"
#include "Gradient.h"
#include "PerlinNoise.h"

namespace rt {
	class CTextureMarble : public CTexture {
	public:
		/**  
		 * @brief Marble texture contructor
		 * @param gradient Wood color
		 * @param seed The seed for the random number generator, allows to generate unique textures
		 * @param period The number of annual rings per one unit of WCS
		 * @param octaves of noise octaves(layers)
		 * @param frequency frequency of the noise
		 * @param amplitude amplitude of the noise
		 * @param lacunarity lacunarity value(Determines how finer the next octaves should be) Lacunarity>1
		 * @param persistence persistence value(Controls how fast the next octave will die out) 0<Persistence<1
		 * @param weird Boolean generating a different type of textures
 		 */
		DllExport CTextureMarble(const CGradient& gradient, unsigned int seed, float period = 2.0f, int octave = 6, float frequency = 0.24f, float amplitude = 2.3f, float lacunarity = 2.5f, float persistence = 0.35f , bool weird = false)
			: m_gradient(gradient)
			, m_noise(seed)
			, m_period(period)
			, m_octaves(octave)
			, m_frequency(frequency)
			, m_amplitude(amplitude)
			, m_lacunarity(lacunarity)
			, m_persistence(persistence)
			, m_weird(weird) 
		{}
		DllExport virtual ~CTextureMarble(void) = default;
     
		DllExport Vec3f	getTexel(const Vec3f &uvw) const override;
		DllExport bool	isProcedural(void) const override { return true; }
    
     
	private:
		CGradient		m_gradient;		///< The color gradient for the wood
		CPerlinNoise	m_noise;		///< The Perlin Noise
		float			m_period;		///< The period of the noise
		int				m_octaves;		///< The noise octaves
		float			m_frequency;	///< Frequency of the noise
		float			m_amplitude;	///< Noise amplitude
		float			m_lacunarity;	///< Noise lacunarity
		float			m_persistence;	///< Noise persistence
		bool			m_weird;		///< boolean to enable a new type of marble(please look at the TextureMarble.cpp)
	};
}
