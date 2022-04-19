#include "PrimSphere.h"
#include "Ray.h"
#include "Transform.h"
#include "macroses.h"

namespace rt {
	bool CPrimSphere::intersect(Ray& ray) const
	{
		double r2 = static_cast<double>(m_radius) * static_cast<double>(m_radius);
#if 1
		// geometrical derivation
		Vec3f L = m_origin - ray.org;

		double tb = static_cast<double>(L.dot(ray.dir));

		double h2 = static_cast<double>(L.dot(L)) - tb * tb;
		if (h2 > r2)					// no intersection
			return false;

		double delta = sqrt(r2 - h2);
		double t0 = tb - delta;
		double t1 = tb + delta;
#else
		// analytical derivation, numerically not very stable, but simple
		// --> find roots of f(t) = ((R+tD)-C)^2 - r^2
		// f(t) = (R-C)^2 + 2(R-C)(tD) + (tD)^2 -r^2
		// --> f(t) = [D^2] t^2 + [2D(R-C)] t + [(R-C)^2 - r^2]
		Vec3f diff = ray.org - m_origin;
		double a = 1; // static_cast<double>(ray.dir.dot(ray.dir));	// must be equal to 1, since ray.dir must be normalized
		double b = 2 * static_cast<double>(ray.dir.dot(diff));
		double c = static_cast<double>(diff.dot(diff)) - r2;

		// use 'abc'-formula for finding root t_1,2 = (-b +/- sqrt(b^2-4ac))/(2a)
		double inRoot = b * b - 4 * a * c;
		if (inRoot < 0)
			return false;
		double root = sqrt(inRoot);
		double t0 = (-b - root) / (2 * a);
		double t1 = (-b + root) / (2 * a);
#endif
		RT_ASSERT(t0 <= t1);

		if (t0 > ray.t) return false;

		if (t0 <= Epsilon) {
			t0 = 0;
			if (t1 < Epsilon || t1 > ray.t) 
				return false;
		}

		ray.t = t0 > Epsilon ? t0 : t1;
		ray.hit = shared_from_this();
		return true;
	}

	/// @todo Optimize it
	bool CPrimSphere::if_intersect(const Ray& ray) const
	{
		return intersect(lvalue_cast(Ray(ray)));
	}

	void CPrimSphere::transform(const Mat& T)
	{
		// Transform origin
		Vec3f o = Vec3f::all(0);		// point in the WCS origin
		o = CTransform::point(o, T);	// translation of the point
		m_origin += o;					// update the sphere's origin
		
		// Transform radius
		Vec3f r = m_radius * normalize(Vec3f::all(1));
		r = CTransform::vector(r, T);
		m_radius = static_cast<float>(norm(r));
	}

	Vec3f CPrimSphere::doGetNormal(const Ray& ray) const
	{
		return normalize(ray.hitPoint() - m_origin);
	}

	Vec2f CPrimSphere::getTextureCoords(const Ray& ray) const
	{
		Vec3f hitPoint = ray.hitPoint() - m_origin;
		float phi = atan2f(hitPoint[2], hitPoint[0]);
		float theta = acosf(MIN(m_radius, hitPoint[1]) / m_radius);
		return Vec2f(-0.5f * phi / Pif, theta / Pif);
	}

        Vec3f CPrimSphere::getObjectCoords(const Ray &ray) const
        {
            Vec3f  normalizeCoords = ray.hitPoint();
            return normalizeCoords;
        }
        
	CBoundingBox CPrimSphere::getBoundingBox(void) const 
	{ 
		return CBoundingBox(m_origin - Vec3f::all(m_radius), m_origin + Vec3f::all(m_radius)); 
	}
}







