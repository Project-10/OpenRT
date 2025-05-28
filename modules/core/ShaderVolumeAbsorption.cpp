#include "ShaderVolumeAbsorption.h"
#include "Ray.h"

inline Vec3f exp(const Vec3f& v) {
	return Vec3f(std::exp(v[0]), std::exp(v[1]), std::exp(v[2]));
}

Vec3f rt::CShaderVolumeAbsorption::shade(const Ray& ray) const 
{
	Vec3f color = Vec3f::all(1) - getDiffuseColor(ray);	// We use the diffuse color to calculate the absorption color in this shader
	Vec3f n = ray.hit->getShadingNormal(ray);			// The shading normal (points outwards of the surface)
	
	// Throw the ray further in the same direction - through the object
	Ray transRay(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
	Vec3f transmitted = transRay.reTrace(getScene());  // What is seen "behind" or "inside" the object

	if (ray.dir.dot(n) < 0) {								// entering the surface
		double dist = transRay.t;							// Path length inside the volume
		Vec3f absorption = exp(-m_density * dist * color);	// The Beer-Lambert attenuation

		return transmitted.mul(absorption);
	} 
	else return transmitted;
}
