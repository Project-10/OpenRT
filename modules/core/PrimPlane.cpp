#include "PrimPlane.h"
#include "ray.h"
#include "Transform.h"
#include "macroses.h"

namespace rt {
	
	bool CPrimPlane::intersect(Ray& ray) const
	{
		float t = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (t < Epsilon || isinf(t) || t > ray.t) return false;

		ray.t = t;
		// ray.u = 0;
		// ray.v = 0;
		ray.hit = shared_from_this();
		return true;
	}

	bool CPrimPlane::if_intersect(const Ray& ray) const
	{
		float t = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (t < Epsilon || isinf(t) || t > ray.t) return false;
		return true;
	}

	void CPrimPlane::transform(const Mat& t)
	{
		// Transform origin
		m_origin = CTransform::point(m_origin, t);

		// Transform normals
		Mat t1 = t.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, t1));
	}

	Vec2f CPrimPlane::getTextureCoords(const Ray& ray) const
	{
		Vec3f mu;
		
		//int mind = 0;
		//int maxd = 0;
		//for (int i = 1; i < 3; i++) {
		//	if (fabs(m_normal.val[i]) < fabs(m_normal.val[mind])) mind = i;
		//	if (fabs(m_normal.val[i]) > fabs(m_normal.val[maxd])) maxd = i;
		//}
		//int midd = 0;
		//for (int i = 1; i < 3; i++) 
		//	if (mind != i && maxd != i) {
		//		midd = i;
		//		break;
		//	}
		//mu.val[mind] = 1;
		//mu.val[maxd] = 0;
		//mu.val[midd] = fabs(m_normal.val[midd]) > Epsilon ? -m_normal.val[maxd] / m_normal.val[midd] : 0;
		
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
	
		if (fabs(m_normal.dot(mu)) > Epsilon || fabs(m_normal.dot(mv)) > Epsilon) {
			std::cout << "m_normal: " << m_normal << std::endl;
			std::cout << "mu: " << mu << std::endl;
			std::cout << "mv: " << mv << std::endl;
			std::cout << "hit: " << hit << std::endl;
			std::cout << "h: " << h << std::endl;
			std::cout << "Texel: " << res << std::endl;
		}

		return res;
	}

	CBoundingBox CPrimPlane::calcBounds(void) const
	{
		float inf = std::numeric_limits<float>::infinity();
		Vec3f minPoint = Vec3f::all(-inf);
		Vec3f maxPoint = Vec3f::all(inf);
		for (int i = 0; i < 3; i++)
			if (m_normal.val[i] == 1) {
				minPoint.val[i] = m_origin.val[i];
				maxPoint.val[i] = m_origin.val[i];
				break;
			}
		return CBoundingBox(minPoint, maxPoint);
	}
}
