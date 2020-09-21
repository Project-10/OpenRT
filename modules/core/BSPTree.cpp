#include "BSPTree.h"
#include "BoundingBox.h"
#include "macroses.h"

namespace rt {
    namespace {
        // Calculates and return the bounding box, containing the whole scene
        CBoundingBox calcBounds(const std::vector<ptr_prim_t>& vpPrims)
        {
            CBoundingBox res;
            for (auto pPrim : vpPrims)
                res.extend(pPrim->calcBounds());
            return res;
        }

        // Returns the best dimension index for next split
        inline int MaxDim(Vec3f v)
        {
            return (v.val[0] > v.val[1]) ? ((v.val[0] > v.val[2]) ? 0 : 2) : ((v.val[1] > v.val[2]) ? 1 : 2);
        }
    }

    // Constructor
    CBSPTree::CBSPTree(const std::vector<ptr_prim_t>& vpPrims)
    {
        m_boundingBox = calcBounds(vpPrims);
#ifdef DEBUG_PRINT_INFO
        std::cout << "Scene bounds are : " << m_boundingBox.m_min << " " << m_boundingBox.m_max << std::endl;
#endif
        m_root = build(m_boundingBox, vpPrims, 0);
    }

    ptr_bspnode_t CBSPTree::build(const CBoundingBox& box, const std::vector<ptr_prim_t>& vpPrims, size_t depth)
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

        auto pLeft  = build(lBounds, lPrim, depth + 1);
        auto pRight = build(rBounds, rPrim, depth + 1);

        return std::make_shared<CBSPNode>(splitVal, splitDim, pLeft, pRight);
    }

    bool CBSPTree::intersect(Ray& ray) const
    {
        RT_ASSERT(!ray.hit);
        
        double t0 = 0;
        double t1 = ray.t;

        m_boundingBox.clip(ray, t0, t1);

        if (t1 - t0 < Epsilon)
            return false;

        m_root->traverse(ray, t0, t1);

        if (ray.hit)
            return true;

        return false;
    }

}
