#include "LightArea.h"
#include "Ray.h"

namespace rt {
	std::optional<Vec3f> CLightArea::illuminate(Ray& ray)
	{
		Vec2f sample = m_pSampler->getNextSample();
		Vec3f org = m_org + sample.val[0] * m_edge1 + sample.val[1] * m_edge2;

		setOrigin(org);
		auto res = CLightOmni::illuminate(ray);

		double cosN = -ray.dir.dot(m_normal) / ray.t;
		if (cosN > 0)	return m_area * cosN * res.value();
		else			return std::nullopt;
	}
}