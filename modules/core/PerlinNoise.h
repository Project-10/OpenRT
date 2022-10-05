
//  Created by Mahmoud El Bergui on 26.04.22.
#pragma once

#include "types.h"

namespace rt{
	/**
	 * @brief Perlin Noise class
	 * @details Reference: https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise
	 * @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	 */
	class CPerlinNoise {
	public:
		/**
		* @brief Constructor
		* @param seed The seed for the random number generator, which modulates the resulting noise
		*/
		DllExport CPerlinNoise(unsigned int seed);
		DllExport ~CPerlinNoise(void) = default;
     
		/**  
		 * @brief Generate 3D noise
		 * @param p Coordinate of 3d point value
		 * @return A pseudo-random value in range [-1; 1]
		 */
		DllExport float eval(const Point3f& p) const;
     
    
	private:
		/**
		* @brief Hash function, which returns a value from permutation vector based on arguments
		*/
		unsigned int hash(int x, int y, int z) const;


	private:
		std::array<Vec3f, 256>			m_aGradients;			///< The array of gradients
		std::array<unsigned int, 256>	m_aPermutationVector;	///< The permutation vector
		
	};
}
