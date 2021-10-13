#include "BoundingBox.h"
#include "Ray.h"
#include "macroses.h"

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

	void CBoundingBox::extend(const Vec3f& p)
	{
		m_minPoint = Min3f(p, m_minPoint);
		m_maxPoint = Max3f(p, m_maxPoint);
	}

	void CBoundingBox::extend(const CBoundingBox& box)
	{
		// We make the extended box a little bit larger than needed (plus-minus Epsilon)
        // That helps to eliminate acne at plane surfaceses parallel to the axises of WCS
        // This acne is not related to self-occlusion, but to the seconst condition in line
        // return (ray.hit && ray.t < t1 + Epsilon);
        // when t1 corresponds to the scene most distant boundary
        extend(box.m_minPoint - Vec3f::all(Epsilon));
		extend(box.m_maxPoint + Vec3f::all(Epsilon));
	}

    std::pair<CBoundingBox, CBoundingBox> CBoundingBox::split(int dim, float val) const
    {
        // Assertions
        RT_ASSERT(dim >= 0 && dim < 3);
        RT_ASSERT_MSG(val > m_minPoint[dim] && val < m_maxPoint[dim], "Splitting value %f does not lie in AABB range [%f: %f]", val, m_minPoint[dim], m_maxPoint[dim]);
        
        auto res = std::make_pair(*this, *this);
        res.first.m_maxPoint[dim] = val;
        res.second.m_minPoint[dim] = val;
        return res;
    }

	bool CBoundingBox::overlaps(const CBoundingBox& box) const
	{
		for (int dim = 0; dim < 3; dim++) {
			if (box.m_minPoint[dim] - Epsilon > m_maxPoint[dim]) return false;
			if (box.m_maxPoint[dim] + Epsilon < m_minPoint[dim]) return false;
		}
		return true;
	}

    void CBoundingBox::clip(const Ray& ray, double& t0, double& t1) const
    {
        float d, den;
        if (ray.dir.val[0] != 0) {
            den = 1.0f / ray.dir.val[0];
            if (ray.dir.val[0] > 0) {
                if ((d = (m_minPoint.val[0] - ray.org.val[0]) * den) > t0) t0 = d;
                if ((d = (m_maxPoint.val[0] - ray.org.val[0]) * den) < t1) t1 = d;
            }
            else {
                if ((d = (m_maxPoint.val[0] - ray.org.val[0]) * den) > t0) t0 = d;
                if ((d = (m_minPoint.val[0] - ray.org.val[0]) * den) < t1) t1 = d;
            }
            if (t0 > t1) return;
        }

        if (ray.dir.val[1] != 0) {
            den = 1.0f / ray.dir.val[1];
            if (ray.dir.val[1] > 0) {
                if ((d = (m_minPoint.val[1] - ray.org.val[1]) * den) > t0) t0 = d;
                if ((d = (m_maxPoint.val[1] - ray.org.val[1]) * den) < t1) t1 = d;
            }
            else {
                if ((d = (m_maxPoint.val[1] - ray.org.val[1]) * den) > t0) t0 = d;
                if ((d = (m_minPoint.val[1] - ray.org.val[1]) * den) < t1) t1 = d;
            }
            if (t0 > t1) return;
        }

        if (ray.dir.val[2] != 0) {
            den = 1.0f / ray.dir.val[2];
            if (ray.dir.val[2] > 0) {
                if ((d = (m_minPoint.val[2] - ray.org.val[2]) * den) > t0) t0 = d;
                if ((d = (m_maxPoint.val[2] - ray.org.val[2]) * den) < t1) t1 = d;
            }
            else {
                if ((d = (m_maxPoint.val[2] - ray.org.val[2]) * den) > t0) t0 = d;
                if ((d = (m_minPoint.val[2] - ray.org.val[2]) * den) < t1) t1 = d;
            }
        }
    }
}

