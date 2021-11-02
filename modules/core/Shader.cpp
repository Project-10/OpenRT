#include "Shader.h"
#include "Ray.h"

namespace rt {
	void CShader::setColor(const Vec3f& color)
	{
		m_color =  color;
		m_pColorMap = nullptr;
	}
	
	void CShader::setColor(const ptr_texture_t pColorMap)
	{
		m_pColorMap = pColorMap;
	}

	Vec3f CShader::getColor(const Ray& ray) const
	{
		Vec3f res = m_color;
#ifdef DEBUG_MODE
		Vec3f normal = ray.hit->getNormal(ray);			// normal
		bool inside = normal.dot(ray.dir) > 0;			// true if normal points outward the ray origin
		res = inside ? RGB(1, 0, 0) : RGB(0, 0, 1);
#endif
		return m_pColorMap ? m_pColorMap->getTexel(ray.hit->getTextureCoords(ray)) : res;
	}
}
