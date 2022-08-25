// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

namespace rt {
	// ================================ Infinite Plane Primitive Class ================================
	/**
	 * @brief The Plane Geometrical Primitive class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CPrimPlane : public CPrim
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 * @param origin Point on the plane
		 * @param normal Normal to the plane
		 */
		DllExport CPrimPlane(const ptr_shader_t pShader, const Vec3f& origin, const Vec3f& normal)
			: CPrim(pShader)
			, m_normal(normal)
			, m_origin(origin)
		{
			normalize(m_normal);
		}
		DllExport virtual ~CPrimPlane(void) = default;

		DllExport virtual bool 			intersect(Ray& ray) const override;
		DllExport virtual bool 			if_intersect(const Ray& ray) const override;
		DllExport virtual void 			transform(const Mat& T) override;
		DllExport virtual Vec3f			getOrigin(void) const override { return m_origin; }
		DllExport virtual Vec2f			getTextureCoords(const Ray& ray) const override;
		DllExport virtual CBoundingBox	getBoundingBox(void) const override;

		
	private:
		DllExport virtual Vec3f 		doGetNormal(const Ray&) const override { return m_normal; }
		
		
	private:
		Vec3f m_normal;	///< Point on the plane
		Vec3f m_origin;	///< Normal to the plane
	};
}
