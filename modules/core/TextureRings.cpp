//
//  Rings.cpp
//  Demo_AreaLight
//
//  Created by Mahmoud El Bergui on 18.04.22.
//

#include "TextureRings.h"

namespace rt{

	Vec3f CTextureRings::getTexel(const Vec3f& uvw) const
	{
		//Getting coordinate info
		float u = uvw.val[0];
		float v = uvw.val[1];
		float w = uvw.val[2];
    
		//Difference between point and center of the shape
		Vec3f lenght = uvw;
		auto factor = 10;
		float norm = sqrtf(powf(lenght[2], 2) + powf(lenght[1], 2));
		auto value = factor * norm;

		return (int) floor(value) % 2 == 0 ? Vec3f(0, 0, 255) : Vec3f(255, 255, 255);
	}

}



