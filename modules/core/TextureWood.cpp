//
//  TextureWood.cpp
//  Demo_AreaLight
//
//  Created by Mahmoud El Bergui on 21.04.22.
//

#include "TextureWood.h"
#include "PerlinNoise.h"
#include "CGradient.h"


namespace rt {

	// Constuctor
	CTextureWood::CTextureWood(float period) 
		: m_period(period)
		, m_gradient(RGB(164, 116, 73), RGB(86, 47, 14))	// early and old wood colors
	{}

	// TODO: does the constants in the arguments of the noise function depend on the size of the geometry. 
	// Should thay be dependant on m_period as well to give user a possiblity to fine-tune the texture?
	Vec3f CTextureWood::getTexel(const Vec3f& uvw) const
	{
		 //Getting coordinate info
		 float u = uvw.val[0];
		 float v = uvw.val[1];
		 float w = uvw.val[2];
     
		 //Increasing the alpha increase the noise effect (>1 destroyes the rings)
		 //fx,fy,fz increase -> more stiff peaks (value around 0.5 gives a more real-like wood texture)
		 //Having a small difference between fx,fy, and fz gives more realism
     
		 //float noise0 = (1 + CPerlinNoise::noise(0.45f * uvw)) / 2;
		 float noise1 = 1 + CPerlinNoise::noise(Point3f(m_period / 2.5f * u, m_period / 2.5f * v ,m_period / 2.5f * w));	// This noise function call puts noise on the rings to give wood the natural felling
		 float noise2 = 1 + CPerlinNoise::noise(m_period * 10.0f * uvw);									// This noise function call gives wood roughness to texture

		 // Rings texture distorted (with added) noise
		 float value = m_period * sqrtf(w * w + u * u) + 0.4f * noise1 + 0.5f * noise2;

		 
		 return m_gradient.getColor(fmodf(value, 1));
	}
}
