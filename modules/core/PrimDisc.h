// Disc Geaometrical Primitive class
// Written by Dr. Sergey Kosov in 2021 for Jacobs University
#pragma once

#include "IPrim.h"

namespace rt {
	// ================================ Disc Primitive Class ================================
	/**
	 * @brief The Disc Geometrical Primitive class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CPrimDisc : public IPrim
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
			: IPrim(pShader)
			, m_normal(normal)
			, m_origin(origin)
			, m_radius(radius)
               , m_t(Mat::eye(4, 4, CV_32FC1))
		{
               for (int i = 0; i < 3; i++) m_t.at<float>(i, 3) = m_origin[i];

          }
		DllExport virtual ~CPrimDisc(void) = default;
		
		DllExport virtual bool				intersect(Ray& ray) const override;
		DllExport virtual bool				if_intersect(const Ray& ray) const override;
		DllExport virtual void				transform(const Mat& T) override;
		DllExport virtual Vec3f				getOrigin(void) const override { return m_origin; }
		DllExport virtual Vec2f				getTextureCoords(const Ray& ray) const override;
		DllExport virtual Vec3f				getSolidTextureCoords(const Ray& ray) const override;
		DllExport virtual CBoundingBox		getBoundingBox(void) const override;
		
	private:
		DllExport virtual Vec3f				doGetNormal(const Ray&) const override { return m_normal; }
		
		
	private:
          Mat m_t;
		Vec3f m_normal;		///< Point on the plane
		Vec3f m_origin;		///< Normal to the plane
		float m_radius;		///< Radius of the disc
	};
}
