#include "PrimPlane.h"
#include "Ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimPlane::intersect(Ray& ray) const
	{
		float dist = (getOrigin() - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;

		ray.t = dist;
		ray.hit = shared_from_this();
		return true;
	}

	bool CPrimPlane::if_intersect(const Ray& ray) const
	{
		float t = (getOrigin() - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (t < Epsilon || isinf(t) || t > ray.t) return false;
		return true;
	}

	Vec2f CPrimPlane::getTextureCoords(const Ray& ray) const
	{
		Vec3f mu, mv; // Together with the normal these vectors should build an object coordinate system
		if (m_normal[1] < 1.0f) mu = normalize(m_normal.cross(Vec3f(0, 1, 0)));	// assuming up-vector to be Y-direction in WCS
		else mu = normalize(m_normal.cross(Vec3f(1, 0, 0)));
		mv = m_normal.cross(mu);
		
		Vec3f hit = ray.hitPoint();
		Vec3f h = hit - getOrigin();
		Vec2f res = norm(h) > Epsilon ? Vec2f(h.dot(mu), h.dot(mv)) : Vec2f(0, 0);
	
		return res;
	}

	CBoundingBox CPrimPlane::getBoundingBox(void) const
	{
		Vec3f minPoint = Vec3f::all(-Infty);
		Vec3f maxPoint = Vec3f::all(Infty);
		Vec3f origin = getOrigin();
		for (int i = 0; i < 3; i++)
			if (m_normal[i] == 1) {
				minPoint[i] = origin[i];
				maxPoint[i] = origin[i];
				break;
			}
		return CBoundingBox(minPoint, maxPoint);
	}

	void CPrimPlane::doTransform(const Mat& T)
	{
		// --- Transform normals ---
		Mat T1 = T.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, T1));
	}
}
