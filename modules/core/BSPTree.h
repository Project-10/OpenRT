// BSP node class for BSP trees
// Written by Dr. Sergey G. Kosov in 2019 for Jacobs University
#pragma once

#include "BSPNode.h"
#include "BoundingBox.h"

namespace rt {
    // ================================ BSP Tree Class ================================
    /**
     * @brief Binary Space Partitioning (BSP) tree class
     * @author Sergey G. Kosov, sergey.kosov@project-10.de
     */
	class CBSPTree
	{
	public:
		CBSPTree(void) = default;
        CBSPTree(const CBSPTree&) = delete;
        ~CBSPTree(void) = default;
        const CBSPTree& operator=(const CBSPTree&) = delete;
		
		/**
		* @brief Builds the BSP tree for the primitives provided via \b vpPrims
		* @param vpPrims The vector of pointers to the primitives in the scene
		* @param maxDepth The maximum allowed depth of the tree.
		* Increasing the depth of the tree may speed-up rendering, but increse the memory consumption.
		* @param minPrimitives The minimum number of primitives in a leaf-node.
		* This parameters should be alway above 1.
		*/
		void build(const std::vector<ptr_prim_t>& vpPrims, size_t maxDepth = 20, size_t minPrimitives = 3);
		/**
		 * @brief Checks whether the ray \b ray intersects a primitive.
		 * @details If ray \b ray intersects a primitive, the \b ray.t value will be updated
		 * @param[in,out] ray The ray
		 */
		bool intersect(Ray& ray) const;


	private:
        /**
		 * @brief Recursively builds the BSP tree
		 * @details This function builds the BSP tree recursively
		 * @param box The bounding box containing all the scene primitives
		 * @param vpPrims The vector of pointers to the primitives included in the bounding box \b box
		 * @param depth The distance from the root node of the tree
		 */
        ptr_bspnode_t build(const CBoundingBox& box, const std::vector<ptr_prim_t>& vpPrims, size_t depth = 0);

		
	private:
		CBoundingBox 	m_treeBoundingBox;		///<
		size_t			m_maxDepth;				///< The maximum allowed depth of the tree
		size_t			m_minPrimitives;		///< The minimum number of primitives in a leaf-node
		ptr_bspnode_t   m_root = nullptr;		///<
	};
}
