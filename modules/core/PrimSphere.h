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
		DllExport CPrimSphere(ptr_shader_t pShader, Vec3f center, float radius)
			: IPrim(pShader)
			, m_center(center)
			, m_radius(radius)
		{}
		DllExport virtual ~CPrimSphere(void) = default;

		DllExport virtual bool intersect(Ray& ray) const override
		{
			// mathematical derivation, numerically not very stable, but simple
			
			// --> find roots of f(t) = ((R+tD)-C)^2 - r^2
			// f(t) = (R-C)^2 + 2(R-C)(tD) + (tD)^2 -r^2
			// --> f(t) = [D^2] t^2 + [2D(R-C)] t + [(R-C)^2 - r^2]
			Vec3f diff = ray.org - m_center;
			float a = ray.dir.dot(ray.dir);
			float b = 2 * ray.dir.dot(diff);
			float c = diff.dot(diff) - m_radius * m_radius;
			
			// use 'abc'-formula for finding root t_1,2 = (-b +/- sqrt(b^2-4ac))/(2a)
			float inRoot = b * b - 4 * a * c;
			if (inRoot < 0) return false;
			float root = sqrtf(inRoot);
			
			float dist = (-b - root) / (2 * a);
			if (dist > ray.t)
				return false;
			
			if (dist < Epsilon) {
				dist = (-b + root) / (2 * a);
				if (dist < Epsilon || dist > ray.t)
					return false;
			}
			
			ray.t = dist;
			ray.hit = shared_from_this();
			return true;
		}
		
		DllExport virtual bool if_intersect(const Ray& ray) const override { return intersect(lvalue_cast(Ray(ray))); }

		/// @todo: Implement this function
		DllExport virtual void transform(const Mat& t) override { printf("CPrimSphere::NOT_IMPLEMENTED\n"); }
		
		DllExport virtual Vec3f getNormal(const Ray& ray) const override { return normalize(ray.hitPoint() - m_center); }
		
		DllExport CBoundingBox	calcBounds(void) const override { return CBoundingBox(m_center - Vec3f::all(m_radius), m_center + Vec3f::all(m_radius)); }
		
	private:
		Vec3f m_center;	///< Position of the center of the sphere
		float m_radius;	///< Radius of the sphere
	};
}
