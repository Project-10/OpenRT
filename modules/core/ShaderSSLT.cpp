#include "ShaderSSLT.h"
#include "macroses.h"

namespace rt
{
	Vec3f CShaderSSLT::shade(const Ray& ray) const
	{
		Vec3f res = Vec3f::all(0);

		Ray I(ray.hitPoint(), ray.dir, ray.counter + 1);
		res = m_opacity * m_color + (1.0f - m_opacity) * reTrace(I);
		return res;
	}

	Vec3f CShaderSSLT::reTrace(const Ray& ray) const
	{
		return ray.counter >= maxRayCounter ? m_exitColor : m_scene.rayTrace(lvalue_cast(Ray(ray.org, ray.dir, ray.counter)));
	}
}