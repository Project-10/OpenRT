#include "PrimDisc.h"
#include "Ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimDisc::intersect(Ray& ray) const
	{
		float dist = (getOrigin() - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;
		if (static_cast<float>(norm(ray.org + ray.dir * dist - getOrigin())) > m_radius) return false;

		ray.t = dist;
		ray.hit = shared_from_this();
		return true;
	}

	/// @todo Optimize it
	bool CPrimDisc::if_intersect(const Ray& ray) const
	{
		float dist = (getOrigin() - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;
		if (static_cast<float>(norm(ray.org + ray.dir * dist - getOrigin())) > m_radius) return false;
		return true;
	}

	Vec2f CPrimDisc::getTextureCoords(const Ray& ray) const
	{
		Vec3f hit = wcs2ocs(ray.hitPoint());	// Hitpoint in OCS
		hit = hit * (0.5f / m_r);
		return norm(hit) > Epsilon ? Vec2f(0.5f + hit.dot(m_u), 0.5f + hit.dot(m_v)) : Vec2f(0.5f, 0.5f);
	}

	std::pair<Vec3f, Vec3f> CPrimDisc::dp(const Vec3f&) const
	{
		Vec3f dpdu = ocs2wcs(m_u);
		Vec3f dpdv = ocs2wcs(m_v);
		return std::make_pair(dpdu, dpdv);
	}

	// Implementation is taken from: https://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	CBoundingBox CPrimDisc::getBoundingBox(void) const
	{
		Vec3f e;
		for (int i = 0; i < 3; i++)
			e[i] = m_radius * sqrtf(1 - m_normal[i] * m_normal[i]);
		return CBoundingBox(getOrigin() - e, getOrigin() + e);
	}

	void CPrimDisc::doTransform(const Mat& T)
	{
		// --- Transform radius ---
		Vec3f r = m_radius * normalize(Vec3f::all(1));
		r = CTransform::vector(r, T);
		m_radius = static_cast<float>(norm(r));

		// --- Transform normals ---
		Mat T1 = T.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, T1));
	}
}
