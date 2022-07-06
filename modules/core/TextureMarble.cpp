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
			@Brief Function to interpolate between marble pillar colors
			@param value value that we want to map
			@return mapped color
			*/
			Vec3f marbleMap(float value)
			{
				Vec3f white =  RGB(255, 255, 255);
				Vec3f blue  =  RGB(119, 135, 153);
				return mix(blue, white, value);
			}

			/**
			@Brief Smoothstep function
			@param val value that we want to use the smoothstep on
			@return smoothstep value
			*/
			double smoothstep(float val)
			{
				return val * val * val * (val * (val * 6 - 15) + 10);
			}

			/**
			@Brief Step function
			@param x value to use the step on
			@param a step parameter
			*/
			float step(float x, float a)
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
  
		CPerlinNoise pn;
		double t =  pn.turbulence(uvw , m_octaves, m_frequency , m_amplitude , m_lacunarity, m_persistence);
		Vec3f color;
		if (m_weird ==  true) {
			t = t - floor(t);
			color = marbleMap(abs(sin(t)));
		}
		else
			//color = marbleMap(abs(sin(0.5*u + t)));
			color = marbleMap(abs(sin(0.5*u + 1.2*t)));
               
		//unable for more control
		//color.val[0] = smoothstep(color.val[0]);
		//color.val[1] = smoothstep(color.val[1]);
		//color.val[2] = smoothstep(color.val[2]);

		//Vec3f color = marbleMap(abs(t));
		Vec3f white = Vec3f::all(1);
		return mix(color, white, 0.2);
	}
}
