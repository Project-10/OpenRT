#include "ShaderSSLT.h"
#include "Scene.h"
#include "Ray.h"

namespace rt
{
	// Constructor
	CShaderSSLT::CShaderSSLT(const CScene& scene, const Vec3f& color, float opacity) : CShader(color), m_scene(scene)
	{
		setOpacity(opacity);
	}

	Vec3f CShaderSSLT::shade(const Ray& ray) const
	{
		Ray I(ray.hitPoint(), ray.dir, ray.counter);
		float opacity = getOpacity();
		return opacity * getDiffuseColor(ray) + (1.0f - opacity) * I.reTrace(m_scene);
	}
}
