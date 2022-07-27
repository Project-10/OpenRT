#include "Gradient.h"
#include "macroses.h"

namespace rt {
	Vec3f CGradient::getColor(float x) const
	{
#ifdef DEBUG_MODE
		if (x < 0) return RGB(0, 0, 255);
		if (x > 1) return RGB(255, 0, 0);
#else
		RT_IF_WARNING(x < 0 || x > 1, "The argument is out of allowed range [0; 1]");
#endif
		
		auto b = m_mColors.lower_bound(x);		// upper known position
		if (b == m_mColors.begin()) return m_mColors.begin()->second;
		auto a = std::prev(b);					// lower known position
		
		float y = (x - a->first) / (b->first - a->first); // y \in [0, 1] to interpolate between known positions

		return (1 - y) * a->second + y * b->second;	// interpolating between 2 colors
	}
}
