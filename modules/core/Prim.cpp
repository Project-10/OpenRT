//  Created by Mahmoud El Bergui on 07.08.22.

#include "Prim.h"

namespace rt {
	void CPrim::transform(const Mat& T) 
	{ 
		doTransform(T); 
	}
	
	Vec3f CPrim::wcs2ocs(const Vec3f& p) const 
	{ 
		return p; 
	}
}
