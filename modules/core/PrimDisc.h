// Disc Geaometrical Primitive class
// Written by Dr. Sergey Kosov in 2021 for Jacobs University
#pragma once

#include "CPrim.h"

namespace rt {
	// ================================ Disc Primitive Class ================================
	/**
	 * @brief The Disc Geometrical Primitive class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CPrimDisc : public CPrim
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 * @param origin The center pointof the disc
		 * @param normal Normal to the disc
		 * @param radius Radius of the disc
		 */
		DllExport CPrimDisc(const ptr_shader_t pShader, const Vec3f& origin, const Vec3f& normal, float radius)
			: CPrim(pShader, origin)
			, m_origin(origin)
			, m_normal(normal)
			, m_radius(radius)
			, m_u(normal[1] < 1.0f ? Vec3f(0, 1, 0).cross(normal) : normal.cross(Vec3f(0, 0, 1)))
			, m_v(m_u.cross(normal))
			, m_r(radius)
		{}
		DllExport virtual ~CPrimDisc(void) = default;
		
		DllExport virtual bool				intersect(Ray& ray) const override;
		DllExport virtual bool				if_intersect(const Ray& ray) const override;
		DllExport virtual Vec3f				getOrigin(void) const override { return m_origin; }
		DllExport virtual Vec2f				getTextureCoords(const Ray& ray) const override;
		DllExport virtual CBoundingBox		getBoundingBox(void) const override;
		

	private:
		DllExport virtual void				doTransform(const Mat& T) override;
		DllExport virtual Vec3f				doGetNormal(const Ray&) const override { return m_normal; }
		
		
	private:
		Vec3f m_normal;		///< Point on the plane
		Vec3f m_origin;		///< Normal to the plane
		float m_radius;		///< Radius of the disc

		const Vec3f m_u;	///< Vector orthogonal to the normal and \b m_v (used for texturing)
		const Vec3f m_v;	///< Vector orthogonal to the normal and \b m_u (used for texturing)
		const float m_r;	///< The initial radius if the disc (used for texturing)
	};
}
