//  Created by Mahmoud El Bergui on 07.08.22.

#include "Prim.h"
#include "Transform.h"
#include "Ray.h"

namespace rt {
	// Constructor
	CPrim::CPrim(const ptr_shader_t pShader, const Vec3f& origin)
		: m_pShader(pShader)
		, m_origin(origin)
		, m_t(Mat::eye(4, 4, CV_32FC1))
	{
		for (int i = 0; i < 3; i++) m_t.at<float>(i, 3) = origin[i];
	}

	void CPrim::transform(const Mat& T)
	{
		// --- Transform origin ---
//		// Appies only translation. This leads to the effect that the rotation and scaling transformations
//		// are done relative to the origin of the primitive and not relative to the origin of the WCS
//		Vec3f o = Vec3f::all(0);		// point in the WCS origin
//		o = CTransform::point(o, T);	// translation of the point
//		m_origin += o;					// update the primitive's origin
//
//		// Above is the same as
//		for (int i = 0; i < 3; i++)
//			m_origin.val[i] += T.at<float>(i, 3);
		
		// The rotation and scaling transformatons are applied relative to the origin of the WCS
		m_origin = CTransform::point(m_origin, T);
		
		// Accumulate transformations in the m_t matrix
		m_t = T * m_t;
		
		// --- Transform primitives' properties ---
		doTransform(T);
	}
	
	Vec3f CPrim::wcs2ocs(const Vec3f& p) const 
	{
		return CTransform::point(p, m_t.inv());
	}
}
