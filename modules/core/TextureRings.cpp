#include "TextureRings.h"

namespace rt{
	/// @todo Play with the direction of the rings
	Vec3f CTextureRings::getTexel(const Vec3f& uvw) const
	{
		const Vec3f period = m_period * Vec3f(1, 1, 0); // orintation of the rings
		
		// Difference between point and center of the shape
		float value = static_cast<float>(norm(uvw.mul(period)));

		return static_cast<int>(value) % 2 == 0 ? RGB(255, 0, 0) : RGB(255, 255, 255);
	}
}
