#include "TextureStripes.h"

namespace rt{
	Vec3f CTextureStripes::getTexel(const Vec3f& uvw) const
	{
		float u = uvw.val[0];
		float v = uvw.val[1];
		float w = uvw.val[2];

		float xSine = sinf(m_periods * u);
		float zSine = cosf(m_periods * v);
		float yCos  = sinf(m_periods * w);
		float intensity = (1 + xSine) / 2;
    
		return (intensity > 0.5) ? Vec3f(0, 0, 1) : Vec3f(1, 1 ,1);
	}
}
