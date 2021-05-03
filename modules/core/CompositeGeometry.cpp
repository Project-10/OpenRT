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
    }

    bool CCompositeGeometry::intersect(Ray &ray) const {
        switch (m_operationType) {
            case BoolOp::Union:
                return computeUnion(ray);
            case BoolOp::Intersection:
                return computeIntersection(ray);
            case BoolOp::Difference:
                return computeDifference(ray);
        }
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

    bool CCompositeGeometry::computeUnion(Ray& ray) const {
        Ray minRay, res;
        minRay.org = ray.org;
        minRay.dir = ray.dir;
        minRay.counter = ray.counter;
        res = minRay;
        int iterations = 0;
        while (true) {
            RT_ASSERT(iterations++ <= 100);
            RT_ASSERT(!minRay.hit);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
            for (const auto &prim : m_vPrims1) {
                prim->intersect(minA);
            }
            for (const auto &prim : m_vPrims2) {
                prim->intersect(minB);
            }
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::Miss) {
                return false;
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::In) {
                auto closestRay = minA.t < minB.t ? minA : minB;
                auto t = computeTrueDistance(res, closestRay);
                res = closestRay;
                res.t = t;
                return true;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::Out) {
                auto closestRay = minA.t > minB.t ? minA : minB;
                auto t = computeTrueDistance(res, closestRay);
                res = closestRay;
                res.t = t;
                return true;
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::Miss) {
                auto t = computeTrueDistance(res, minA);
                res = minA;
                res.t = t;
                return true;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::Miss) {
                auto t = computeTrueDistance(res, minA);
                res = minA;
                res.t = t;
                return true;
            }
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::In) {
                auto t = computeTrueDistance(res, minB);
                res = minB;
                res.t = t;
                return true;
            }
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::Out) {
                auto t = computeTrueDistance(res, minB);
                res = minB;
                res.t = t;
                return true;
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::Out) {
                if (minB.t < minA.t) {
                    auto t = computeTrueDistance(res, minB);
                    res = minB;
                    res.t = t;
                    return true;
                }
                minRay.org = minA.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::In) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(res, minA);
                    res = minA;
                    res.t = t;
                    return true;
                }
                minRay.org = minB.hitPoint();
                continue;
            }
        }
        if (res.hit) {
            if (ray.hit && ray.t < res.t) {
                return false;
            }
            ray = res;
            return true;
        }
        return false;
    }

    bool CCompositeGeometry::computeIntersection(Ray &ray) const {
        Ray minRay, res;
        minRay.org = ray.org;
        minRay.dir = ray.dir;
        minRay.counter = ray.counter;
        res = minRay;
        int iterations = 0;
        while (true) {
            RT_ASSERT(iterations++ <= 100);
            RT_ASSERT(!minRay.hit);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
            for (const auto &prim : m_vPrims1) {
                prim->intersect(minA);
            }
            for (const auto &prim : m_vPrims2) {
                prim->intersect(minB);
            }
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::Miss) {
                return false;
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::In) {
                if (minA.t < minB.t) {
                    minRay.org = minA.hitPoint();
                    continue;
                } else {
                    minRay.org = minB.hitPoint();
                    continue;
                }
                break;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::Out) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(res, minA);
                    res = minA;
                    res.t = t;
                    break;
                } else {
                    auto t = computeTrueDistance(res, minB);
                    res = minB;
                    res.t = t;
                    break;
                }
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::Miss) {
                return false;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::Miss) {
                return false;
            }
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::In) {
                return false;
            }
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::Out) {
                return false;
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::Out) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(res, minA);
                    res = minA;
                    res.t = t;
                    break;
                }
                minRay.org = minB.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::In) {
                if (minB.t < minA.t) {
                    auto t = computeTrueDistance(res, minB);
                    res = minB;
                    res.t = t;
                    break;
                }
                minRay.org = minA.hitPoint();
                continue;
            }
        }
        if (res.hit) {
            if (ray.hit && ray.t < res.t) {
                return false;
            }
            ray = res;
            return true;
        }
        return false;
    }

    bool CCompositeGeometry::computeDifference(Ray &ray) const {
        Ray minRay, res;
        minRay.org = ray.org;
        minRay.dir = ray.dir;
        minRay.counter = ray.counter;
        res = minRay;
        int iterations = 0;
        while (true) {
            RT_ASSERT(iterations++ <= 100);
            RT_ASSERT(!minRay.hit);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
            for (const auto &prim : m_vPrims1) {
                prim->intersect(minA);
            }
            for (const auto &prim : m_vPrims2) {
                prim->intersect(minB);
            }
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::Miss) {
                return false;
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::In) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(res, minA);
                    res = minA;
                    res.t = t;
                    break;
                }
                minRay.org = minB.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::Out) {
                if (minB.t < minA.t) {
                    auto t = computeTrueDistance(res, minB);
                    res = minB;
                    res.t = t;
                    break;
                }
                minRay.org = minA.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::Miss) {
                auto t = computeTrueDistance(res, minA);
                res = minA;
                res.t = t;
                break;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::Miss) {
                auto t = computeTrueDistance(res, minA);
                res = minA;
                res.t = t;
                break;
            }
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::In) {
                return false;
            }
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::Out) {
                return false;
            }
            if (stateA == IntersectionState::In && stateB == IntersectionState::Out) {
                if (minA.t < minB.t) {
                    minRay.org = minA.hitPoint();
                } else {
                    minRay.org = minB.hitPoint();
                }
                continue;
            }
            if (stateA == IntersectionState::Out && stateB == IntersectionState::In) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(res, minA);
                    res = minA;
                    res.t = t;
                } else {
                    auto t = computeTrueDistance(res, minB);
                    res = minB;
                    res.t = t;
                }
                break;
            }
        }
        if (res.hit) {
            if (ray.hit && ray.t < res.t) {
                return false;
            }
            ray = res;
            return true;
        }
        return false;
    }

    IntersectionState CCompositeGeometry::classifyRay(const Ray& ray) {
        if (!ray.hit)
            return IntersectionState::Miss;
        if (ray.hit->getNormal(ray).dot(ray.dir) < 0)
            return IntersectionState::In;
        return IntersectionState::Out;
    }

    double CCompositeGeometry::computeTrueDistance(const Ray& ray, const Ray& modifiedRay) {
        return ray.org != modifiedRay.org ? modifiedRay.t + cv::norm(ray.org - modifiedRay.org) : modifiedRay.t;
    }
};
