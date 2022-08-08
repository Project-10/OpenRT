#include "BSPTree.h"
#include "CPrim.h"
#include "Ray.h"
#include "macroses.h"

namespace rt {
    namespace {
        // Calculates and return the bounding box, containing the whole scene
        CBoundingBox calcBoundingBox(const std::vector<ptr_prim_t>& vpPrims)
        {
            CBoundingBox res;
            for (auto pPrim : vpPrims)
                res.extend(pPrim->getBoundingBox());
            return res;
        }

        // Returns the best dimension index for next split
        int MaxDim(const Vec3f& v)
        {
            return (v.val[0] > v.val[1]) ? ((v.val[0] > v.val[2]) ? 0 : 2) : ((v.val[1] > v.val[2]) ? 1 : 2);
        }
    }

    void CBSPTree::build(const std::vector<ptr_prim_t>& vpPrims, size_t maxDepth, size_t minPrimitives)
    {
        m_treeBoundingBox = calcBoundingBox(vpPrims);
        m_maxDepth = maxDepth;
        m_minPrimitives = minPrimitives;
#ifdef DEBUG_PRINT_INFO
        std::cout << "Scene bounds are : " << m_treeBoundingBox << std::endl;
#endif
        m_root = build(m_treeBoundingBox, vpPrims, 0);
    }

    bool CBSPTree::intersect(Ray& ray) const
    {
        RT_ASSERT(!ray.hit);

        double t0 = 0;
        double t1 = ray.t;
        m_treeBoundingBox.clip(ray, t0, t1);
        if (t1 < t0) return false;  // no intersection with the bounding box

        return m_root->intersect(ray, t0, t1);
    }

    ptr_bspnode_t CBSPTree::build(const CBoundingBox& box, const std::vector<ptr_prim_t>& vpPrims, size_t depth)
    {
        // Check for stopping criteria
        if (depth >= m_maxDepth || vpPrims.size() <= m_minPrimitives)
            return std::make_shared<CBSPNode>(vpPrims);                                     // => Create a leaf node and break recursion

        // else -> prepare for creating a branch node
        // First split the bounding volume into two halfes
        int     splitDim = MaxDim(box.getMaxPoint() - box.getMinPoint());                   // Calculate split dimension as the dimension where the aabb is the widest
        float   splitVal = (box.getMinPoint()[splitDim] + box.getMaxPoint()[splitDim]) / 2; // Split the aabb exactly in two halfes
        auto    splitBoxes = box.split(splitDim, splitVal);
        CBoundingBox& lBox = splitBoxes.first;
        CBoundingBox& rBox = splitBoxes.second;

        // Second order the primitives into new nounding boxes
        std::vector<ptr_prim_t> lPrim;
        std::vector<ptr_prim_t> rPrim;
        for (auto pPrim : vpPrims) {
            if (pPrim->getBoundingBox().overlaps(lBox))
                lPrim.push_back(pPrim);
            if (pPrim->getBoundingBox().overlaps(rBox))
                rPrim.push_back(pPrim);
        }

        // Next build recursively 2 subtrees for both halfes
        auto pLeft = build(lBox, lPrim, depth + 1);
        auto pRight = build(rBox, rPrim, depth + 1);

        return std::make_shared<CBSPNode>(splitDim, splitVal, pLeft, pRight);
    }
}
