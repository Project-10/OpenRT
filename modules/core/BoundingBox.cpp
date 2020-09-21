#include "BoundingBox.h"
#include "ray.h"

namespace rt {

	namespace {
		inline Vec3f Min3f(const Vec3f& a, const Vec3f& b)
		{
			return Vec3f(MIN(a.val[0], b.val[0]), MIN(a.val[1], b.val[1]), MIN(a.val[2], b.val[2]));
		}

		inline Vec3f Max3f(const Vec3f& a, const Vec3f& b)
		{
			return Vec3f(MAX(a.val[0], b.val[0]), MAX(a.val[1], b.val[1]), MAX(a.val[2], b.val[2]));
		}
	}

	void CBoundingBox::clear(void)
	{
		m_min = Vec3f::all(Infty);
		m_max = Vec3f::all(-Infty);
	}

	void CBoundingBox::extend(const Vec3f& p)
	{
		m_min = Min3f(p, m_min);
		m_max = Max3f(p, m_max);
	}

	void CBoundingBox::extend(const CBoundingBox& box)
	{
		extend(box.m_min);
		extend(box.m_max);
	}

	bool CBoundingBox::overlaps(const CBoundingBox& box)
	{
		for (int i = 0; i < 3; i++) {
			if (box.m_min[i] - Epsilon > m_max[i]) return false;
			if (box.m_max[i] + Epsilon < m_min[i]) return false;
		}
		return true;
	}

	void CBoundingBox::clip(const Ray& ray, double& t0, double& t1) const
	{
        float d, den;
		den = 1.0f / ray.dir.val[0];
		if (ray.dir.val[0] > 0) {
			if ((d = (m_min.val[0] - ray.org.val[0]) * den) > t0) t0 = d;
			if ((d = (m_max.val[0] - ray.org.val[0]) * den) < t1) t1 = d;
		}
		else {
			if ((d = (m_max.val[0] - ray.org.val[0]) * den) > t0) t0 = d;
			if ((d = (m_min.val[0] - ray.org.val[0]) * den) < t1) t1 = d;
		}
		if (t0 > t1) return;

		den = 1.0f / ray.dir.val[1];
		if (ray.dir.val[1] > 0) {
			if ((d = (m_min.val[1] - ray.org.val[1]) * den) > t0) t0 = d;
			if ((d = (m_max.val[1] - ray.org.val[1]) * den) < t1) t1 = d;
		}
		else {
			if ((d = (m_max.val[1] - ray.org.val[1]) * den) > t0) t0 = d;
			if ((d = (m_min.val[1] - ray.org.val[1]) * den) < t1) t1 = d;
		}
		if (t0 > t1) return;

		den = 1.0f / ray.dir.val[2];
		if (ray.dir.val[2] > 0) {
			if ((d = (m_min.val[2] - ray.org.val[2]) * den) > t0) t0 = d;
			if ((d = (m_max.val[2] - ray.org.val[2]) * den) < t1) t1 = d;
		}
		else {
			if ((d = (m_max.val[2] - ray.org.val[2]) * den) > t0) t0 = d;
			if ((d = (m_min.val[2] - ray.org.val[2]) * den) < t1) t1 = d;
		}
	}

}

