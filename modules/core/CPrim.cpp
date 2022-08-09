//  Created by Mahmoud El Bergui on 07.08.22.

#include "CPrim.h"
#include "Transform.h"
#include "Ray.h"

namespace rt{

	CPrim::CPrim(const ptr_shader_t pShader, const Vec3f& origin)
		: m_pShader(pShader)
		, m_t(Mat::eye(4, 4, CV_32FC1))
	{
		 for (int i = 0; i < 3; i++) m_t.at<float>(i, 3) = origin[i];
	}

	Vec3f CPrim::wcs2ocs(const Vec3f& p) const
	{
		 return CTransform::point(p, m_t.inv());
	}

	void CPrim::transform(const Mat &T)
	{
		// Accumulate transformation in the transformation matrix
		m_t = m_t * T;		
	}
}
