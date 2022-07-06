
//  Created by Mahmoud El Bergui on 26.04.22.
#pragma once

#include <stdio.h>
#include <vector>

namespace rt{

     class CPerlinNoise {
     public:
		/**  @Brief Construct Perlin Noise using values of the permutation vector
		*/
		DllExport CPerlinNoise();

		/**  
		 * @brief Generate 3D noise
		 * @param p coordinate of 3d point value
		 */
		DllExport float noise(const Point3f& p) const;
          
		/**  @Brief Generate 3D turbulence
		@param p coordinate of 3d point value
		@param octaves of noise octaves(layers)
		@param f frequency of the noise
		@param amplitude amplitude of the noise
		@param lacunarity lacunarity value(Determines how finer the next octaves should be) Lacunarity>1
		@param persistence persistence value(Controls how fast the next octave will die out) 0<Persistence<1
		@return turbulence value
		*/
		DllExport float turbulence(const Point3f& p, int octaves ,float f, float amplitude, float lacunarity, float persistence) const;


	private:
		std::vector<int> m_p;	///< The permutation vector
	};
}
