// Smoothed Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "PrimTriangle.h"
#include "Transform.h"

namespace rt {
	// ================================ Smooth Triangle Primitive Class ================================
	/**
	 * @brief Triangle Geaometrical Primitive class with interpolation of normal
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
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
		
		DllExport virtual void	transform(const Mat& T) override;
		DllExport virtual Vec3f	getNormal(const Ray& ray) const override;


	private:
		Vec3f m_na;		///< Normal at vertex a
		Vec3f m_nb;		///< Normal at vertex b
		Vec3f m_nc;		///< Normal at vertex c
	};

}
