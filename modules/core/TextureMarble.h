//  Created by Mahmoud El Bergui on 21.04.22.
//

#pragma once
#include"Texture.h"


namespace rt {
     class CTextureMarble : public CTexture{
     
          public:
     /**  @brief Marble texture contructor
          @param octaves of noise octaves(layers)
          @param frequency frequency of the noise
          @param amplitude amplitude of the noise
          @param lacunarity lacunarity value(Determines how finer the next octaves should be) Lacunarity>1
          @param persistence persistence value(Controls how fast the next octave will die out) 0<Persistence<1
          @param weird Boolean generating a different type of textures
      */
     DllExport CTextureMarble(float period = 2.0, float octave = 6, float frequency = 0.24, float amplitude = 2.3, float lacunarity = 2.5, float persistence = 0.35 , bool weird = false) : m_period(period), m_octaves(octave), m_frequency (frequency), m_amplitude(amplitude), m_lacunarity(lacunarity), m_persistence(persistence) , m_weird(weird) {};
     DllExport virtual ~CTextureMarble(void) = default;
    
     /**  @brief Returns the texture element with coordinates \b (uvw)
      *   @param uv The textel coordinates in World space
      *   @return The texture elment (color)
      */
     DllExport Vec3f getTexel(const Vec3f &uvw) const override;
     
    /**   @Brief Checks if we are dealing with procedural textiures
    */
     DllExport bool isProcedural(void) const override { return true; }
     
     /**  @Brief Function to interpolate between marble pillar colors
          @param value value that we want to map
          @return mapped color
     */
     DllExport Vec3f marbleMap(float value) const;
     
     /**  @Brief Smoothstep function
          @param val value that we want to use the smoothstep on
          @return smoothstep value
     */
     DllExport double smoothstep(float val) const;
     
     /**  @Brief Mixes between two colors
          @param C0 first color
          @param C1 second color
          @param f weight coefficient
          @return returns the mixed color */
     DllExport Vec3f mix(Vec3f& C0, Vec3f& C1, float f ) const;
     
     /**  @Brief Step function
          @param x value to use the step on
          @param a step parameter*/
     DllExport float step(float x , float a) const;


	private:
		float m_period;///<The period of the noise
          int m_octaves;///<The noise octaves
          float m_frequency;///<Frequency of the noise
          float m_amplitude;///<Noise amplitude
          float m_lacunarity;///<Noise lacunarity
          float m_persistence;///<Noise persistence
          bool m_weird;///< boolean to enable a new type of marble(please look at the TextureMarble.cpp)
          
  };
}
