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

		Ray I(ray.hitPoint(), ray.dir, ray.counter);
		Vec3f res = I.reTrace(m_scene);

		if (ray.dir.dot(n) < 0) { // entering the surface
		    double attenuation = I.attenuation();
		    const double alpha = MIN(1, sqrt(attenuation * I.t));
		    return alpha * getDiffuseColor(ray) + (1 - alpha) * res;
		} else return res;
    	}
}
