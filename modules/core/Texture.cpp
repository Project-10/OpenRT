#include "Texture.h"
#include <math.h>

namespace rt{
	Vec3f CTexture::getTexel(const Vec2f& uv) const
	{
		float t;
		float u = modff(uv.val[0] + Epsilon, &t);
		float v = modff(uv.val[1] + Epsilon, &t);

		if (u < 0) u += 1;
		if (v < 0) v += 1;
		
		if (empty()) {
			bool ax = u < 0.5f ? true : false;
			bool ay = v > 0.5f ? true : false;
		
			bool c = ax ^ ay;
			return c ? Vec3f::all(1) : Vec3f::all(0);
		} else {
			// find texel indices
			int x = static_cast<int>(cols * u);
			int y = static_cast<int>(rows * v);

			return (*this).at<Vec3f>(y, x);
		}
	}
}

