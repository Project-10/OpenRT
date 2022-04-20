#include "TextureStripes.h"

namespace rt{

	Vec3f CTextureStripes::getTexel(const Vec3f& uvw) const
	{
		float u = uvw.val[0];
		float v = uvw.val[1];
		float w = uvw.val[2];

		float periods= 5;
		float xSine = sinf(periods * u);
		float zSine = cosf(periods * v);
		float yCos  = sinf(periods * w);
		float intensity = (1 + xSine) / 2;
    
		std::cout << intensity << std::endl;
    
		return (intensity > 0.5) ? Vec3f(0, 0, 255) : Vec3f(255, 255 ,255);
	}
}


