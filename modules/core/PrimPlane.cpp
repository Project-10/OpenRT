#include "PrimPlane.h"
#include "Ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimPlane::intersect(Ray& ray) const
	{
		float dist = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;

		ray.t = dist;
		ray.hit = shared_from_this();
		return true;
	}

	bool CPrimPlane::if_intersect(const Ray& ray) const
	{
		float t = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
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
		Vec3f h = hit - m_origin;
		Vec2f res = norm(h) > Epsilon ? Vec2f(h.dot(mu), h.dot(mv)) : Vec2f(0, 0);
	
		return res;
	}

	CBoundingBox CPrimPlane::getBoundingBox(void) const
	{
		Vec3f minPoint = Vec3f::all(-Infty);
		Vec3f maxPoint = Vec3f::all(Infty);
		for (int i = 0; i < 3; i++)
			if (m_normal[i] == 1) {
				minPoint[i] = m_origin[i];
				maxPoint[i] = m_origin[i];
				break;
			}
		return CBoundingBox(minPoint, maxPoint);
	}

	void CPrimPlane::doTransform(const Mat& T)
	{
		// --- Transform origin ---
//		// Appies only translation. This leads to the effect that the rotation and scaling transformations
//		// are done relative to the origin of the primitive and not relative to the origin of the WCS
//		Vec3f o = Vec3f::all(0);		// point in the WCS origin
//		o = CTransform::point(o, T);	// translation of the point
//		m_origin += o;					// update the primitive's origin
//
//		// Above is the same as
//		for (int i = 0; i < 3; i++)
//			m_origin.val[i] += T.at<float>(i, 3);
		
		// The rotation and scaling transformatons are applied relative to the origin of the WCS
		m_origin = CTransform::point(m_origin, T);

		// --- Transform normals ---
		Mat T1 = T.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, T1));
	}
}
