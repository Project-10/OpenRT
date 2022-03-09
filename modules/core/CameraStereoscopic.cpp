#include "CameraStereoscopic.h"
#include "Ray.h"
#include "macroses.h"

namespace rt
{
void CCameraStereoscopic::InitRay(Ray& ray, int x, int y, const Vec2f& sample)
    {
		Size resolution = getResolution();
		int width = resolution.width;
		int height = resolution.height;

		// Asserts
		RT_IF_WARNING(x >= width, "Argument x = %d exceeds the camera resolution width (%d)", x, width);
		RT_IF_WARNING(y >= height, "Argument y = %d exceeds the camera resolution height (%d)", y, height);

		if (m_needUpdateAxes) {
			m_zAxis = m_dir;
			m_xAxis = normalize(m_zAxis.cross(m_up));
			m_yAxis = normalize(m_zAxis.cross(m_xAxis));
			m_needUpdateAxes = false;
		}

		float phi = 2 * Pif * (x + sample.val[0]) / width - Pif;
		float theta = Pif * (y + sample.val[1]) / height;

		Vec3f eq_dir = cosf(phi) * m_zAxis + sinf(phi) * m_xAxis;
		Vec3f eq_right = normalize(eq_dir.cross(m_up));
		// Left eye
		if(m_eye == 1) {
			ray.org = m_pos - (m_IPD / 2 * eq_right);
		}
		// Right eye
		if(m_eye == 2) {
			ray.org = m_pos + (m_IPD / 2 * eq_right);
		}

		//ray.org = m_pos;

		ray.dir = sinf(theta) * eq_dir - cosf(theta) * m_yAxis;
		ray.t = std::numeric_limits<double>::infinity();
		ray.hit = nullptr;		
    }
}

