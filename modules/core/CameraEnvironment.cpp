#include "CameraEnvironment.h"
#include "Ray.h"
#include "macroses.h"

namespace rt
{
    void CCameraEnvironment::InitRay(Ray& ray, int x, int y, const Vec2f& sample)
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
        
        ray.org = m_pos;
        ray.dir = normalize(sinf(theta) * cosf(phi) * m_zAxis + sinf(theta) * sinf(phi) * m_xAxis - cosf(theta) * m_yAxis);
        ray.t = std::numeric_limits<double>::infinity();
        ray.hit = nullptr;
    }
}
