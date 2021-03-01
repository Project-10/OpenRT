#include "CameraPerspective.h"
#include "Ray.h"
#include "macroses.h"

namespace rt
{
	void CCameraPerspective::InitRay(Ray& ray, int x, int y, const Vec2f& sample)
	{
		Size resolution = getResolution();
		int width = resolution.width;
		int height = resolution.height;

		// Asserts
		RT_IF_WARNING(x >= width, "Argument x = %d exceeds the camera resolution width (%d)", x, width);
		RT_IF_WARNING(y >= height, "Argument y = %d exceeds the camera resolution height (%d)", y, height);
		
		// Screen-space coordinates \in [-1, 1]
		float sscx = 2 * (x + sample.val[0]) / width - 1;
		float sscy = 2 * (y + sample.val[1]) / height - 1;

		if (m_needUpdateAxes) {
			m_zAxis = m_dir;
			m_xAxis = normalize(m_zAxis.cross(m_up));
			m_yAxis = normalize(m_zAxis.cross(m_xAxis));
			m_needUpdateAxes = false;
		}

		ray.org = m_pos;
		ray.dir = normalize(getAspectRatio() * sscx * m_xAxis + sscy * m_yAxis + m_focus * m_zAxis);
		ray.t	= std::numeric_limits<double>::infinity();
		ray.hit = nullptr;

		float lensr = getlensRadius();
		float nBlades = getnBlades(); 
		if (lensr > 0) {
			// Sample point on lens
			Vec2f pLens;
			Vec2f sample(random::U<float>(), random::U<float>());
			if (nBlades == 0) {
				pLens = lensr * CSampler::concentricSampleDisk(sample);
			}
			else {
				//sample from uniformly distributed points in a regular polygon
				RT_ASSERT(nBlades >= 3 && nBlades <= 16);
				pLens = lensr * CSampler::uniformSampleRegularNgon(sample, nBlades, random::u<int>(1, nBlades));
			}

			// Compute point on plane of focus
			float ft = getfocalDistance() / ray.dir.val[2];
			Vec3f pFocus = ray.org + ray.dir * ft; 
			
			// Update ray for effect of lens
			ray.org += Vec3f(pLens.val[0], pLens.val[1], 0);
			ray.dir = normalize(pFocus - ray.org);
		}
	} 
}
