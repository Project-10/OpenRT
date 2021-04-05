#include "CompositeGeometry.h"

#include <utility>
#include <macroses.h>
#include "Ray.h"
#include "Transform.h"

namespace rt {

    // Constructor
    CCompositeGeometry::CCompositeGeometry(const CSolid &s1, const CSolid &s2, BoolOp operationType, int maxDepth,
                                           int maxPrimitives)
            : IPrim(nullptr), m_vPrims1(s1.getPrims()), m_vPrims2(s2.getPrims()), m_operationType(operationType)
#ifdef ENABLE_BSP
    , m_pBSPTree1(new CBSPTree()), m_pBSPTree2(new CBSPTree())
#endif
    {
        // Initializing the bounding box
        CBoundingBox boxA, boxB;
        for (const auto &prim : s1.getPrims())
            boxA.extend(prim->getBoundingBox());
        for (const auto &prim : s2.getPrims())
            boxB.extend(prim->getBoundingBox());
        Vec3f minPt = Vec3f::all(0);
        Vec3f maxPt = Vec3f::all(0);
        switch (m_operationType) {
            case BoolOp::Union:
                for (int i = 0; i < 3; i++) {
                    minPt[i] = MIN(boxA.getMinPoint()[i], boxB.getMinPoint()[i]);
                    maxPt[i] = MAX(boxA.getMaxPoint()[i], boxB.getMaxPoint()[i]);
                }
                break;
            case BoolOp::Intersection:
                for (int i = 0; i < 3; i++) {
                    minPt[i] = MAX(boxA.getMinPoint()[i], boxB.getMinPoint()[i]);
                    maxPt[i] = MIN(boxA.getMaxPoint()[i], boxB.getMaxPoint()[i]);
                }
                break;
            case BoolOp::Difference:
                for (int i = 0; i < 3; i++) {
                    minPt[i] = boxA.getMinPoint()[i];
                    maxPt[i] = boxA.getMaxPoint()[i];
                }
                break;
            default:
                break;
        }
        m_boundingBox = CBoundingBox(minPt, maxPt);
        m_origin = m_boundingBox.getCenter();
#ifdef ENABLE_BSP
        m_pBSPTree1->build(m_vPrims1, maxPrimitives, maxDepth);
        m_pBSPTree2->build(m_vPrims2, maxPrimitives, maxDepth);
#endif
    }

    bool CCompositeGeometry::intersect(Ray &ray) const {
        std::pair<Ray, Ray> range1(ray, ray);
        std::pair<Ray, Ray> range2(ray, ray);
        range1.second.t = -Infty;
        range2.second.t = -Infty;
        bool hasIntersection = false;
#ifdef ENABLE_BSP
        hasIntersection = m_pBSPTree1->intersect(range1.first);
        hasIntersection |= m_pBSPTree2->intersect(range2.first);
        if (m_operationType == BoolOp::Difference) {
            Ray r1 = ray;
            Ray r2 = ray;
            if (m_pBSPTree1->intersect_furthest(r1)) {
                range1.second = r1;
                hasIntersection = true;
            }
            if (m_pBSPTree2->intersect_furthest(r2)) {
                range2.second = r2;
                hasIntersection = true;
            }
        }
#else
        for (const auto &prim : m_vPrims1) {
            Ray r = ray;
            if (prim->intersect(r)) {
                if (r.t < range1.first.t)
                    range1.first = r;
                if (r.t > range1.second.t)
                    range1.second = r;
                hasIntersection = true;
            }
        }
        for (const auto &prim : m_vPrims2) {
            Ray r = ray;
            if (prim->intersect(r)) {
                if (r.t < range2.first.t)
                    range2.first = r;
                if (r.t > range2.second.t)
                    range2.second = r;
                hasIntersection = true;
            }
        }
#endif
        if (!hasIntersection)
            return false;
        double t;
        switch (m_operationType) {
            case BoolOp::Union:
                t = MIN(range1.first.t, range2.first.t);
                if (abs(t - range1.first.t) < Epsilon)
                    ray = range1.first;
                else if (abs(t - range2.first.t) < Epsilon)
                    ray = range2.first;
                break;
            case BoolOp::Intersection:
                t = MAX(range1.first.t, range2.first.t);
                if (abs(t) >= Infty)
                    return false;
                if (abs(t - range1.first.t) < Epsilon)
                    ray = range1.first;
                else if (abs(t - range2.first.t) < Epsilon)
                    ray = range2.first;
                break;
            case BoolOp::Difference:
                if (range1.first.t >= Infty || range1.second.t <= -Infty) {
                    return false;
                }
                if (abs(range2.first.t - range1.first.t) < Epsilon) {
                    ray = range2.second;
                    break;
                }
                if (range2.first.t < range1.first.t) {
                    if (range1.first.t > range2.second.t) {
                        ray = range1.first;
                    } else {
                        ray = range2.second;
                    }
                } else if (range1.first.t < range2.first.t) {
                    ray = range1.first;
                } else {
                    return false;
                }
                break;
            default:
                break;
        }
        return true;
    }

    bool CCompositeGeometry::if_intersect(const Ray &ray) const {
        return intersect(lvalue_cast(Ray(ray)));
    }

    void CCompositeGeometry::transform(const Mat &T) {
        CTransform tr;
        Mat T1 = tr.translate(-m_origin).get();
        Mat T2 = tr.translate(m_origin).get();

        // transform first geometry
        for (auto &pPrim : m_vPrims1) pPrim->transform(T * T1);
        for (auto &pPrim : m_vPrims1) pPrim->transform(T2);

        // transform second geometry
        for (auto &pPrim : m_vPrims2) pPrim->transform(T * T1);
        for (auto &pPrim : m_vPrims2) pPrim->transform(T2);

        // update pivots point
        for (int i = 0; i < 3; i++)
            m_origin.val[i] += T.at<float>(i, 3);
    }

    Vec3f CCompositeGeometry::getNormal(const Ray &ray) const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }

    Vec2f CCompositeGeometry::getTextureCoords(const Ray &ray) const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }
}
