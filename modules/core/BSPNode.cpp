#include "BSPNode.h"

namespace rt {
    bool CBSPNode::traverse(Ray& ray, double& t0, double& t1)
    {
        if (isLeaf()) {
            for (auto pPrim : m_vpPrims)
                pPrim->intersect(ray);
            return (ray.hit != NULL && ray.t < t1);
        }
        else {
            double d = (m_splitVal - ray.org[m_splitDim]) / ray.dir[m_splitDim];

            auto frontNode = (ray.dir[m_splitDim] < 0) ? Right() : Left();
            auto backNode  = (ray.dir[m_splitDim] < 0) ? Left() : Right();

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
}
