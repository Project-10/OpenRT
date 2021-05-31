#include "ShaderFlat.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderFlat::shade(const Ray& ray) const 
	{
	    Vec3f color = m_color;
#ifdef DEBUG_MODE
        Vec3f normal = ray.hit->getNormal(ray);									// shading normal
        bool inside = false;
        if (normal.dot(ray.dir) > 0) {
            normal = -normal;													// turn normal to front
            inside = true;
        }
        color = inside ? RGB(1, 0, 0) : RGB(0, 0, 1);
#endif
		return m_pTexture ? m_pTexture->getTexel(ray.hit->getTextureCoords(ray)) : color;
	}
}