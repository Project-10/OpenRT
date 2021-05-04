#include "CompositeGeometry.h"

#include <utility>
#include <macroses.h>
#include "Ray.h"
#include "Transform.h"
#include "PrimDummy.h"

namespace rt {

    CCompositeGeometry::CCompositeGeometry(const CSolid &s1, const CSolid &s2, BoolOp operationType, int maxDepth,
                                           int maxPrimitives)
            : IPrim(nullptr), m_vPrims1(s1.getPrims()), m_vPrims2(s2.getPrims()), m_operationType(operationType)
#ifdef CSG_OPTIM
    , m_pBSPTree1(new CBSPTree()), m_pBSPTree2(new CBSPTree())
#endif
    {
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
#ifdef CSG_OPTIM
        m_pBSPTree1->build(m_vPrims1, maxDepth, maxPrimitives);
        m_pBSPTree2->build(m_vPrims2, maxDepth, maxPrimitives);
#endif
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
            RT_ASSERT(iterations++ <= MAX_INTERSECTIONS);
            RT_ASSERT(!minRay.hit);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
#ifdef CSG_OPTIM
            m_pBSPTree1->intersect(minA);
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &prim : m_vPrims1) {
                prim->intersect(minA);
            }
            for (const auto &prim : m_vPrims2) {
                prim->intersect(minB);
            }
#endif
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::Miss) {
                return false;
            } else if (stateA == IntersectionState::Miss) {
                auto t = computeTrueDistance(res, minB);
                res = minB;
                res.t = t;
                break;
            } else if (stateB == IntersectionState::Miss) {
                auto t = computeTrueDistance(res, minA);
                res = minA;
                res.t = t;
                break;
            } else if (stateA == stateB) {
                auto closestRay = minA.t < minB.t ? minA : minB;
                auto t = computeTrueDistance(res, closestRay);
                res = closestRay;
                res.t = t;
                break;
            } else if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
                if (minB.t < minA.t) {
                    auto t = computeTrueDistance(res, minB);
                    res = minB;
                    res.t = t;
                    break;
                }
                minRay.org = minA.hitPoint();
                continue;
            } else if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(res, minA);
                    res = minA;
                    res.t = t;
                    break;
                }
                minRay.org = minB.hitPoint();
                continue;
            }
        }
        if (res.hit) {
            if (ray.hit && ray.t < res.t) {
                return false;
            }
            auto currentNormal = res.hit->getNormal(res);
            auto dummyPrim = std::make_shared<CPrimDummy>(res.hit->getShader(), currentNormal.dot(res.dir) >= 0 ? -currentNormal : currentNormal, res.hit->getTextureCoords(res));
            ray = res;
            ray.hit = dummyPrim;
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
            RT_ASSERT(iterations++ <= MAX_INTERSECTIONS);
            RT_ASSERT(!minRay.hit);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
#ifdef CSG_OPTIM
            m_pBSPTree1->intersect(minA);
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &prim : m_vPrims1) {
                prim->intersect(minA);
            }
            for (const auto &prim : m_vPrims2) {
                prim->intersect(minB);
            }
#endif
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss || stateB == IntersectionState::Miss) {
                return false;
            } else if (stateA == IntersectionState::Enter && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) {
                    minRay.org = minA.hitPoint();
                    continue;
                } else {
                    minRay.org = minB.hitPoint();
                    continue;
                }
            } else if (stateA == IntersectionState::Exit && stateB == IntersectionState::Exit) {
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
            } else if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(res, minA);
                    res = minA;
                    res.t = t;
                    break;
                }
                minRay.org = minB.hitPoint();
                continue;
            } else if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) {
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
        int iterations = 0;
        while (true) {
            RT_ASSERT(iterations++ <= MAX_INTERSECTIONS);
            RT_ASSERT(!minRay.hit);
            RT_ASSERT(minRay.t >= Infty);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
#ifdef CSG_OPTIM
            m_pBSPTree1->intersect(minA);
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &prim : m_vPrims1) {
                prim->intersect(minA);
            }
            for (const auto &prim : m_vPrims2) {
                prim->intersect(minB);
            }
#endif
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss) {
                return false;
            } else if (stateB == IntersectionState::Miss) {
                auto t = computeTrueDistance(ray, minA);
                res = minA;
                res.t = t;
                break;
            } else if (stateA == IntersectionState::Enter && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(ray, minA);
                    res = minA;
                    res.t = t;
                    break;
                }
                minRay.org = minB.hitPoint();
                continue;
            } else if (stateA == IntersectionState::Exit && stateB == IntersectionState::Exit) {
                if (minB.t < minA.t) {
                    auto t = computeTrueDistance(ray, minB);
                    res = minB;
                    res.t = t;
                    auto dummyPrim = std::make_shared<CPrimDummy>(res.hit->getShader(), -res.hit->getNormal(res), res.hit->getTextureCoords(res));
                    res.hit = dummyPrim;
                    break;
                }
                minRay.org = minA.hitPoint();
                continue;
            } else if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
                if (minA.t < minB.t) {
                    minRay.org = minA.hitPoint();
                } else {
                    minRay.org = minB.hitPoint();
                }
                continue;
            } else if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(ray, minA);
                    res = minA;
                    res.t = t;
                    auto currentNormal = res.hit->getNormal(res);
                    auto dummyPrim = std::make_shared<CPrimDummy>(res.hit->getShader(), -currentNormal, res.hit->getTextureCoords(res));
                    res.hit = dummyPrim;
                } else {
                    auto t = computeTrueDistance(ray, minB);
                    res = minB;
                    res.t = t;
                }
                break;
            }
        }
        if (res.hit) {
            if (ray.t < res.t) {
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
            return IntersectionState::Enter;
        return IntersectionState::Exit;
    }

    double CCompositeGeometry::computeTrueDistance(const Ray& ray, const Ray& modifiedRay) {
        return ray.org != modifiedRay.org ? modifiedRay.t + cv::norm(ray.org - modifiedRay.org) : modifiedRay.t;
    }
};
