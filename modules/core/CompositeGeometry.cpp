#include "CompositeGeometry.h"

#include <utility>
#include <macroses.h>
#include "Ray.h"
#include "Transform.h"
#include "PrimDummy.h"

namespace rt {

    CCompositeGeometry::CCompositeGeometry(const CSolid &s1, const CSolid &s2, BoolOp operationType, int maxDepth, int maxPrimitives)
		: IPrim(nullptr)
		, m_vPrims1(s1.getPrims())
		, m_vPrims2(s2.getPrims())
		, m_operationType(operationType)
#ifdef ENABLE_BSP
		, m_maxDepth(maxDepth)
		, m_maxPrimitives(maxPrimitives)
		, m_pBSPTree1(new CBSPTree())
		, m_pBSPTree2(new CBSPTree())
#endif
    {
        computeBoundingBox();
        m_origin = m_boundingBox.getCenter();
#ifdef ENABLE_BSP
        m_pBSPTree1->build(m_vPrims1, m_maxDepth, m_maxPrimitives);
        m_pBSPTree2->build(m_vPrims2, m_maxDepth, m_maxPrimitives);
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
			default:
				RT_ASSERT_MSG(false, "Unknown boolean operation");
				return false;
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

        // recompute the bounding box
        computeBoundingBox();
#ifdef ENABLE_BSP
		m_pBSPTree1->build(m_vPrims1, m_maxDepth, m_maxPrimitives);
		m_pBSPTree2->build(m_vPrims2, m_maxDepth, m_maxPrimitives);
#endif
    }

