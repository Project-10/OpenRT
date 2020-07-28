#include "PrimSphere.h"
#include "ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimSphere::intersect(Ray& ray) const
	{
		// mathematical derivation, numerically not very stable, but simple
		
		// --> find roots of f(t) = ((R+tD)-C)^2 - r^2
		// f(t) = (R-C)^2 + 2(R-C)(tD) + (tD)^2 -r^2
		// --> f(t) = [D^2] t^2 + [2D(R-C)] t + [(R-C)^2 - r^2]
		Vec3f diff = ray.org - m_origin;
		float a = ray.dir.dot(ray.dir);
		float b = 2 * ray.dir.dot(diff);
		float c = diff.dot(diff) - m_radius * m_radius;
		
		// use 'abc'-formula for finding root t_1,2 = (-b +/- sqrt(b^2-4ac))/(2a)
		float inRoot = b * b - 4 * a * c;
		if (inRoot < 0) return false;
		float root = sqrtf(inRoot);
		
		float dist = (-b - root) / (2 * a);
		if (dist > ray.t)
			return false;
		
		if (dist < Epsilon) {
			dist = (-b + root) / (2 * a);
			if (dist < Epsilon || dist > ray.t)
				return false;
		}
		
		ray.t = dist;
		ray.hit = shared_from_this();
		return true;
	}

	bool CPrimSphere::if_intersect(const Ray& ray) const
	{
		return intersect(lvalue_cast(Ray(ray)));
	}

	void CPrimSphere::transform(const Mat& t)
	{
		// Transform origin
		m_origin = CTransform::point(m_origin, t);
		
		Vec3f r = m_radius * normalize(Vec3f::all(1));
		r = CTransform::vector(r, t);
		m_radius = norm(r);
	}

	Vec3f CPrimSphere::getNormal(const Ray& ray) const
	{
		return normalize(ray.hitPoint() - m_origin);
	}

	Vec2f CPrimSphere::getTextureCoords(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hitPoint() - m_origin;
		hitPoint.val[1] = MIN(MAX(hitPoint.val[1], -1), 1);
		float theta = acosf(hitPoint.val[1] / m_radius);	// [0; Pif]

		float phi 	= sinf(theta) > Epsilon ? acosf(hitPoint.val[0] / (m_radius * sinf(theta))) : 0;	// [0; Pif]
		if (hitPoint.val[2] < 0) phi = - phi;															// [-Pif; Pif]
		if (isnan(phi)) phi = 0;
		return Vec2f(-0.5f * (1 + phi / Pif), theta / Pif);
	}
}

