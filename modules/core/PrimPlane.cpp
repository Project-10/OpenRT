#include "PrimPlane.h"
#include "ray.h"
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

	void CPrimPlane::transform(const Mat& T)
	{
		// Transform origin
		m_origin = CTransform::point(m_origin, T);

		// Transform normals
		Mat T1 = T.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, T1));
	}

	Vec2f CPrimPlane::getTextureCoords(const Ray& ray) const
	{
		Vec3f mu;
		for (int i = 0; i < 3; i++)
			if (fabs(m_normal.val[i]) >= 1.0f / sqrtf(3)) {
				mu.val[i] = 0;
				int mind, maxd;
				if (fabs(m_normal.val[(i + 1) % 3]) > fabs(m_normal.val[(i + 2) % 3])) {
					maxd = (i + 1) % 3;
					mind = (i + 2) % 3;
				}
				else {
					maxd = (i + 2) % 3;
					mind = (i + 1) % 3;
				}
				mu.val[mind] = 1;
				mu.val[maxd] = fabs(m_normal.val[maxd]) > Epsilon ? -m_normal.val[mind] / m_normal.val[maxd] : 0;
				break;
			}
		mu = normalize(mu);
		Vec3f mv = normalize(m_normal.cross(mu));
		
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
			if (m_normal.val[i] == 1) {
				minPoint.val[i] = m_origin.val[i];
				maxPoint.val[i] = m_origin.val[i];
				break;
			}
		return CBoundingBox(minPoint, maxPoint);
	}
}
