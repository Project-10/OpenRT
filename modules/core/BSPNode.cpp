#include <macroses.h>
#include "BSPNode.h"
#include "Ray.h"

namespace rt {
    bool CBSPNode::intersect(Ray& ray, double t0, double t1) const
    {
        if (isLeaf()) {
            bool hit = false;
            Ray lastIntersection;
            for (auto& pPrim : m_vpPrims) {
                Ray r = ray;
                if (pPrim->intersect(r)) {
                    if (r.t < lastIntersection.t) {
                        lastIntersection = r;
                    }
                    hit = true;
                }
            }
            if (hit) {
                ray = lastIntersection;
            }
            return hit;
        }
        else {
            // distance from ray origin to the split plane of the current volume (may be negative)
            double d = (m_splitVal - ray.org[m_splitDim]) / ray.dir[m_splitDim];

            auto frontNode = (ray.dir[m_splitDim] < 0) ? Right() : Left();
            auto backNode  = (ray.dir[m_splitDim] < 0) ? Left() : Right();

            if (d <= t0) {
                // t0..t1 is totally behind d, only go to back side
                return backNode->intersect(ray, t0, t1);
            }
            else if (d >= t1) {
                // t0..t1 is totally in front of d, only go to front side
                return frontNode->intersect(ray, t0, t1);
            }
            else {
                // travese both children. front one first, back one last
                if (frontNode->intersect(ray, t0, d))
                    return true;

                return backNode->intersect(ray, d, t1);
            }
        }
    }
}
