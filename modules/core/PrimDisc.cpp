#include "PrimDisc.h"
#include "Ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimDisc::intersect(Ray& ray) const
	{
		float dist = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;
		if (static_cast<float>(norm(ray.org + ray.dir * dist - m_origin)) > m_radius) return false;

		ray.t = dist;
		ray.hit = shared_from_this();
		return true;
	}

	/// @todo Optimize it
	bool CPrimDisc::if_intersect(const Ray& ray) const
	{
		float dist = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
		if (dist < Epsilon || isinf(dist) || dist > ray.t) return false;
		if (static_cast<float>(norm(ray.org + ray.dir * dist - m_origin)) > m_radius) return false;
		return true;
	}

	void CPrimDisc::transform(const Mat& T)
	{
		CPrim::transform(T);

		// Transform origin
		Vec3f o = Vec3f::all(0);		// point in the WCS origin
		o = CTransform::point(o, T);	// transltion of the point
		m_origin += o;					// update the sphere's origin

		// Transform normals
		Mat T1 = T.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, T1));

		// Transform radius
		Vec3f r = m_radius * normalize(Vec3f::all(1));
		r = CTransform::vector(r, T);
		m_radius = static_cast<float>(norm(r));
	}

	Vec2f CPrimDisc::getTextureCoords(const Ray& ray) const
	{
		Vec3f mu, mv; // Together with the normal these vectors should build an object coordinate system
		if (m_normal[1] < 1.0f) mu = normalize(m_normal.cross(Vec3f(0, 1, 0)));	// assuming up-vector to be Y-direction in WCS
		else mu = normalize(m_normal.cross(Vec3f(1, 0, 0)));
		mv = m_normal.cross(mu);
		
		Vec3f hit = wcs2ocs(ray.hitPoint());
		hit = hit * (0.5f / m_radius);
		Vec2f res = norm(hit) > Epsilon ? Vec2f(0.5f + hit.dot(mu), 0.5f + hit.dot(mv)) : Vec2f(0.5f, 0.5f);
	
		return res;
	}

     Vec3f CPrimDisc::getSolidTextureCoords(const Ray& ray) const
     {
          return wcs2ocs(ray.hitPoint());
     }

	// Implementation is taken from: https://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	CBoundingBox CPrimDisc::getBoundingBox(void) const
	{
		Vec3f e;
		for (int i = 0; i < 3; i++)
			e[i] = m_radius * sqrtf(1 - m_normal[i] * m_normal[i]);
		return CBoundingBox(m_origin - e, m_origin + e);
	}
}
