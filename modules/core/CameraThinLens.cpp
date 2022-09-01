#include "CameraThinLens.h"
#include "Ray.h"
#include "random.h"
#include "Sampler.h"
#include "macroses.h"

namespace rt
{
	void CCameraThinLens::InitRay(Ray& ray, int x, int y, const Vec2f& sample)
	{
		CCameraPerspective::InitRay(ray, x, y, sample);

		if (m_lensRadius > 0) {
			// Sample point on lens
			Vec2f sample(random::U<float>(), random::U<float>());
			
			//sample from uniformly distributed points in a regular polygon
			RT_ASSERT(m_nBlades == 0 || (m_nBlades >= 3 && m_nBlades <= 16));
			Vec2f pLens = m_lensRadius * CSampler::uniformSampleRegularNgon(sample, m_nBlades, random::u<int>(1, m_nBlades));
			
			// Compute point on plane of focus
			float ft = abs(m_focalDistance / ray.dir.val[2]);
			Vec3f pFocus = ray.org + ray.dir * ft;
			//std::cout << "a " << pFocus.val[2] << std::endl;
			// Update ray for effect of lens
			ray.org += (pLens.val[0] * getxAxis() + pLens.val[1] * getyAxis());
			ray.dir = normalize(pFocus - ray.org);
		}
	}
}
