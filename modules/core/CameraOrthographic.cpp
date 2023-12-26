#include "CameraOrthographic.h"
#include "Ray.h"
#include "macroses.h"

namespace rt {
	void CCameraOrthographic::InitRay(Ray& ray, int x, int y, const Vec2f& sample) {
		Size resolution = getResolution();
		int width = resolution.width;
		int height = resolution.height;

		// Asserts
		RT_IF_WARNING(x >= width, "Argument x = %d exceeds the camera resolution width (%d)", x, width);
		RT_IF_WARNING(y >= height, "Argument y = %d exceeds the camera resolution height (%d)", y, height);
		
		// Normalized device coordinates \in [0; 1]
		float ndcx = (x + sample.val[0]) / width;
		float ndcy = (y + sample.val[1]) / height;
		
		// Screen-space coordinates \in [-1, 1]
		float sscx = 2 * ndcx - 1;
		float sscy = 2 * ndcy - 1;
		
		if (m_needUpdateAxes) {
			m_zAxis = m_dir;
			m_xAxis = normalize(m_zAxis.cross(m_up));
			m_yAxis = normalize(m_zAxis.cross(m_xAxis));
			m_needUpdateAxes = false;
		}
		
		ray.org = m_pos + m_size * (getAspectRatio() * sscx * m_xAxis + sscy * m_yAxis);
		ray.dir = m_dir;
		ray.t	= std::numeric_limits<double>::infinity();
		ray.hit = nullptr;
		ray.ndc = Vec2f(ndcx, ndcy);
	}
}
