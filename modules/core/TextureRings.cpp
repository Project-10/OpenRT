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
		float value = m_period * sqrtf(w * w + u * u);

		return static_cast<int>(value) % 2 == 0 ? Vec3f(0, 0, 1) : Vec3f::all(1);
	}

}



