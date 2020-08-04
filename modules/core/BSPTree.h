#pragma once

#include "BSPNode.h"
#include "BoundingBox.h"
#include "macroses.h"

namespace rt {
	namespace {
		inline int MaxDim(Vec3f v)
		{
			return (v.val[0] > v.val[1]) ? ((v.val[0] > v.val[2]) ? 0 : 2) : ((v.val[1] > v.val[2]) ? 1 : 2);
		}
	}

	class BSPTree
	{
	public:
		/**
		 * @brief Constructor
		 * @param bounds The scene bounding box
		 * @param vpPrims The vector of pointers to the primitives in the scene
		 */
		BSPTree(CBoundingBox& bounds, const std::vector<ptr_prim_t>& vpPrims)
			: m_bounds(bounds)
			, m_maxDepth(20)
			, m_minTri(3)
			, m_root(nullptr)
		{
			m_root = buildTree(bounds, vpPrims, 0);
		}
		
		/**
		 * @brief Builds the BSP tree
		 * @details This function builds the BSP tree recursively
		 * @param box The bounding box containing all the scene primitives
		 * @param vpPrims The vector of pointers to the primitives included in the bounding box \b box
		 * @param depth The distance from the root node of the tree
		 */
		std::shared_ptr<CBSPNode> buildTree(const CBoundingBox& box, const std::vector<ptr_prim_t>& vpPrims, int depth)
		{
			if (depth > m_maxDepth || vpPrims.size() <= m_minTri) {
				// could do some optimizations here..
				return std::make_shared<CBSPNode>(vpPrims);
			}

			Vec3f diam = box.m_max - box.m_min;

			int splitDim = MaxDim(diam);

			CBoundingBox lBounds = box;
			CBoundingBox rBounds = box;

			float splitVal = lBounds.m_max[splitDim] = rBounds.m_min[splitDim] = (box.m_min[splitDim] + box.m_max[splitDim]) * 0.5f;

			std::vector<ptr_prim_t> lPrim;
			std::vector<ptr_prim_t> rPrim;

			for (auto pPrim : vpPrims) {
				if (pPrim->calcBounds().overlaps(lBounds))
					lPrim.push_back(pPrim);
				if (pPrim->calcBounds().overlaps(rBounds))
					rPrim.push_back(pPrim);
			}

			auto pLeft  = buildTree(lBounds, lPrim, depth + 1);
			auto pRight = buildTree(rBounds, rPrim, depth + 1);

			return std::make_shared<CBSPNode>(splitVal, splitDim, pLeft, pRight);
		}

		/**
		 * @brief Checks whether the ray \b ray intersects a primitive.
		 * @details If ray \b ray intersects a primitive, the \b ray.t value will be updated
		 * @param[in,out] ray The ray
		 */
		bool intersect(Ray& ray)
		{
			RT_ASSERT(!ray.hit);
			
			double t0 = 0;
			double t1 = ray.t;

			m_bounds.clip(ray, t0, t1);

			if (t1 - t0 < Epsilon)
				return false;

			m_root->traverse(ray, t0, t1);

			if (ray.hit)
				return true;

			return false;
		}

		
	private:
		CBoundingBox 				m_bounds;
		const int 	 				m_maxDepth;
		const size_t	 			m_minTri;
		std::shared_ptr<CBSPNode> 	m_root;
	};
}
