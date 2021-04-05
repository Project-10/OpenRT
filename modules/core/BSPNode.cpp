#include "BSPNode.h"
#include "Ray.h"

namespace rt {
    bool CBSPNode::intersect(Ray& ray, double t0, double t1) const
    {
        if (isLeaf()) {
            for (auto& pPrim : m_vpPrims)
                pPrim->intersect(ray);
            return (ray.hit && ray.t < t1 + Epsilon);
        }
        else {
            // distnace from ray origin to the split plane of the current volume (may be negative)
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

    bool CBSPNode::intersect_furthest(Ray &ray, double t0, double t1) const {
        if (isLeaf()) {
            // main difference between the two functions resides here.
            // instead of looking for the closest intersection
            // we look for the furthest intersection in the leaf node.
            bool hasIntersection = false;
            auto mainCopy = ray;
            Ray range = ray;
            range.t = -Infty;
            for (const auto &prim : m_vpPrims) {
                Ray r = mainCopy;
                if (prim->intersect(r)) {
                    if (r.t > range.t) {
                        range = r;
                    }
                    hasIntersection = true;
                }
            }
            if (range.t > -Infty) {
                ray = range;
            }
            return (hasIntersection && ray.t < t1 + Epsilon);
        }
        else {
            // distance from ray origin to the split plane of the current volume (may be negative)
            double d = (m_splitVal - ray.org[m_splitDim]) / ray.dir[m_splitDim];

            auto frontNode = (ray.dir[m_splitDim] < 0) ? Right() : Left();
            auto backNode  = (ray.dir[m_splitDim] < 0) ? Left() : Right();

            if (d <= t0) {
                // t0..t1 is totally behind d, only go to back side
                return backNode->intersect_furthest(ray, t0, t1);
            }
            else if (d >= t1) {
                // t0..t1 is totally in front of d, only go to front side
                return frontNode->intersect_furthest(ray, t0, t1);
            }
            else {
                // travese both children. back one first since we're looking for the furthest intersection, front one last
                if (backNode->intersect_furthest(ray, d, t1))
                    return true;

                return frontNode->intersect_furthest(ray, t0, d);
            }
        }
    }
}
