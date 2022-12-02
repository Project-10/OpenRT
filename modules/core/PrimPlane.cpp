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
		Vec3f hit = wcs2ocs(ray.hitPoint());
		Vec2f res = norm(hit) > Epsilon ? Vec2f(hit.dot(m_u), hit.dot(m_v)) : Vec2f(0, 0);
	
		return res;
	}

	std::pair<Vec3f, Vec3f> CPrimPlane::dp(const Vec3f& p) const
	{
		return std::make_pair(m_u, m_v);
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
