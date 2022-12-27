// Disc Geaometrical Primitive class
// Written by Dr. Sergey Kosov in 2021 for Jacobs University
#pragma once

#include "Prim.h"

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
		 * @param innerRadius The disc can also be generalized to an annulus by specifying an inner radius
		 */
		DllExport CPrimDisc(const ptr_shader_t pShader, const Vec3f& origin, const Vec3f& normal, float radius, float innerRadius = 0.0f)
			: CPrim(pShader, origin)
			, m_normal(normal)
			, m_radius(radius)
			, m_innerRadius(innerRadius)
			, m_n(normal)
			, m_t(normal[1] < 1.0f ? Vec3f(0, 1, 0).cross(normal) : normal.cross(Vec3f(0, 0, 1)))
			, m_r(radius)
			, m_ri(innerRadius)
		{}
		DllExport virtual ~CPrimDisc(void) = default;
		
		DllExport virtual bool						intersect(Ray& ray) const override;
		DllExport virtual bool						if_intersect(const Ray& ray) const override;
		DllExport virtual Vec2f						getTextureCoords(const Ray& ray) const override;
		DllExport virtual std::pair<Vec3f, Vec3f>	dp(const Vec3f& p) const;
		DllExport virtual CBoundingBox				getBoundingBox(void) const override;
		

	private:
		DllExport virtual Vec3f						doGetNormal(const Ray&) const override { return m_normal; }
		DllExport virtual void						doTransform(const Mat& T) override;
		

	private:
		Vec3f m_normal;			///< The normal to the plane
		float m_radius;			///< The radius of the disc
		float m_innerRadius;	///< The inner radius of the disc, if larger than 0, specifies an annulus
		
		const Vec3f m_n;		///< The initial normal vector (used for texturing)
		const Vec3f m_t;		///< A vector orthogonal to normal and lying on the disc surface (used for texturing)
		const float m_r;		///< The initial radius of the disc (used for texturing)
		const float m_ri;		///< The initial inner radius of the disc (used for texturing)
	};
}
