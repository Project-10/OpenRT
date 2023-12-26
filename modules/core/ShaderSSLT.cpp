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
		Vec3f n = ray.hit->getNormal(ray);
		
		Ray I(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
		Vec3f res = I.reTrace(m_scene);
		
		//if (ray.dir.dot(n) < 0) { // entering the surface
		//	const double k = 0.25;
		//	const double f = k * I.t; // linear
		//	//const double f = k * I.t* I.t;
		//	const double alpha = MIN(1, f);
		//	return alpha * getDiffuseColor(ray) + (1 - alpha) * res;
		//}
		//else return res;
		
		float opacity = getOpacity(ray);
		return opacity * getDiffuseColor(ray) + (1.0f - opacity) * res;
	}
}
