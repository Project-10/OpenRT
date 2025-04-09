#include "LightSpot.h"
#include "Ray.h"

namespace rt {
	std::optional<Vec3f> CLightSpot::illuminate(Ray& shadowray, const Vec3f& point, const Vec3f&) const {
		auto res = CLightOmni::illuminate(shadowray, point);

		float angle = acosf(m_dir.dot(-shadowray.dir)) * 180 / Pif;
		if (angle > (m_alpha + m_beta)) return std::nullopt;	// no light
		if (angle <= m_alpha) return res;						// 100% light

		// angle \in (m_alpha; m_alpha + m_beta]
		float k = (angle - m_alpha) / m_beta;					// k \in (0, 1]
		float scale;
		switch (2) {
			case 0: scale = 1 - k; 					 break;
			case 1: scale = 1 - k * k; 				 break;
			case 2: scale = (1 + cosf(Pif * k)) / 2; break;
			default: scale = 1;
		}
		return (res.value() * scale);				// attenuated light
	}
}