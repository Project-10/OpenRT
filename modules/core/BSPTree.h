// BSP node class for BSP trees
// Written by Dr. Sergey G. Kosov in 2019 for Jacobs University
#pragma once

#include "BSPNode.h"

namespace rt {

    // ================================ BSP Tree Class ================================
    /**
     * @brief Binary Space Partitioning (BSP) tree class
     * @author Sergey G. Kosov, sergey.kosov@project-10.de
     */
	class CBSPTree
	{
	public:
		/**
		 * @brief Constructor
		 * @param vpPrims The vector of pointers to the primitives in the scene
		 */
        CBSPTree(const std::vector<ptr_prim_t>& vpPrims);
        CBSPTree(const CBSPTree&) = delete;
        ~CBSPTree(void) = default;
        const CBSPTree& operator=(const CBSPTree&) = delete;
		
        /**
		 * @brief Builds the BSP tree
		 * @details This function builds the BSP tree recursively
		 * @param box The bounding box containing all the scene primitives
		 * @param vpPrims The vector of pointers to the primitives included in the bounding box \b box
		 * @param depth The distance from the root node of the tree
		 */
        ptr_bspnode_t build(const CBoundingBox& box, const std::vector<ptr_prim_t>& vpPrims, size_t depth = 0);
		/**
		 * @brief Checks whether the ray \b ray intersects a primitive.
		 * @details If ray \b ray intersects a primitive, the \b ray.t value will be updated
		 * @param[in,out] ray The ray
		 */
        bool intersect(Ray& ray) const;

		
	private:
		CBoundingBox 	m_boundingBox;
		const size_t    m_maxDepth      = 20;
		const size_t	m_minTri        = 3;
		ptr_bspnode_t   m_root          = nullptr;
	};
}
