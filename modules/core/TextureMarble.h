//  Created by Mahmoud El Bergui on 21.04.22.

#pragma once

#include "Texture.h"
#include "Gradient.h"

namespace rt {
	class CTextureMarble : public CTexture {
	public:
		/**  
		 * @brief Marble texture contructor
		 * @param octaves of noise octaves(layers)
		 * @param frequency frequency of the noise
		 * @param amplitude amplitude of the noise
		 * @param lacunarity lacunarity value(Determines how finer the next octaves should be) Lacunarity>1
		 * @param persistence persistence value(Controls how fast the next octave will die out) 0<Persistence<1
		 * @param weird Boolean generating a different type of textures
 		 */
		DllExport CTextureMarble(const CGradient& gradient, float period = 2.0f, int octave = 6, float frequency = 0.24f, float amplitude = 2.3f, float lacunarity = 2.5f, float persistence = 0.35f , bool weird = false) 
			: m_gradient(gradient)
			, m_period(period)
			, m_octaves(octave)
			, m_frequency(frequency)
			, m_amplitude(amplitude)
			, m_lacunarity(lacunarity)
			, m_persistence(persistence)
			, m_weird(weird) 
		{}
		DllExport virtual ~CTextureMarble(void) = default;
     
		/**  
		 * @brief Returns the texture element with coordinates \b (uvw)
		 * @param uv The textel coordinates in World space
		 * @return The texture elment (color)
		 */
		DllExport Vec3f getTexel(const Vec3f &uvw) const override;
     
		/**   
		 * @brief Checks if we are dealing with procedural textiures
		 */
		DllExport bool isProcedural(void) const override { return true; }
    
     
	private:
		CGradient	m_gradient;		///< The color gradient for the wood
		float		m_period;		///< The period of the noise
		int			m_octaves;		///< The noise octaves
		float		m_frequency;	///< Frequency of the noise
		float		m_amplitude;	///< Noise amplitude
		float		m_lacunarity;	///< Noise lacunarity
		float		m_persistence;	///< Noise persistence
		bool		m_weird;		///< boolean to enable a new type of marble(please look at the TextureMarble.cpp)
	};
}
