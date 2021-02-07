// Axis-Aligned Bounding Box (AABB) class
// Written by Dr. Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "types.h"

namespace rt {
	struct Ray;
    // ================================ AABB Class ================================
    /**
     * @brief Axis-Aligned Bounding Box (AABB) class
     * @author Sergey G. Kosov, sergey.kosov@project-10.de
     */
	class CBoundingBox
	{
	public:
		/**
		 * @brief Constructor
		 * @param minPoint The minimal point defying the size of the bounding box
		 * @param maxPoint The maximal point defying the size of the bounding box
		 */
        DllExport explicit CBoundingBox(const Vec3f& minPoint = Vec3f::all(Infty), const Vec3f& maxPoint = Vec3f::all(-Infty))
			: m_minPoint(minPoint)
			, m_maxPoint(maxPoint)
		{}
        DllExport ~CBoundingBox(void) = default;
        DllExport friend std::ostream& operator<<(std::ostream& os, const CBoundingBox& box) {
			os << box.m_minPoint << " " << box.m_maxPoint;
			return os;
		}

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
         * @brief Splits the bounding box into two parts
         * @details This function splits the bounding box with a plane orthogonal to the axis \b dim. Two resulting bounding boxes are initialized and returned as the result.
         * @param dim The dimension in which the bounding box is splitted: 0 is x, 1 is y and 2 is z
         * @param val The value for the defined dimension where the box is splitted. It must be in range defined my minimal and maximal points of the bounding box
         * @returns A pair of bounding boxes, as a matter of fact "left" and "right" bounding boxes
         */
        DllExport std::pair<CBoundingBox, CBoundingBox> split(int dim, float val) const;
        /**
		 * @brief Checks if the current bounding box overlaps with the argument bounding box \b box
		 * @param box The secind bounding box to be checked with
		 */
        DllExport bool overlaps(const CBoundingBox& box) const;
        /**
         * @brief Clips the ray with the bounding box
         * @details If ray \b ray does not intersect the bounding box, resulting t1 will be smaller than t0
		 * @note This is actually a ray - aabb intersection algorithm
         * @param[in] ray The ray
         * @param[in,out] t0 The distance from ray origin at which the ray enters the bounding box
         * @param[in,out] t1 The distance from ray origin at which the ray leaves the bounding box
         */
        DllExport void clip(const Ray& ray, double& t0, double& t1) const;
        /**
         * @brief Returns the minimal point defying the size of the bounding box
         * @returns The minimal point defying the size of the bounding box
         */
        DllExport Vec3f getMinPoint(void) const { return m_minPoint; }
        /**
         * @brief Returns the maximal point defying the size of the bounding box
         * @returns The maximal point defying the size of the bounding box
         */
        DllExport Vec3f getMaxPoint(void) const { return m_maxPoint; }
        /**
         * @brief Computes the estimated centroid of the bounding box.
         * @returns The point defining the centroid of the bounding box.
         */
        DllExport Vec3f getCenter(void) const { return Vec3f((m_minPoint[0] + m_maxPoint[0]) / 2, (m_minPoint[1] + m_maxPoint[1]) / 2, (m_minPoint[2] + m_maxPoint[2]) / 2); }
		
        
	private:
        Vec3f m_minPoint;	///< The minimal point defying the size of the bounding box
        Vec3f m_maxPoint;	///< The maximal point defying the size of the bounding box
	};
}
