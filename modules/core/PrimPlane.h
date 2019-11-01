// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

namespace rt {
	/**
	 * @brief The Plane Geaometrical Primitive class
	 */
	class CPrimPlane : public CPrim
	{
	public:
		/**
		 * @brief Constructor
		 * @param origin Point on the plane
		 * @param normal Normal to the plane
		 */
		DllExport CPrimPlane(Vec3f origin, Vec3f normal)
			: CPrim()
			, m_normal(normal)
			, m_origin(origin)
		{
			normalize(m_normal);
		}
		DllExport virtual ~CPrimPlane(void) = default;

		DllExport virtual bool Intersect(Ray& ray) override
		{
			float t = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
			if (t < Epsilon || t > ray.t) return false;
			ray.t = t;
			return true;
		}
		
		DllExport virtual Vec3f GetNormal(const Ray& ray) const override
		{
			// --- PUT YOUR CODE HERE ---
			return Vec3f();
		}
		
	private:
		Vec3f m_normal;	///< Point on the plane
		Vec3f m_origin;	///< Normal to the plane
	};
}
