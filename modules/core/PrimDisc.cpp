#include "PrimDisc.h"
#include "Ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimDisc::intersect(Ray& ray) const
	{
		// Compute plane intersection for disc
		float dist = (getOrigin() - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;
		// See if hit point  is inside disc radii
		float r = static_cast<float>(norm(ray.org + ray.dir * dist - getOrigin()));
		if (r > m_radius || r < m_innerRadius) return false;

		ray.t = dist;
		ray.hit = shared_from_this();
		return true;
	}

	/// @todo Optimize it
	bool CPrimDisc::if_intersect(const Ray& ray) const
	{
		float dist = (getOrigin() - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;
		float r = static_cast<float>(norm(ray.org + ray.dir * dist - getOrigin()));
		if (r > m_radius || r < m_innerRadius) return false;
		return true;
	}

	Vec2f CPrimDisc::getTextureCoords(const Ray& ray) const
	{
		Vec3f hitPoint = wcs2ocs(ray.hitPoint());		// Hitpoint in OCS
		float r = static_cast<float>(norm(hitPoint));	// Radius in OCS: sqrt(x^2 + y^2 + z^2) (in respect to the initial radius of the disc, before any transforms)

		float dot = m_t.dot(hitPoint);
		float det = m_n.dot(m_t.cross(hitPoint));
		float phi = atan2f(det, dot);

		return Vec2f(-0.5f * phi / Pif, (m_r - r) / (m_r - m_ri));
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
		// --- Transform normals ---
		Mat T1 = T.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, T1));
		
		// --- Transform radius ---
		Vec3f r = m_radius * normalize(Vec3f::all(1));
		r = CTransform::vector(r, T);
		float scale = static_cast<float>(norm(r)) / m_radius;
		m_radius *= scale;
		m_innerRadius *= scale;
	}
}
