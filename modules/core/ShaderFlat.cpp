#include "ShaderFlat.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderFlat::shade(const Ray& ray) const 
	{
		return getColor(ray);
	}
}
