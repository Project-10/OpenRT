// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

namespace rt {
	// ================================ Sphere Primitive Class ================================
	/**
	 * @brief Sphere Geaometrical Primitive class
	 * @details The sphere is parametrized as \f$ \left\{\begin{array}{l} x=r\sin\theta\cos\phi\\ y=r\cos\theta\\ z=-r\sin\theta\cos\phi\end{array}\right. \f$
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
			: CPrim(pShader, origin)
			, m_radius(radius)
		{}
		DllExport virtual ~CPrimSphere(void) = default;

		DllExport virtual bool 						intersect(Ray& ray) const override;
		DllExport virtual bool 						if_intersect(const Ray& ray) const override;
		DllExport virtual Vec2f						getTextureCoords(const Ray& ray) const override;
		DllExport virtual std::pair<Vec3f, Vec3f>	dp(const Vec3f& p) const override;
		DllExport virtual CBoundingBox				getBoundingBox(void) const override;

	
	private:
		DllExport virtual Vec3f 					doGetNormal(const Ray& ray) const override;
		DllExport virtual void						doTransform(const Mat& T) override;
		

	private:
		float	m_radius;	///< Radius of the sphere
	};
}
