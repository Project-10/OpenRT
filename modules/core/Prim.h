// Geometrical Primitives base abstract class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"
#include "IShader.h"
#include "BoundingBox.h"

namespace rt {
	//struct Ray;
	
	// ================================ Primitive Interface Class ================================
	/**
	 * @brief Geometrical Primitives (Prims) base abstract class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CPrim : public std::enable_shared_from_this<CPrim>
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the primitive
		 * @param origin Position of the center of the primitive
		 */
		DllExport CPrim(const ptr_shader_t pShader, const Vec3f& origin);
		DllExport CPrim(const CPrim&) = delete;
		DllExport virtual ~CPrim(void) = default;
		DllExport const CPrim& operator=(const CPrim&) = delete;

		/**
		 * @brief Checks for intersection between ray \b ray and the primitive
		 * @details If a valid intersection has been found with the primitive, it sets Ray::t to the distance to this intersection 
		 * point (if current t < ray.t) and sets Ray::hit to point to the current primitive
		 * @param[in,out] ray The ray (Ref. @ref Ray for details)
		 * @retval true If and only if a valid intersection has been found in the interval (epsilon; Ray::t)
		 * @retval false Otherwise
		 */
		DllExport virtual bool						intersect(Ray& ray) const = 0;
		/**
		 * @brief Checks for intersection between ray \b ray and the primitive
		 * @details This function does not modify argument \b ray and is used just to check if there is an intersection.
		 * One may use this function for a fast check if the \b ray.org is occluded from a light source by a primitive.
		 * @param ray The ray (Ref. @ref Ray for details)
		 * @retval true If and only if a valid intersection has been found in the interval (epsilon; Ray::t)
		 * @retval false Otherwise
		 */
		DllExport virtual bool						if_intersect(const Ray& ray) const = 0;
		/**
		 * @brief Returns the texture coordinates in the ray - primitive intersection point
		 * @param ray Ray, which has hit the geometry. 
		 * @return The texture coordinates
		 */
		DllExport virtual Vec2f						getTextureCoords(const Ray& ray) const = 0;
		/**
		 * @brief Calculates derivatives of the primitive's surface over its parametrization parameters \a u and \a v
		 * @param p Point in the WCS
		 * @return A couple of vectors \f$ \frac{\partial p}{\partial u} \f$, \f$ \frac{\partial p}{\partial v} \f$
		 */
		DllExport virtual std::pair<Vec3f, Vec3f>	dp(const Vec3f& p) const = 0;
		/**
		 * @brief Returns the minimum axis-aligned bounding box, which contain the primitive
		 * @return The bounding box, which contain the primitive
		 */
		DllExport virtual CBoundingBox				getBoundingBox(void) const = 0;
		/**
		 * @brief Flips the normal of the primitive.
		 */
		DllExport virtual void						flipNormal(void) { m_flipped = !m_flipped; }
		/**
		 * @brief Returns the center of the primitive
		 * @return The origin point
		 */
		DllExport Vec3f								getOrigin(void) const { return m_origin; }
		/**
		 * @brief Updates the primitive's shader
		 * @param pShader Pointer to the shader to be applied for the primitive
		 */
		DllExport void								setShader(const ptr_shader_t pShader) { m_pShader = pShader; }
		/**
		 * @brief Returns the primitive's shader
		 * @return The pointer to the primitive's shader
		 */
		DllExport ptr_shader_t						getShader(void) const { return m_pShader; }
		/**
		 * @brief Sets a new name to the primitive
		 * @param name The new name
		 */
		DllExport void								setName(const std::string& name) { m_name = name;}
		/**
		 * @brief Returns the name of the primitive
		 * @return The name of the primitive
		 */
		DllExport std::string						getName(void) const { return m_name; }
        /**
		 * @brief Returns normal of the primitive. Flips the normal if it's been set to flip.
         * @param ray Ray intersecting the primitive
		 * @return The normalized normal of the primitive at the ray - primitive intersection point
		 */
        DllExport Vec3f								getNormal(const Ray& ray) const { return m_flipped ? -doGetNormal(ray): doGetNormal(ray); }
        /**
        * @brief Returns the  normal vector of the primitive in the ray - primitive intersection point
        * @note In contrast to the @ref doGetNormal() method, this methods takes into account the possible normal interpolation along the primitive
        * @param ray Ray intersecting the primitive
        * @return The normalized normal of the primitive at the ray - primitive intersection point
        */
        DllExport Vec3f								getShadingNormal(const Ray& ray) const { return m_flipped ? -doGetShadingNormal(ray): doGetShadingNormal(ray); }
		/**
		 * @brief Performs affine transformation
		 * @param T Transformation matrix (size: 4 x 4; type: CV_32FC1)
		 */
		DllExport void								transform(const Mat& T);
		/**
		 * @brief Translates the \a point \b p from World Coordiante System (WCS) to the Object CoordinateSystem (OCS)
		 * @param p Point in the WCS
		 * @return Point \b p in OCS
		 */
		DllExport Vec3f								wcs2ocs(const Vec3f& p) const;
		/**
		* @brief Translates the \a vector \b v from OCS to WCS
		* @param v Vector on OCS
		* @return Vector \b v in WCS
		*/
		DllExport Vec3f								ocs2wcs(const Vec3f& v) const;

		
    private:
		/**
		 * @brief Returns the normal vector of the primitive in the ray - primitive intersection point
		 * @param ray Ray intersecting the primitive
		 * @return The normalized normal of the primitive at the ray - primitive intersection point
		 */
		DllExport virtual Vec3f						doGetNormal(const Ray& ray) const = 0;
		/**
		 * @brief Returns the  normal vector of the primitive in the ray - primitive intersection point
		 * @note In contrast to the @ref doGetNormal() method, this methods takes into account the possible normal interpolation along the primitive
		 * @param ray Ray intersecting the primitive
		 * @return The normalized normal of the primitive at the ray - primitive intersection point
		 */
		DllExport virtual Vec3f						doGetShadingNormal(const Ray& ray) const { return doGetNormal(ray); }
		/**
		 * @brief Performs affine transformation
		 * @param T Transformation matrix (size: 4 x 4; type: CV_32FC1)
		 */
		DllExport virtual void						doTransform(const Mat& T) = 0;
	

	private:
		ptr_shader_t	m_pShader;			///< Pointer to the shader, see @ref  IShader.
		Vec3f			m_origin;			///< Position of the center of the primitive
		std::string		m_name;				///< Optional name of the primitive.
		bool			m_flipped = false;	///< Flag which helps decide whether to flip the normal or not.
		Mat				m_t;				///< The transformation matrix (size: 4 x 4) needed for transition from WCS to OCS
	};
}
