
//  Created by Mahmoud El Bergui on 26.04.22.
//Reference: https://cs.nyu.edu/~perlin/noise/

#include "types.h"
#include"math.h"
#include"stdlib.h"
#include"PerlinNoise.h"


namespace rt{
	namespace
     {
		/**  @Brief Smoothstep function
			 @param val value that we want to use the smoothstep on
			 @return smoothstep value
		*/
		double fade(double val)
		{
			return val * val * val * (val * (val * 6 - 15) + 10);
		}

		/**  @Brief Interpolation function
			 @param val value that we want to interpolated
			 @param a first border of the interpolation
			 @param b second border of the interpolation
			 @return interpolated value
		*/
		float lerp(float val, float a, float b)
		{
			return a + val * (b - a);
		}

		//Calculate the gradiant
		/**@Brief Gradient function
			 @param hash hashing value
			 @param x x-coordinate value
			 @param y y-coordinate value
			 @param z z-coordinate value
		*/
		double grad(int hash, double x, double y, double z)
		{
			//Converts the lower 4 bits into 12 gradient directions
			int h = hash & 15;

			double u = h < 8 ? x : y;
			double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}
     }
	 
	 
	 CPerlinNoise::CPerlinNoise() 
	 {
		//Permutation vector with reference values used by Perlin
		m_p = {
			151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
			8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
			35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
			134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
			55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
			18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
			250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
			189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
			43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
			97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
			107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
			138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
		};
		//Duplicaiton of reference vector
		//p.insert(position, Number of times, value)
		m_p.insert(m_p.end(), m_p.begin(), m_p.end());
     }
     

     float CPerlinNoise::noise(const Point3f& p) const
	 {
          //Find the unit cube that contains the point
          int X  = (int) floor(p.x) & 255;
          int Y = (int) floor(p.y) & 255;
          int Z = (int) floor(p.z) & 255;
          
          // Find the coordinates of the cube containing the points
          float x = p.x - floor(p.x);
          float y = p.y - floor(p.y);
          float z = p.z - floor(p.z);
          
          //Compute the smoothstep function for x,y,z coordinates
          double u = fade(x);
          double v = fade(y);
          double w = fade(z);
          
          //Hash coordinates of 8 cube corners
          int A = m_p[X] + Y;
          int AA = m_p[A] + Z;
          int AB = m_p[A + 1] + Z;
          int B = m_p[X + 1] + Y;
          int BA = m_p[B] + Z;
          int BB = m_p[B + 1] + Z;
          
          //Interpolation
          return lerp(w ,
                         lerp(v,
                              lerp(u, grad(m_p[AA], x, y, z), grad(m_p[BA], x-1, y, z)),
                              lerp(u, grad(m_p[AB], x, y-1, z), grad(m_p[BB], x-1, y-1, z))),
                         lerp(v ,
                              lerp(u, grad(m_p[AA+1], x, y, z-1), grad(m_p[BA+1], x-1, y, z-1)),
                              lerp(u, grad(m_p[AB+1], x, y-1, z-1), grad(m_p[BB+1], x-1, y-1, z-1)))
                          );
     }
     
     float CPerlinNoise::turbulence(const Point3f& p, int octaves, float f, float amplitude, float lacunarity ,float persistence) const 
	 {
          float res = 0;
          for (int i = 1; i <= octaves; i++) {
               res += amplitude * noise(f * p);
               amplitude *= persistence;
               f *= lacunarity;
          }
          return res;
     }

}
