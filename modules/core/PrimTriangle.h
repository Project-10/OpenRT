// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"

namespace rt {
	// ================================ Triangle Primitive Class ================================
	/**
	 * @brief Triangle Geometrical Primitive class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
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
		 * @param ta Texture coordinate for the first vertex
		 * @param tb Texture coordinate for the second vertex
		 * @param tc Texture coordinate for the third vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 */
		DllExport CPrimTriangle(const ptr_shader_t pShader, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec2f& ta = Vec2f::all(0), const Vec2f& tb = Vec2f::all(0), const Vec2f& tc = Vec2f::all(0), std::optional<Vec3f> na = std::nullopt, std::optional<Vec3f> nb = std::nullopt, std::optional<Vec3f> nc = std::nullopt)
			: IPrim(pShader)
			, m_a(a)
			, m_b(b)
			, m_c(c)
			, m_ta(ta)
			, m_tb(tb)
			, m_tc(tc)
			, m_na(na)
			, m_nb(nb)
			, m_nc(nc)
			, m_edge1(b - a)
			, m_edge2(c - a)
			, m_normal(normalize(m_edge1.cross(m_edge2)))
		{}
		DllExport virtual ~CPrimTriangle(void) = default;
		
		DllExport virtual bool	intersect(Ray& ray) const override;
		DllExport virtual bool	if_intersect(const Ray& ray) const override { return MoellerTrumbore(ray).has_value(); }
		DllExport virtual void	transform(const Mat& t) override;
		DllExport virtual Vec3f	getOrigin(void) const override;
		DllExport virtual Vec3f doGetNormal(const Ray& ray) const override;
		DllExport virtual Vec3f doGetShadingNormal(const Ray& ray) const override;
		DllExport virtual Vec2f	getTextureCoords(const Ray& ray) const override;
		DllExport CBoundingBox	getBoundingBox(void) const override;
		
		
	private:
		// Moeller-Trumbore intersection algorithm
		DllExport std::optional<Vec3f> MoellerTrumbore(const Ray& ray) const;
		
		
	protected:
		Vec3f m_a;						///< Position of the first vertex
		Vec3f m_b;						///< Position of the second vertex
		Vec3f m_c;						///< Position of the third vertex
		Vec2f m_ta;						///< Vertex a texture coordiante
		Vec2f m_tb;						///< Vertex b texture coordiante
		Vec2f m_tc;						///< Vertex c texture coordiante
		std::optional<Vec3f> m_na;		///< Normal at vertex a
		std::optional<Vec3f> m_nb;		///< Normal at vertex b
		std::optional<Vec3f> m_nc;		///< Normal at vertex c
		Vec3f m_edge1;					///< Edge AB
		Vec3f m_edge2;					///< Edge AC
		Vec3f m_normal;					///< Triangle normal
	};
}
