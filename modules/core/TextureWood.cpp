//
//  TextureWood.cpp
//  Demo_AreaLight
//
//  Created by Mahmoud El Bergui on 21.04.22.
//

#include "TextureWood.h"
#include "PerlinNoise.h"


namespace rt {

	// Constuctor
	//CTextureWood::CTextureWood(float period) 
	//	: m_period(period)
	//	, m_gradient(RGB(164, 116, 73), RGB(86, 47, 14))	// early and old wood colors
	//{}

	// TODO: does the constants in the arguments of the noise function depend on the size of the geometry. 
	// Should thay be dependant on m_period as well to give user a possiblity to fine-tune the texture?
	Vec3f CTextureWood::getTexel(const Vec3f& uvw) const
	{
		 //Getting coordinate info
		 float u = uvw.val[0];
		 float v = uvw.val[1];
		 float w = uvw.val[2];
     
    
		 //float noise0 = (1 + CPerlinNoise::noise(0.45f * uvw)) / 2;
		 float noise1 = 1 + CPerlinNoise::noise(m_period * uvw.mul(Vec3f(0.2f, 0.2f, 0.01f)));		// This noise function call puts noise on the rings to give wood the natural felling
		 float noise2 = 1 + CPerlinNoise::noise(m_period * 5.0f * uvw);	// This noise function call gives wood roughness to texture

		 // Rings texture distorted (with added) noise
		 float value = m_period * sqrtf(v * v + u * u) + 1.5f * noise1 + 0.02f * noise2;

		 
		 return m_gradient.getColor(fmodf(value, 1));
	}
}
