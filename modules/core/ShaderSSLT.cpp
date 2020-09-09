#include "ShaderSSLT.h"
#include "macroses.h"

namespace rt
{
	Vec3f CShaderSSLT::shade(const Ray& ray) const
	{
		Vec3f res = Vec3f::all(0);

		Vec3f color = m_color;

		Ray I(ray.hitPoint(), ray.dir, ray.counter + 1);
		res = color + reTrace(I);
		return res;
	}

	Vec3f CShaderSSLT::reTrace(const Ray& ray) const
	{
		return ray.counter >= maxRayCounter ? exitColor : m_scene.rayTrace(lvalue_cast(Ray(ray.org, ray.dir, ray.counter)));
	}
}