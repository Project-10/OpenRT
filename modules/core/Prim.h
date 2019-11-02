// Geaometrical Primitives base abstract class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"
#include "IShader.h"

namespace rt {
	struct Ray;

	/**
	 * @brief Geometrical Primitives (Prims) base abstract class
	 */
	class IPrim : public std::enable_shared_from_this<IPrim>
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 */
		DllExport IPrim(std::shared_ptr<IShader> pShader) : m_pShader(pShader) {}
		DllExport IPrim(const IPrim&) = delete;
		DllExport virtual ~IPrim(void) = default;
		DllExport const IPrim& operator=(const IPrim&) = delete;

		/**
		 * @brief Checks for intersection between ray \b Ray and the primitive
		 * @details If a valid intersection has been found with the primitive, set Ray::t to the distance to this intersection point (if current t < ray.t)
		 * @param[in,out] ray The ray (Ref. @ref Ray for details)
		 * @retval true If and only if a valid intersection has been found in the interval (epsilon; Ray::t)
		 * @retval false Otherwise
		 */
		DllExport virtual bool	intersect(Ray& ray) = 0;
		/**
		 * @brief Checks if the \b ray.org is occluded
		 * @retval true If the intersection point is occluded
		 * @retval false Otherwise
		 */
		DllExport virtual bool	occluded(Ray& ray) { return intersect(ray); }
		/**
		 * @brief Returns the normalized normal of the primitive
		 * @param ray The ray
		 * @return The normalized normal of the primitive
		 */
		DllExport virtual Vec3f	getNormal(const Ray& ray) const = 0;
		/**
		 * @brief Returns the primitive's shader
		 * @return The pointer to the primitive's shader
		*/
		DllExport std::shared_ptr<IShader> getShader(void) const { return m_pShader; }
	
	
	private:
		std::shared_ptr<IShader>	m_pShader;
	};
}
