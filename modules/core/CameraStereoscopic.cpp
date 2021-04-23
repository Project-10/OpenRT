#include "CameraStereoscopic.h"
#include "Ray.h"
#include "macroses.h"
#include "CameraEnvironmentTarget.h"

namespace rt
{
void CCameraStereoscopic::InitRay(Ray& ray, int x, int y, const Vec2f& sample)
    {
        Size resolution = getResolution();
        const Vec3f& direction = normalize(m_dir - m_pos);
        const Vec3f& translation_vector = normalize(direction.cross(m_up));
        
        if(m_eye == 1) {
            const Vec3f& left_position = m_pos - .5f * m_IPD * translation_vector;
            CCameraEnvironmentTarget *Left = new CCameraEnvironmentTarget(resolution, left_position, m_dir, m_up);
        
            Left->InitRay(ray, x, y);
        }
            
        if(m_eye == 2) {
            const Vec3f& right_position = m_pos + .5f * m_IPD * translation_vector;
            CCameraEnvironmentTarget *Right = new CCameraEnvironmentTarget(resolution, right_position, m_dir, m_up);
        
            Right->InitRay(ray, x, y);
        }
    }
}
