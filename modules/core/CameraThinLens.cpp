#include "CameraThinLens.h"
#include "Ray.h"
#include "random.h"
#include "Sampler.h"
#include "macroses.h"

namespace rt
{
	void CCameraThinLens::InitRay(Ray& ray, int x, int y, const Vec2f& sample)
	{
		m_pCamera->InitRay(ray, x, y, sample);
		
		if (m_lensRadius > 0) {
			// Sample point on lens
			Vec2f sample(random::U<float>(), sqrtf(random::U<float>()));	// placing more samples to the outer border 
			
			//sample from uniformly distributed points in a regular polygon
			RT_ASSERT(m_nBlades == 0 || (m_nBlades >= 3 && m_nBlades <= 16));
			Point2f lens_point = m_lensRadius * CSampler::uniformSampleRegularNgon(sample, m_nBlades, random::u<int>(1, m_nBlades));
			
			// Compute point on plane of focus
			//float ft = abs(m_focalDistance / ray.dir.val[2]);	// TODO: possible bug here
			float ft = m_focalDistance;
			Vec3f focus_point = ray.org + ray.dir * ft;
			
			// Update ray for effect of lens
			ray.org += (lens_point.x * m_pCamera->getXAxis() + lens_point.y * m_pCamera->getYAxis());
			ray.dir = normalize(focus_point - ray.org);
		}
	}
}
