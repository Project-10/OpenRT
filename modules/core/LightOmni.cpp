#include "LightOmni.h"
#include "Ray.h"

namespace rt {
	std::optional<Vec3f> CLightOmni::illuminate(Ray& shadowray, const Vec3f& point, const Vec3f&) const
	{
		shadowray		= Ray(point);
		shadowray.dir	= m_org - shadowray.org;
		shadowray.t		= norm(shadowray.dir);
		shadowray.dir	= normalize(shadowray.dir);
		
		return getIntensity() * (1 / (shadowray.t * shadowray.t));
	}
}