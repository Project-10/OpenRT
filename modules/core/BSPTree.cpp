#include "BSPTree.h"
#include "IPrim.h"
#include "ray.h"
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
    
        /**
         * @brief Clips the ray with the bounding box
         * @details If ray \b ray does not intersect the bounding box, resulting t1 will be smaller than t0
         * @param[in] ray The ray
         * @param[in] box The bounding box
         * @param[in,out] t0 The distance from ray origin at which the ray enters the bounding box
         * @param[in,out] t1 The distance from ray origin at which the ray leaves the bounding box
         */
        void clip(const Ray& ray, const CBoundingBox& box, double& t0, double& t1)
        {
            float d, den;
            den = 1.0f / ray.dir.val[0];
            if (ray.dir.val[0] > 0) {
                if ((d = (box.getMinPoint().val[0] - ray.org.val[0]) * den) > t0) t0 = d;
                if ((d = (box.getMaxPoint().val[0] - ray.org.val[0]) * den) < t1) t1 = d;
            }
            else {
                if ((d = (box.getMaxPoint().val[0] - ray.org.val[0]) * den) > t0) t0 = d;
                if ((d = (box.getMinPoint().val[0] - ray.org.val[0]) * den) < t1) t1 = d;
            }
            if (t0 > t1) return;

            den = 1.0f / ray.dir.val[1];
            if (ray.dir.val[1] > 0) {
                if ((d = (box.getMinPoint().val[1] - ray.org.val[1]) * den) > t0) t0 = d;
                if ((d = (box.getMaxPoint().val[1] - ray.org.val[1]) * den) < t1) t1 = d;
            }
            else {
                if ((d = (box.getMaxPoint().val[1] - ray.org.val[1]) * den) > t0) t0 = d;
                if ((d = (box.getMinPoint().val[1] - ray.org.val[1]) * den) < t1) t1 = d;
            }
            if (t0 > t1) return;

            den = 1.0f / ray.dir.val[2];
            if (ray.dir.val[2] > 0) {
                if ((d = (box.getMinPoint().val[2] - ray.org.val[2]) * den) > t0) t0 = d;
                if ((d = (box.getMaxPoint().val[2] - ray.org.val[2]) * den) < t1) t1 = d;
            }
            else {
                if ((d = (box.getMaxPoint().val[2] - ray.org.val[2]) * den) > t0) t0 = d;
                if ((d = (box.getMinPoint().val[2] - ray.org.val[2]) * den) < t1) t1 = d;
            }
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
        clip(ray, m_treeBoundingBox, t0, t1);
        if (t1 < t0) return false;  // no intersection with the bounding box
        return m_root->intersect(ray, t0, t1);
    }

    ptr_bspnode_t CBSPTree::build(const CBoundingBox& box, const std::vector<ptr_prim_t>& vpPrims, size_t depth)
    {
        // Check for stoppong criteria
        if (depth > m_maxDepth || vpPrims.size() <= m_minPrimitives)
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
