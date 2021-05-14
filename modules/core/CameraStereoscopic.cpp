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
        
        float theta = Pif * ((y + sample.val[1]) / height);
        float phi   = Pif * (((x + sample.val[0]) / width) * 2 - 0.5f);
        
        if (m_needUpdateAxes) {
            m_zAxis = m_dir;
            m_xAxis = normalize(m_zAxis.cross(m_up));
            m_yAxis = normalize(m_zAxis.cross(m_xAxis));
            m_needUpdateAxes = false;
        }
        
        RT_ASSERT_MSG(m_dir != m_up, "Direction vector is the same as up vector");
        
        Vec3f ort = normalize(m_up.cross(m_dir));
            
        // Left eye
        if(m_eye == 1) {
            ray.org = m_pos - (m_IPD / 2 * ort);
        }
        
        // Right eye
        if(m_eye == 2) {
            ray.org = m_pos + (m_IPD / 2 * ort);
        }
        
        ray.dir = normalize(sinf(theta) * cosf(phi) * m_xAxis + sinf(theta) * sinf(phi) * m_zAxis - cosf(theta) * m_yAxis);
        
        ray.t = std::numeric_limits<double>::infinity();
        ray.hit = nullptr;
    }
}

