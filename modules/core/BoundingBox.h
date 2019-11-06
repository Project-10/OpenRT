#pragma once

#include "types.h"

namespace rt {
	struct Ray;

	/**
	 * @brief Bounding Box class
	 */
	class CBoundingBox
	{
	public:
		CBoundingBox(void) = default;
		~CBoundingBox(void)= default;
		
		/**
		 * @brief Resets the bounding box
		 * @details This function resets the member variables \b m_min and \b m_max
		 */
		void clear(void);
		/**
		 * @brief Extends the bounding box to contain point \b a
		 * @param a A point
		 */
		void extend(Vec3f a);
		/**
		 * @brief Extends the bounding box to contain bounding box \b box
		 * @param box The second bounding box
		 */
		void extend(const CBoundingBox& box);
		/**
		 * @brief Checks if the current bounding box overlaps with the argument bounding box \b box
		 * @param box The secind bounding box to be checked with
		 */
		bool overlaps(const CBoundingBox& box);
		/**
		 * @brief Clips the ray with the bounding box
		 * @param[in] ray The ray
		 * @param[in,out] t0 The distance from ray origin at which the ray enters the bounding box
		 * @param[in,out] t1 The distance from ray origin at which the ray leaves the bounding box
		 */
		void clip(const Ray& ray, float& t0, float& t1);
		
		
	public:
		Vec3f m_min = Vec3f::all(std::numeric_limits<float>::infinity());	///< The minimal point defying the size of the bounding box
		Vec3f m_max = Vec3f::all(-std::numeric_limits<float>::infinity());	///< The maximal point defying the size of the bounding box
	};
}
