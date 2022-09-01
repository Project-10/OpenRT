#include "TextureStripes.h"

namespace rt{
	/// @todo Play with the direction of the stripes
	Vec3f CTextureStripes::getTexel(const Vec3f& uvw) const
	{
		// Full form
		//const Vec3f period = m_period * Vec3f(1, 0, 0); // orintation of the stripes
		//float value = static_cast<float>(sum(uvw.mul(period))[0]);

		float value = m_period * uvw[2];	// Short form
		if (value < 0) value -= 1;			// Making stripes to be odd function (0.1 -> even, -0.1 -> odd)

		return static_cast<int>(value) % 2 == 0 ? RGB(255, 0, 0) : RGB(255, 255, 255);
	}
}