    Vec3f CCompositeGeometry::getNormal(const Ray &ray) const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }

    Vec2f CCompositeGeometry::getTextureCoords(const Ray &ray) const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }

    bool CCompositeGeometry::computeUnion(Ray &ray) const {
        Ray minRay, res;
        minRay = ray;
        minRay.hit = nullptr;
        minRay.t = Infty;
        int iterations = 0;
        while (true) {
            RT_ASSERT(iterations++ <= MAX_INTERSECTIONS);
            RT_ASSERT(!minRay.hit);
            RT_ASSERT(minRay.t >= Infty);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
#ifdef ENABLE_BSP
            m_pBSPTree1->intersect(minA);
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &prim : m_vPrims1) 
                prim->intersect(minA);
            for (const auto &prim : m_vPrims2) 
                prim->intersect(minB);
#endif
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss && stateB == IntersectionState::Miss) {
                return false;
            }
            if (stateA == IntersectionState::Miss || stateB == IntersectionState::Miss) {
                Ray closestRay = stateA == IntersectionState::Miss ? minB : minA;
                auto t = computeTrueDistance(ray, closestRay);
                res = closestRay;
                res.t = t;
                break;
            }
            if (stateA == stateB) {
                Ray chosenRay;
                if (stateA == IntersectionState::Enter) {
                    chosenRay = minA.t < minB.t ? minA : minB;
                } else {
                    chosenRay = minA.t > minB.t ? minA : minB;
                }
                auto t = computeTrueDistance(ray, chosenRay);
                res = chosenRay;
                res.t = t;
                break;
            }
            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
                if (minB.t < minA.t) {
                    auto t = computeTrueDistance(ray, minB);
                    res = minB;
                    res.t = t;
                    break;
                }
                minRay.org = minA.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(ray, minA);
                    res = minA;
                    res.t = t;
                    break;
                }
                minRay.org = minB.hitPoint();
                continue;
            }
        }
        if (res.hit) {
            if (ray.t < res.t) {
                return false;
            }
            auto initialOrigin = ray.org;
            ray = res;
            ray.org = initialOrigin;
            return true;
        }
        return false;
    }

    bool CCompositeGeometry::computeIntersection(Ray &ray) const {
        Ray minRay, res;
        minRay = ray;
        minRay.hit = nullptr;
        minRay.t = Infty;
        int iterations = 0;
        while (true) {
            RT_ASSERT(iterations++ <= MAX_INTERSECTIONS);
            RT_ASSERT(!minRay.hit);
            RT_ASSERT(minRay.t >= Infty);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
#ifdef ENABLE_BSP
            m_pBSPTree1->intersect(minA);
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &prim : m_vPrims1) 
                prim->intersect(minA);
            for (const auto &prim : m_vPrims2)
                prim->intersect(minB);
#endif
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss || stateB == IntersectionState::Miss) {
                return false;
            }
            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Enter) {
                minRay.org = minA.t < minB.t ? minA.hitPoint() : minB.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Exit) {
                auto closestRay = minA.t < minB.t ? minA : minB;
                auto t = computeTrueDistance(ray, closestRay);
                res = closestRay;
                res.t = t;
                break;
            }
            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(ray, minA);
                    res = minA;
                    res.t = t;
                    break;
                }
                minRay.org = minB.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) {
                if (minB.t < minA.t) {
                    auto t = computeTrueDistance(ray, minB);
                    res = minB;
                    res.t = t;
                    break;
                }
                minRay.org = minA.hitPoint();
                continue;
            }
        }
        if (res.hit) {
            if (ray.t < res.t) {
                return false;
            }
            auto initialOrigin = ray.org;
            ray = res;
            ray.org = initialOrigin;
            return true;
        }
        return false;
    }

    bool CCompositeGeometry::computeDifference(Ray &ray) const {
        Ray minRay, res;
        minRay = ray;
        minRay.hit = nullptr;
        minRay.t = Infty;
        int iterations = 0;
        while (true) {
            RT_ASSERT(iterations++ <= MAX_INTERSECTIONS);
            RT_ASSERT(!minRay.hit);
            RT_ASSERT(minRay.t >= Infty);
            Ray minA, minB;
            minA = minRay;
            minB = minRay;
#ifdef ENABLE_BSP
            m_pBSPTree1->intersect(minA);
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &prim : m_vPrims1)
                prim->intersect(minA);
            for (const auto &prim : m_vPrims2)
                prim->intersect(minB);
#endif
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss) {
                return false;
            }
            if (stateB == IntersectionState::Miss) {
                auto t = computeTrueDistance(ray, minA);
                res = minA;
                res.t = t;
                break;
            }
            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(ray, minA);
                    res = minA;
                    res.t = t;
                    break;
                }
                minRay.org = minB.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Exit) {
                if (minB.t < minA.t) {
                    auto t = computeTrueDistance(ray, minB);
                    res = minB;
                    res.t = t;
                    auto dummyPrim = std::make_shared<CPrimDummy>(res.hit->getShader(), -res.hit->getNormal(res),
                                                                  res.hit->getTextureCoords(res));
                    res.hit = dummyPrim;
                    break;
                }
                minRay.org = minA.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
                minRay.org = minA.t < minB.t ? minA.hitPoint() : minB.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) {
                    auto t = computeTrueDistance(ray, minA);
                    res = minA;
                    res.t = t;
                    auto currentNormal = res.hit->getNormal(res);
                    auto dummyPrim = std::make_shared<CPrimDummy>(res.hit->getShader(), -currentNormal,
                                                                  res.hit->getTextureCoords(res));
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
            auto initialOrigin = ray.org;
            ray = res;
            ray.org = initialOrigin;
            return true;
        }
        return false;
    }

    IntersectionState CCompositeGeometry::classifyRay(const Ray &ray) {
        if (!ray.hit)
            return IntersectionState::Miss;
        if (ray.hit->getNormal(ray).dot(ray.dir) < 0)
            return IntersectionState::Enter;
        return IntersectionState::Exit;
    }

    double CCompositeGeometry::computeTrueDistance(const Ray &ray, const Ray &modifiedRay) 
	{
        return ray.org != modifiedRay.org ? modifiedRay.t + cv::norm(ray.org - modifiedRay.org) : modifiedRay.t;
    }

    void CCompositeGeometry::computeBoundingBox() {
        CBoundingBox boxA, boxB;
        for (const auto &prim : m_vPrims1)
            boxA.extend(prim->getBoundingBox());
        for (const auto &prim : m_vPrims2)
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
    }
};
