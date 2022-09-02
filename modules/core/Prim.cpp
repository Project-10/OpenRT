//  Created by Mahmoud El Bergui on 07.08.22.

#include "Prim.h"
#include "Transform.h"

namespace rt {
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
		
		// --- Transform primitives' properties ---
		doTransform(T);
	}
	
	Vec3f CPrim::wcs2ocs(const Vec3f& p) const 
	{ 
		return p; 
	}
}
