// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"

namespace rt {
	/**
	 * @brief Sphere Geaometrical Primitive class
	 */
	class CPrimSphere : public IPrim
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 * @param center Position of the center of the sphere
		 * @param radius Radius of the sphere
		 */
		DllExport CPrimSphere(ptr_shader_t pShader, Vec3f origin, float radius)
			: IPrim(pShader)
			, m_origin(origin)
			, m_radius(radius)
		{}
		DllExport virtual ~CPrimSphere(void) = default;

		DllExport virtual bool 			intersect(Ray& ray) const override;
		DllExport virtual bool 			if_intersect(const Ray& ray) const override;
		DllExport virtual void 			transform(const Mat& t) override;
		DllExport virtual Vec3f 		getNormal(const Ray& ray) const override;
		DllExport virtual CBoundingBox	calcBounds(void) const override { return CBoundingBox(m_origin - Vec3f::all(m_radius), m_origin + Vec3f::all(m_radius)); }
		
		
	private:
		Vec3f m_origin;	///< Position of the center of the sphere
		float m_radius;	///< Radius of the sphere
	};
}
