#pragma once

#include "PrimTriangle.h"
#include "IShader.h"
#include "Transform.h"

namespace rt {
	/**
	* @brief Triangle Geaometrical Primitive class with interpolation of normal
	*/
	class CPrimTriangleSmooth : public CPrimTriangle
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 */
		DllExport CPrimTriangleSmooth(ptr_shader_t pShader, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& na, const Vec3f& nb, const Vec3f& nc)
			: CPrimTriangle(pShader, a, b, c)
			, m_na(na)
			, m_nb(nb)
			, m_nc(nc)
		{}
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 */
		DllExport CPrimTriangleSmooth(ptr_shader_t pShader, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec2f& ta, const Vec2f& tb, const Vec2f& tc, const Vec3f& na, const Vec3f& nb, const Vec3f& nc)
			: CPrimTriangle(pShader, a, b, c, ta, tb, tc)
			, m_na(na)
			, m_nb(nb)
			, m_nc(nc)
		{}
		DllExport virtual ~CPrimTriangleSmooth(void) = default;
		
		DllExport virtual void transform(const Mat& t) override
		{
			// Transform vertexes
			m_a = CTransform::point(m_a, t);
			m_b = CTransform::point(m_b, t);
			m_c = CTransform::point(m_c, t);
			
			// Transform normals
			Mat t1 = t.inv().t();
			
			m_na = normalize(CTransform::vector(m_na, t1));
			m_nb = normalize(CTransform::vector(m_nb, t1));
			m_nc = normalize(CTransform::vector(m_nc, t1));
			
			m_edge1 = m_b - m_a;
			m_edge2 = m_c - m_a;
		}
		
		DllExport virtual Vec3f getNormal(const Ray& ray) const override
		{
			// assume u/v coordinates in ray correspond to beta(u) and gamma(v) barycentric coordinates of 
			// hitpoint on triangle (have to be stored like this in the intersection code!)
			return  normalize(ray.u * m_nb + ray.v * m_nc + (1.0f - ray.u - ray.v) * m_na);
		}


	private:
		Vec3f m_na;		///< Normal at vertex a
		Vec3f m_nb;		///< Normal at vertex b
		Vec3f m_nc;		///< Normal at vertex c
	};

}
