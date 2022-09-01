
// Created by Mahmoud El Bergui on 26.04.22.

#include "PerlinNoise.h"

namespace rt{
	namespace {
		// Ken Perlin's smoothstep function
		float smootherstep(float x)
		{
			if (x < 0) return 0;
			if (x > 1) return 1;
			return x * x * x * (x * (x * 6 - 15) + 10);
		}

		/**
		 * @brief Interpolation function
		 * @param val value that we want to interpolated
		 * @param a first border of the interpolation
		 * @param b second border of the interpolation
		 * @return interpolated value
		 */
		float lerp(float val, float a, float b)
		{
			return a + val * (b - a);
		}

		/**
		* @brief Gradient function
		* @param hash hashing value
		* @param x x-coordinate value
		* @param y y-coordinate value
		* @param z z-coordinate value
		*/
		float grad(int hash, float x, float y, float z)
		{
			//Converts the lower 4 bits into 12 gradient directions
			int h = hash & 15;
     
			float u = h < 8 ? x : y;
			float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}
	}

	float CPerlinNoise::noise(const Point3f& p)
	{
		// Find the unit cube that contains the point
		int X = (int) floor(p.x) & 255;
		int Y = (int) floor(p.y) & 255;
		int Z = (int) floor(p.z) & 255;
     
		// Find the coordinates of the cube containing the points
		float x = p.x - floor(p.x);
		float y = p.y - floor(p.y);
		float z = p.z - floor(p.z);
     
		// Compute the smoothstep function for x,y,z coordinates
		float u = smootherstep(x);
		float v = smootherstep(y);
		float w = smootherstep(z);
     
		// Hash coordinates of 8 cube corners
		const int n = static_cast<int>(m_p.size());
		int A  = (m_p[X % n] + Y);
		int B  = (m_p[(X + 1) % n] + Y);
     
		int AA = (m_p[A % n] + Z);
		int AB = (m_p[(A + 1) % n] + Z);
		int BA = (m_p[B % n] + Z);
		int BB = (m_p[(B + 1) % n] + Z);

		// Interpolation
		float res = lerp(w ,
					lerp(v,
						lerp(u, grad(m_p[AA % n], x, y, z),   grad(m_p[BA % n], x - 1, y, z)),
						lerp(u, grad(m_p[AB % n], x, y - 1, z), grad(m_p[BB % n], x - 1, y - 1, z))
					),
					lerp(v ,
						lerp(u, grad(m_p[(AA + 1) % n], x, y, z-1),   grad(m_p[(BA + 1) % n], x - 1, y, z - 1)),
						lerp(u, grad(m_p[(AB + 1) % n], x, y - 1, z - 1), grad(m_p[(BB + 1) % n], x - 1, y - 1, z - 1))
					)
				);
	
		return res;
	}
}
