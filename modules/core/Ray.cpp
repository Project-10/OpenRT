#include "Ray.h"
#include "Scene.h"

namespace rt {
	Vec3f Ray::hitPoint(void) const 
	{ 
		return org + dir * t; 
	}

	Vec3f Ray::hitPoint(const Vec3f& normal) const
	{
		return hitPoint() + normal * 1e-2;
	}

	Ray Ray::reflected(const Vec3f& normal) const
	{
		float cos_alpha = -dir.dot(normal);
		if (cos_alpha > 0)	return Ray(hitPoint(normal), normalize(dir + 2 * cos_alpha * normal), counter);
		else				return Ray(hitPoint(normal), dir, counter);
	}

	std::optional<Ray> Ray::refracted(const Vec3f& normal, float k) const 
	{
		if (k == 1) return Ray(hitPoint(-normal), dir, counter);
		
		float cos_alpha = -dir.dot(normal);
		float sin_2_alpha = 1.0f - cos_alpha * cos_alpha;
		float k_2_sin_2_alpha = k * k * sin_2_alpha;
		if (k_2_sin_2_alpha <= 1) {
			float cos_beta = sqrtf(1.0f - k * k * sin_2_alpha);
			return Ray(hitPoint(-normal), normalize((k * cos_alpha - cos_beta) * normal + k * dir), counter);
		}
		else
			return std::nullopt;
	}

	Vec3f Ray::reTrace(const CScene& scene) const
	{
		return counter >= maxRayCounter ? exitColor : scene.rayTrace(lvalue_cast(Ray(org, dir, counter + 1)));
	}
}

