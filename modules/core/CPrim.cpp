//  Created by Mahmoud El Bergui on 07.08.22.

#include "CPrim.h"
#include "Transform.h"
#include "Ray.h"

namespace rt{

	CPrim::CPrim(const ptr_shader_t pShader, const Vec3f& pivot)
		: m_pShader(pShader)
		, m_t(Mat::eye(4, 4, CV_32FC1))
	{
		setPivot(pivot);
	}

	Vec3f CPrim::wcs2ocs(const Vec3f& p) const
	{
		return CTransform::point(p, m_t.inv());
	}

	void CPrim::transform(const Mat &T)
	{
		// Accumulate transformation in the transformation matrix
		Vec3f pivot;
		for (int i = 0; i < 3; i++) {
			pivot[i] = m_t.at<float>(i, 3);
			m_t.at<float>(i, 3) = 0;
		}

		m_t = T * m_t;

		for (int i = 0; i < 3; i++)
			m_t.at<float>(i, 3) += pivot[i];

		doTransform(T);
	}

	Vec3f CPrim::getNormal(const Ray& ray) const 
	{ 
		return m_flipped ? -doGetNormal(ray) : doGetNormal(ray); 
	}
	
	Vec3f CPrim::getShadingNormal(const Ray& ray) const 
	{
		return m_flipped ? -doGetShadingNormal(ray) : doGetShadingNormal(ray); 
	}
}