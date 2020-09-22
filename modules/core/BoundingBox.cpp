#include "BoundingBox.h"
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
		extend(box.m_minPoint);
		extend(box.m_maxPoint);
	}

    std::pair<CBoundingBox, CBoundingBox> CBoundingBox::split(int dim, float val) const
    {
        // Assertions
        RT_ASSERT(dim >= 0 && dim < 3);
        RT_ASSERT(val > m_minPoint[dim] && val < m_maxPoint[dim]);
        
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
}

