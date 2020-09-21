// Axis - Aligned Bounding Box (AABB) class
// Written by Dr. Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "types.h"

namespace rt {
	struct Ray;

    // ================================ AABB Class ================================
    /**
     * @brief Axis Aligned Bounding Box (AABB) class
     * @author  Sergey G. Kosov, sergey.kosov@project-10.de
    */
	class CBoundingBox
	{
	public:
		/**
		 * @brief Constructor
		 * @param minPoint The minimal point defying the size of the bounding box
		 * @param maxPoint The maximal point defying the size of the bounding box
		*/
		DllExport CBoundingBox(const Vec3f& minPoint = Vec3f::all(std::numeric_limits<float>::infinity()), const Vec3f& maxPoint = Vec3f::all(-std::numeric_limits<float>::infinity()))
			: m_min(minPoint)
			, m_max(maxPoint) 
		{}
		DllExport ~CBoundingBox(void)= default;
		
		/**
		 * @brief Resets the bounding box
		 * @details This function resets the member variables \b m_min and \b m_max
		 */
		DllExport void clear(void);
		/**
		 * @brief Extends the bounding box to contain point \b p
		 * @param p A point
		 */
		DllExport void extend(const Vec3f& p);
		/**
		 * @brief Extends the bounding box to contain bounding box \b box
		 * @param box The second bounding box
		 */
		DllExport void extend(const CBoundingBox& box);
		/**
		 * @brief Checks if the current bounding box overlaps with the argument bounding box \b box
		 * @param box The secind bounding box to be checked with
		 */
		DllExport bool overlaps(const CBoundingBox& box);
		/**
		 * @brief Clips the ray with the bounding box
		 * @param[in] ray The ray
		 * @param[in,out] t0 The distance from ray origin at which the ray enters the bounding box
		 * @param[in,out] t1 The distance from ray origin at which the ray leaves the bounding box
		 */
		DllExport void clip(const Ray& ray, double& t0, double& t1) const;
		
		
	public:
        Vec3f m_min;	///< The minimal point defying the size of the bounding box
        Vec3f m_max;	///< The maximal point defying the size of the bounding box
	};
}
