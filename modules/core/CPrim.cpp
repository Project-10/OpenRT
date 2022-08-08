//  Created by Mahmoud El Bergui on 07.08.22.
//

#include "CPrim.h"
#include "Transform.h"
#include "Ray.h"

namespace rt{

CPrim::CPrim(const ptr_shader_t pShader, Vec3f origin)
: m_pShader(pShader)
, m_origin(origin)
, m_t(Mat::eye(4, 4, CV_32FC1))
{
     for (int i = 0; i < 3; i++) m_t.at<float>(i, 3) = m_origin[i];
}

Vec3f CPrim::getSolidTextureCoords(const Ray &ray) const{
     return CTransform::point(ray.hitPoint(), m_t.inv());
}

}
