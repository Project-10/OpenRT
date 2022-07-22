//  Created by Mahmoud El Bergui on 21.04.22.

#include "TextureMarble.h"
#include "PerlinNoise.h"

namespace rt{
	namespace {
		/**
		 @Brief Mixes between two colors
		 @param C0 first color
		 @param C1 second color
		 @param f weight coefficient
		 @return returns the mixed color
		 */
		Vec3f mix(const Vec3f& C0, const Vec3f& C1, float f)
		{
			 return (1 - f) * C0 + f * C1;
		}

		/**
		 @Brief Smoothstep function
		 @param val value that we want to use the smoothstep on
		 @return smoothstep value
		 */
		float smoothstep(float val)
		{
			 return val * val * val * (val * (val * 6 - 15) + 10);
		}

		/**
		 @Brief Step function
		 @param x value to use the step on
		 @param a step parameter
		 */
		float stepFunc(float x, float a)
		{
			 return (float)(x > a);
		}

	}

	Vec3f CTextureMarble::getTexel(const Vec3f& uvw) const
	{
		 //Getting coordinate info
		 float u = uvw.val[0];
		 float v = uvw.val[1];
		 float w = uvw.val[2];
     
		 float t = CPerlinNoise::turbulence(uvw , m_octaves, m_frequency , m_amplitude , m_lacunarity, m_persistence);
		 Vec3f color;
		 if (m_weird) {
			  t = t - floor(t);
			  color = m_gradient.getColor(abs(sinf(m_period*t)));
          
			  Vec3f white = Vec3f::all(1);
			  color = mix(color, white, 0.1f);
		 }
		 else{
			  //color = marbleMap(abs(sin(0.5*u + t)));
			  color = m_gradient.getColor(abs(sinf(m_period*u + 1*t)));
			  //        unable for more control
			  color.val[0] = smoothstep(color.val[0] * 1.15f);
			  color.val[1] = smoothstep(color.val[1] * 1.15f);
			  color.val[2] = smoothstep(color.val[2] * 1.15f);
          
			  //Vec3f color = marbleMap(abs(t));
			  Vec3f white = Vec3f::all(1);
			  color = mix(color, white, 0.1f);
          
			  if((stepFunc(color.val[0], 1) == 1) && (stepFunc(color.val[1], 1) == 1) && (stepFunc(color.val[2], 1) == 1))
				   //vcolor = Vec3f(0.203, 0.2617 , 0.2422);
				   //color = Vec3f(1,1,1);
				   color = Vec3f(0.6f, 0.53f, 0.467f);
		 }
		 return color;
	}
}
