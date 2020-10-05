#include "ShaderSSLT.h"
#include "Scene.h"
#include "Ray.h"

namespace rt
{
	Vec3f CShaderSSLT::shade(const Ray& ray) const
	{
		Ray I(ray.hitPoint(), ray.dir, ray.counter);
		return m_opacity * CShaderFlat::shade(ray) + (1.0f - m_opacity) * I.reTrace(m_scene);
	}
}