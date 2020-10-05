#include "ShaderEyelight.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderEyelight::shade(const Ray& ray) const
	{
		return CShaderFlat::shade(ray) * fabs(ray.dir.dot(ray.hit->getNormal(ray)));
	}
}