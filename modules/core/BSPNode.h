// BSP node class for BSP trees
// Written by Dr. Sergey G. Kosov in 2019 for Jacobs University
#pragma once

#include "types.h"
#include "ray.h"

namespace rt {
	class CBSPNode
	{
	public:
		/**
		 * @brief Leaf node constructor
		 * @param vpPrims The vector of pointers to the primitives included in the leaf node
		 */
		CBSPNode(const std::vector<ptr_prim_t>& vpPrims)
			: CBSPNode(vpPrims, 0, 0, nullptr, nullptr)
		{}
		/**
		 * @brief Branch node constructor
		 * @param splitVal The splitting value
		 * @param splitDim The splitting dimension
		 * @param left Pointer to the left sub-tree
		 * @param right Pointer to the right sub-tree
		 */
		CBSPNode(float splitVal, int splitDim, std::shared_ptr<CBSPNode> left, std::shared_ptr<CBSPNode> right)
			: CBSPNode(std::nullopt, splitVal, splitDim, left, right)
		{}
		CBSPNode(const CBSPNode&) = delete;
		virtual ~CBSPNode(void) = default;
		const CBSPNode& operator=(const CBSPNode&) = delete;

		/**
		 * @brief Checks whether the node is either leaf or branch node
		 * @retval true if the node is the leaf-node
		 * @retval false if the node is a branch-node
		 */
		bool isLeaf(void) const { return (!m_pLeft && ! m_pRight); }
		
		/**
		 * @brief Traverses the ray \b ray and checks for intersection with a primitive
		 * @details If the intersection is found, \b ray.t is updated
		 * @param[in,out] ray The ray
		 * @param[in,out] t0 The distance from ray origin at which the ray enters the scene
		 * @param[in,out] t1 The distance from ray origin at which the ray leaves the scene
		 */
		virtual bool traverse(Ray& ray, double& t0, double& t1)
		{
			if (isLeaf()) {
				for (auto pPrim : m_vpPrims)
					pPrim->intersect(ray);
				return (ray.hit != NULL && ray.t < t1);
			}
			else {
				double d = (m_splitVal - ray.org[m_splitDim]) / ray.dir[m_splitDim];

				auto frontNode = (ray.dir[m_splitDim] < 0) ? Right() : Left();
				auto backNode = (ray.dir[m_splitDim] < 0) ? Left() : Right();

				if (d <= t0) {
					// t0..t1 is totally behind d, only go to back side
					return backNode->traverse(ray, t0, t1);
				}
				else if (d >= t1) {
					// t0..t1 is totally in front of d, only go to front side
					return frontNode->traverse(ray, t0, t1);
				}
				else {
					// travese both children. front one first, back one last
					if (frontNode->traverse(ray, t0, d))
						return true;

					return backNode->traverse(ray, d, t1);
				}
			}
		}

		/**
		 * @brief Returns the pointer to the \a left child
		 * @returns The pointer to the root-node of the \a left sub-tree
		 */
		std::shared_ptr<CBSPNode> Left(void) const { return m_pLeft; }
		/**
		 * @brief Returns the pointer to the \a right child
		 * @returns The pointer to the root-node of the \a right sub-tree
		 */
		std::shared_ptr<CBSPNode> Right(void) const { return m_pRight; }

		
	private:
		CBSPNode(std::optional<std::vector<ptr_prim_t>> vpPrims, float splitVal, int splitDim, std::shared_ptr<CBSPNode> left, std::shared_ptr<CBSPNode> right)
			: m_splitVal(splitVal)
			, m_splitDim(splitDim)
			, m_pLeft(left)
			, m_pRight(right)
		{
			if (vpPrims) m_vpPrims = vpPrims.value();
		}
		
		
	private:
		std::vector<ptr_prim_t> m_vpPrims;
		float 					 			m_splitVal;
		int 					 			m_splitDim;
		std::shared_ptr<CBSPNode> 			m_pLeft;
		std::shared_ptr<CBSPNode> 			m_pRight;
	};
}
