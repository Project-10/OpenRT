
//  Created by Mahmoud El Bergui on 26.04.22.
#pragma once

#include "types.h"

namespace rt{
	/**
	 * @brief Perlin Noise class
	 * @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	 */
	class CPerlinNoise {
	public:
		/**
		 * @brief Constructor
		 * @param seed The seed for the random number generator, which modulates the resulting noise
		 * @param amplitude Amplitude of the noise (\f$A\f$).
		 * @param frequency The frequency determines a scaling value to be applied to point \p p before calling the noise function.
		 * @param numOctaves The number of octaves (\f$N\f$) determines how many times the noise function is called. If \p numOctaves = \b 0, the result of this method will be zero as well.
		 * @param gain Gain is a value in the range (0; 1) that controls how quickly the later octaves "die out". Something around \b 0.5 is pretty conventional here.
		 * @param lacunarity Lacunarity is a value greater than 1 that controls how much finer a scale each subsequent octave should use. Something around \b 2.0 is a conventional choice.
		 */
		DllExport CPerlinNoise(unsigned int seed, float amplitude = 1.0f, float frequency = 1.0f, size_t numOctaves = 1, float gain = 0.5f, float lacunarity = 2.0f);
		DllExport ~CPerlinNoise(void) = default;
     
		/**  
		 * @brief Generate 3D noise
		 * @details Reference: <a href="https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise" target="_blank">Perlin Noise: Part 2</a>.
		 * @param p Coordinate of 3d point value
		 * @return A pseudo-random value in range [-1; 1]
		 */
		DllExport float eval(const Point3f& p) const;
		/**
		 * @brief Fractional Brownian Motion (FBM) noise turbulence function
		 * @details This method calculates a superposition of the Perlin noise functions as follows: \f[ \sum^{N-1}_{i=0} A\cdot gain^i \cdot\mathcal{N}(frequency\cdot lacunarity^i \cdot p)  \f]
		 * By other words, this method layers Perlin noise into something like FBM. 
		 * If called as CPerlinNoise::eval_fbm(\p p, \p 1, \p 1, \p 1) this method is equvalent to method CPerlinNoise::eval(\p p).
		 * @see <a href="https://thebookofshaders.com/13" target="_blank">Fractal Brownian Motion</a>.
		 * @param p Coordinate of 3d point value.
		 * @param amplitude Amplitude of the noise (\f$A\f$).
		 * @param frequency The frequency determines a scaling value to be applied to point \p p before calling the noise function.
		 * @param numOctaves The number of octaves (\f$N\f$) determines how many times the noise function is called. If \p numOctaves = \b 0, the result of this method will be zero as well.
		 * @param gain Gain is a value in the range (0; 1) that controls how quickly the later octaves "die out". Something around \b 0.5 is pretty conventional here.
		 * @param lacunarity Lacunarity is a value greater than 1 that controls how much finer a scale each subsequent octave should use. Something around \b 2.0 is a conventional choice.
		 * @return A pseudo-random value
		 */
		DllExport float eval_fbm(const Point3f& p, float amplitude, float frequency, size_t numOctaves, float gain = 0.5f, float lacunarity = 2.0f) const;

		/**
		 * @brief Fractional Brownian Motion (FBM) noise turbulence function
		 * @param p Coordinate of 3d point value.
		 * @return A pseudo-random value
		 */
		DllExport float eval_fbm(const Point3f& p) const { return eval_fbm(p, m_amplitude, m_frequency, m_numOctaves, m_gain, m_lacunarity); }
    

	private:
		/**
		* @brief Hash function, which returns a value from permutation vector based on arguments
		*/
		unsigned int hash(int x, int y, int z) const;


	private:
		std::array<Vec3f, 256>			m_aGradients;			///< The array of gradients
		std::array<unsigned int, 256>	m_aPermutationVector;	///< The permutation vector


	private:
		const float		m_amplitude		= 1.0f;		///<
		const float		m_frequency		= 1.0f;		///<
		const size_t	m_numOctaves	= 1;		///<
		const float		m_gain			= 0.5f;		///<
		const float		m_lacunarity	= 2.0f;		///<
	};

	using ptr_perlin_t = std::shared_ptr<CPerlinNoise>;
}
