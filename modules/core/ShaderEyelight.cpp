#include "ShaderEyelight.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderEyelight::shade(const Ray& ray) const
	{
		return getDiffuseColor(ray) * fabs(ray.dir.dot(ray.hit->getShadingNormal(ray)));
	}
}
