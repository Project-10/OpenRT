// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"

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
		DllExport CPrimPlane(ptr_shader_t pShader, Vec3f origin, Vec3f normal)
			: IPrim(pShader)
			, m_normal(normal)
			, m_origin(origin)
		{
			normalize(m_normal);
		}
		DllExport virtual ~CPrimPlane(void) = default;

		DllExport virtual bool 			intersect(Ray& ray) const override;
		DllExport virtual bool 			if_intersect(const Ray& ray) const override;
		DllExport virtual void 			transform(const Mat& t) override;
		DllExport virtual Vec3f 		getNormal(const Ray&) const override { return m_normal; }
		DllExport virtual CBoundingBox	calcBounds(void) const override;

		
	private:
		Vec3f m_normal;	///< Point on the plane
		Vec3f m_origin;	///< Normal to the plane
	};
}
