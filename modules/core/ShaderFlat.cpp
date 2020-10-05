#include "ShaderFlat.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderFlat::shade(const Ray& ray) const 
	{
		return m_pTexture ? m_pTexture->getTexel(ray.hit->getTextureCoords(ray)) : m_color;
	}
}