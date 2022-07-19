//  Created by Mahmoud El Bergui on 12.07.22.

#include "CGradient.h"

namespace rt {
	Vec3f CGradient::getColor(float x) const
	{
		// These 2 lines are for debugging
		if (x < 0) return RGB(0, 0, 255);
		if (x > 1) return RGB(255, 0, 0);
		
		auto b = m_mColors.lower_bound(x);		// upper known position
		auto a = std::prev(b);					// lower known position
		
		float y = (x - a->first) / (b->first - a->first); // y \in [0, 1] to interpolate between known positions

		return (1 - y) * a->second + y * b->second;	// interpolating between 2 colors
	}
}
