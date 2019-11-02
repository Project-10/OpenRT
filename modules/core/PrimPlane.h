// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

namespace rt {
	/**
	 * @brief The Plane Geaometrical Primitive class
	 */
	class CPrimPlane : public IPrim
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 * @param origin Point on the plane
		 * @param normal Normal to the plane
		 */
		DllExport CPrimPlane(std::shared_ptr<IShader> pShader, Vec3f origin, Vec3f normal)
			: IPrim(pShader)
			, m_normal(normal)
			, m_origin(origin)
		{
			normalize(m_normal);
		}
		DllExport virtual ~CPrimPlane(void) = default;

		DllExport virtual bool intersect(Ray& ray) override
		{
			float t = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
			if (t < Epsilon || t > ray.t) return false;
			ray.t = t;
			ray.hit = shared_from_this();
			return true;
		}
		
		DllExport virtual Vec3f getNormal(const Ray& ray) const override { return m_normal; }
		
	private:
		Vec3f m_normal;	///< Point on the plane
		Vec3f m_origin;	///< Normal to the plane
	};
}
