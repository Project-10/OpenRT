// Axis-Aligned Bounding Box (AABB) class
// Written by Dr. Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "types.h"

namespace rt {

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
		CBoundingBox(const Vec3f& minPoint = Vec3f::all(Infty), const Vec3f& maxPoint = Vec3f::all(-Infty))
			: m_minPoint(minPoint)
			, m_maxPoint(maxPoint)
		{}
		~CBoundingBox(void) = default;
		friend std::ostream& operator<<(std::ostream& os, const CBoundingBox& box) {
			os << box.m_minPoint << " " << box.m_maxPoint;
			return os;
		}

		/**
		 * @brief Extends the bounding box to contain point \b p
		 * @param p A point
		 */
		void extend(const Vec3f& p);
		/**
		 * @brief Extends the bounding box to contain bounding box \b box
		 * @param box The second bounding box
		 */
		void extend(const CBoundingBox& box);
		/**
         * @brief Splits the bounding box into two parts
         * @details This function splits the bounding box with a plane orthogonal to the axis \b dim. Two resulting bounding boxes are initialized and returned as the result.
         * @param dim The dimension in which the bounding box is splitted: 0 is x, 1 is y and 2 is z
         * @param val The value for the defined dimension where the box is splitted. It must be in range defined my minimal and maximal points of the bounding box
         * @returns A pair of bounding boxes, as a matter of fact "left" and "right" bounding boxes
         */
        std::pair<CBoundingBox, CBoundingBox> split(int dim, float val) const;
        /**
		 * @brief Checks if the current bounding box overlaps with the argument bounding box \b box
		 * @param box The secind bounding box to be checked with
		 */
		bool overlaps(const CBoundingBox& box) const;
		
        /**
         * @brief Returns the minimal point defying the size of the bounding box
         * @returns The minimal point defying the size of the bounding box
         */
        Vec3f getMinPoint(void) const { return m_minPoint; }
        /**
         * @brief Returns the maximal point defying the size of the bounding box
         * @returns The maximal point defying the size of the bounding box
         */
        Vec3f getMaxPoint(void) const { return m_maxPoint; }
		
        
	private:
        Vec3f m_minPoint;	///< The minimal point defying the size of the bounding box
        Vec3f m_maxPoint;	///< The maximal point defying the size of the bounding box
	};
}
