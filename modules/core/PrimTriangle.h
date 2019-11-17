// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"

namespace rt {
	/**
	 * @brief Triangle Geaometrical Primitive class
	 */
	class CPrimTriangle : public IPrim
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 */
		DllExport CPrimTriangle(ptr_shader_t pShader, Vec3f a, Vec3f b, Vec3f c)
			: IPrim(pShader)
			, m_a(a)
			, m_b(b)
			, m_c(c)
			, m_edge1(b - a)
			, m_edge2(c - a)
			, m_normal(normalize(m_edge1.cross(m_edge2)))
		{}
		DllExport virtual ~CPrimTriangle(void) = default;
		
		DllExport virtual bool intersect(Ray& ray) const override
		{
			auto t = MoellerTrumbore(ray);
			if (t) {
				ray.t = t.value().val[0];
				ray.u = t.value().val[1];
				ray.v = t.value().val[2];
				ray.hit = shared_from_this();
				return true;
			}
			else
				return false;
		}

		DllExport virtual bool if_intersect(const Ray& ray) const override { return MoellerTrumbore(ray).has_value(); }

		DllExport virtual Vec3f getNormal(const Ray&) const override { return m_normal; }
		
		DllExport CBoundingBox	calcBounds(void) const override {
			CBoundingBox res;
			res.extend(m_a);
			res.extend(m_b);
			res.extend(m_c);
			return res;
		}
		
	private:
		// Moeller–Trumbore intersection algorithm
		std::optional<Vec3f> MoellerTrumbore(const Ray& ray) const 
		{
			const Vec3f pvec = ray.dir.cross(m_edge2);
			const float det = m_edge1.dot(pvec);
			if (fabs(det) < Epsilon)
				return std::nullopt;

			const float inv_det = 1.0f / det;
			const Vec3f tvec = ray.org - m_a;
			float lambda = tvec.dot(pvec);
			lambda *= inv_det;
			if (lambda < 0.0f || lambda > 1.0f)
				return std::nullopt;

			const Vec3f qvec = tvec.cross(m_edge1);
			float mue = ray.dir.dot(qvec);
			mue *= inv_det;
			if (mue < 0.0f || mue + lambda > 1.0f)
				return std::nullopt;

			float t = m_edge2.dot(qvec);
			t *= inv_det;
			if (ray.t <= t || t < Epsilon)
				return std::nullopt;

			return Vec3f(t, lambda, mue);
		}
		
	protected:
		Vec3f m_a;	///< Position of the first vertex
		Vec3f m_b;	///< Position of the second vertex
		Vec3f m_c;	///< Position of the third vertex
		Vec3f m_edge1;	///< Edge AB
		Vec3f m_edge2;	///< Edge AC
		Vec3f m_normal;	///< Triangle normal
	};
}
