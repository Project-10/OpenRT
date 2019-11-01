// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

namespace rt {
	/**
	 * @brief Triangle Geaometrical Primitive class
	 */
	class CPrimTriangle : public CPrim
	{
	public:
		/**
		 * @brief Constructor
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 */
		DllExport CPrimTriangle(Vec3f a, Vec3f b, Vec3f c)
			: CPrim()
			, m_a(a)
			, m_b(b)
			, m_c(c)
		{}
		DllExport virtual ~CPrimTriangle(void) = default;
		
		DllExport virtual bool Intersect(Ray& ray) override
		{
			const Vec3f edge1 = m_b - m_a;
			const Vec3f edge2 = m_c - m_a;
			
			const Vec3f pvec = ray.dir.cross(edge2);
			
			const float det = edge1.dot(pvec);
			if (fabs(det) < Epsilon) return false;
			
			const float inv_det = 1.0f / det;
			
			const Vec3f tvec = ray.org - m_a;
			float lambda = tvec.dot(pvec);
			lambda *= inv_det;
			
			if (lambda < 0.0f || lambda > 1.0f) return false;
			
			const Vec3f qvec = tvec.cross(edge1);
			float mue = ray.dir.dot(qvec);
			mue *= inv_det;
			
			if (mue < 0.0f || mue + lambda > 1.0f) return false;
			
			float f = edge2.dot(qvec);
			f *= inv_det;
			if (ray.t <= f || f <  1E-4  ) return false;
			
			ray.t = f;
			
			return true;
		}

		DllExport virtual Vec3f GetNormal(const Ray& ray) const override
		{
			// --- PUT YOUR CODE HERE ---
			return Vec3f();
		}
		
	private:
		Vec3f m_a;	///< Position of the first vertex
		Vec3f m_b;	///< Position of the second vertex
		Vec3f m_c;	///< Position of the third vertex
	};
}
