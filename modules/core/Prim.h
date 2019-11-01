// Geaometrical Primitives base abstract class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"

namespace rt {
	struct Ray;

	/**
	 * @brief Geometrical Primitives (Prims) base abstract class
	 */
	class CPrim
	{
	public:
		/**
		* @brief Constructor
		*/
		DllExport CPrim(void) = default;
		DllExport CPrim(const CPrim&) = delete;
		DllExport virtual ~CPrim(void) = default;
		DllExport const CPrim& operator=(const CPrim&) = delete;

		/**
		 * @brief Checks for intersection between ray \b Ray and the primitive
		 * @details If a valid intersection has been found with the primitive, set Ray::t to the distance to this intersection point (if current t < ray.t)
		 * @param[in,out] ray The ray (Ref. @ref Ray for details)
		 * @retval true If and only if a valid intersection has been found in the interval (epsilon; Ray::t)
		 * @retval false Otherwise
		 */
		DllExport virtual bool	Intersect(Ray& ray) = 0;
		/**
		 * @brief Checks if the \b ray.org is occluded
		 */
		DllExport virtual bool	Occluded(Ray& ray) { return Intersect(ray); }
		/**
		 * @brief Returns the normalized normal of the primitive
		 * @param ray The ray
		 * @return The normalized normal of the primitive
		 */
		DllExport virtual Vec3f	GetNormal(const Ray& ray) const = 0;
	};
}
