// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

namespace rt {
	// ================================ Sphere Primitive Class ================================
	/**
	 * @brief Sphere Geaometrical Primitive class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CPrimSphere : public CPrim
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the primitive
		 * @param origin Position of the center of the sphere
		 * @param radius Radius of the sphere
		 */
		DllExport CPrimSphere(const ptr_shader_t pShader, const Vec3f& origin, float radius)
			: CPrim(pShader)
			, m_origin(origin)
			, m_radius(radius)
		{}
		DllExport virtual ~CPrimSphere(void) = default;

		DllExport virtual bool 			intersect(Ray& ray) const override;
		DllExport virtual bool 			if_intersect(const Ray& ray) const override;
		DllExport virtual void 			transform(const Mat& T) override;
		DllExport virtual Vec3f			getOrigin(void) const override { return m_origin; }
		DllExport virtual Vec2f			getTextureCoords(const Ray& ray) const override;
		DllExport virtual CBoundingBox	getBoundingBox(void) const override;

	
	private:
		DllExport virtual Vec3f 		doGetNormal(const Ray& ray) const override;

		
	private:
		Vec3f	m_origin;	///< Position of the center of the sphere
		float	m_radius;	///< Radius of the sphere
	};
}
