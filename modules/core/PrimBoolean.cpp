#include "PrimBoolean.h"
#include "Transform.h"
#include "Ray.h"
#include "macroses.h"

namespace rt {
	enum class IntersectionState { Enter, Exit, Miss };

	CPrimBoolean::CPrimBoolean(const CSolid &A, const CSolid &B, BoolOp operation, int maxDepth, int maxPrimitives)
		: CPrim(nullptr)
		, m_vpPrims1(A.getPrims())
		, m_vpPrims2(B.getPrims())
		, m_operation(operation)
#ifdef ENABLE_BSP
		, m_maxDepth(maxDepth)
		, m_maxPrimitives(maxPrimitives)
		, m_pBSPTree1(new CBSPTree())
		, m_pBSPTree2(new CBSPTree())
#endif
    {
        if (operation == BoolOp::Substraction)
			for (auto& pPrim : m_vpPrims2) pPrim->flipNormal();
		computeBoundingBox();
        m_origin = m_boundingBox.getCenter();
#ifdef ENABLE_BSP
        m_pBSPTree1->build(m_vpPrims1, m_maxDepth, m_maxPrimitives);
        m_pBSPTree2->build(m_vpPrims2, m_maxDepth, m_maxPrimitives);
#endif
    }

    bool CPrimBoolean::intersect(Ray &ray) const 
	{
		std::optional<Ray> res;
		switch (m_operation) {
			case BoolOp::Union: 		res = computeUnion(ray); 		break;
			case BoolOp::Intersection: 	res = computeIntersection(ray); break;
			case BoolOp::Substraction:	res = computeSubstraction(ray);	break;
			default: RT_ASSERT_MSG(false, "Unknown boolean operation");
        }
		if (!res) return false;
		
		RT_ASSERT(res.value().hit);

		double t = norm(ray.org - res.value().hitPoint());
		if (t > ray.t) return false;

		ray.t = t;
		ray.hit = res.value().hit;
		ray.u = res.value().u;
		ray.v = res.value().v;
		
		return true;
    }

    // TODO: This can be greatly improved. To be optimized further.
    bool CPrimBoolean::if_intersect(const Ray &ray) const 
	{
        return intersect(lvalue_cast(Ray(ray)));
    }

    void CPrimBoolean::transform(const Mat &T) 
	{
        CTransform tr;
        Mat T1 = tr.translate(-m_origin).get();
        Mat T2 = tr.translate(m_origin).get();

        // transform first geometry
        for (auto &pPrim : m_vpPrims1) pPrim->transform(T * T1);
        for (auto &pPrim : m_vpPrims1) pPrim->transform(T2);

        // transform second geometry
        for (auto &pPrim : m_vpPrims2) pPrim->transform(T * T1);
        for (auto &pPrim : m_vpPrims2) pPrim->transform(T2);

        // update pivots point
        for (int i = 0; i < 3; i++)
            m_origin.val[i] += T.at<float>(i, 3);

        // recompute the bounding box
        computeBoundingBox();
#ifdef ENABLE_BSP
		m_pBSPTree1->build(m_vpPrims1, m_maxDepth, m_maxPrimitives);
		m_pBSPTree2->build(m_vpPrims2, m_maxDepth, m_maxPrimitives);
#endif
    }

    Vec3f CPrimBoolean::doGetNormal(const Ray &ray) const 
	{
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }

    Vec2f CPrimBoolean::getTextureCoords(const Ray &ray) const 
	{
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }

	void CPrimBoolean::flipNormal(void) {
		for (auto &pPrim : m_vpPrims1) pPrim->flipNormal();
		for (auto &pPrim : m_vpPrims2) pPrim->flipNormal();
		m_flippedNormal = !m_flippedNormal;
	}

	IntersectionState CPrimBoolean::classifyRay(const Ray& ray) const
	{
		if (!ray.hit) return IntersectionState::Miss;
		
		Vec3f realNormal = m_flippedNormal ? -ray.hit->getNormal(ray) : ray.hit->getNormal(ray);

		if (realNormal.dot(ray.dir) < 0)	return IntersectionState::Enter;
		else								return IntersectionState::Exit;
	}

	std::optional<Ray> CPrimBoolean::computeUnion(const Ray &ray) const 
	{
		Ray minRay(ray.org, ray.dir);
        for (int iteration = 0; iteration < 100; iteration++) {
            RT_ASSERT(!minRay.hit);
            Ray minA = minRay;
            Ray minB = minRay;
#ifdef ENABLE_BSP
            m_pBSPTree1->intersect(minA);
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &pPrim : m_vpPrims1) pPrim->intersect(minA);
            for (const auto &pPrim : m_vpPrims2) pPrim->intersect(minB);
#endif
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            
			if (stateA == IntersectionState::Miss && stateB == IntersectionState::Miss) return std::nullopt;
            if (stateA == IntersectionState::Miss || stateB == IntersectionState::Miss) return stateA == IntersectionState::Miss ? minB : minA;
            if (stateA == stateB) {
                if (stateA == IntersectionState::Enter)	return minA.t < minB.t ? minA : minB;
				else									return minA.t > minB.t ? minA : minB;
            }
            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
                if (minB.t < minA.t) return minB;
                minRay.org = minA.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) return minA;
                minRay.org = minB.hitPoint();
                continue;
            }
        } // iteration
		RT_WARNING("The maximum depth of calculations is reached.");
		return std::nullopt;
    }

	std::optional<Ray> CPrimBoolean::computeIntersection(const Ray &ray) const 
	{
		Ray minRay(ray.org, ray.dir);
		for (int iteration = 0; iteration < 100; iteration++) {
            RT_ASSERT(!minRay.hit);
            Ray minA = minRay;
            Ray minB = minRay;
#ifdef ENABLE_BSP
            m_pBSPTree1->intersect(minA);
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &pPrim : m_vpPrims1) pPrim->intersect(minA);
            for (const auto &pPrim : m_vpPrims2) pPrim->intersect(minB);
#endif
            auto stateA = classifyRay(minA);
            auto stateB = classifyRay(minB);
            if (stateA == IntersectionState::Miss || stateB == IntersectionState::Miss) return std::nullopt;
            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Enter) {
                minRay.org = minA.t < minB.t ? minA.hitPoint() : minB.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Exit) return minA.t < minB.t ? minA : minB;

            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
                if (minA.t < minB.t) return minA;
                minRay.org = minB.hitPoint();
                continue;
            }
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) {
                if (minB.t < minA.t) return minB;
                minRay.org = minA.hitPoint();
                continue;
            }
        } // iteration
		RT_WARNING("The maximum depth of calculations is reached.");
		return std::nullopt;
    }

	std::optional<Ray> CPrimBoolean::computeSubstraction(const Ray &ray) const 
	{
		Ray minRay(ray.org, ray.dir);
		for (int iteration = 0; iteration < 100; iteration++) {
            RT_ASSERT(!minRay.hit);
			// --------- RAY A ---------
			Ray minA = minRay;
#ifdef ENABLE_BSP
			m_pBSPTree1->intersect(minA);
#else
			for (const auto &pPrim : m_vpPrims1) pPrim->intersect(minA);
#endif
			auto stateA = classifyRay(minA);

			// Miss A
			if (stateA == IntersectionState::Miss) return std::nullopt;
			
			// --------- RAY B ---------
			Ray minB = minRay;
#ifdef ENABLE_BSP
            m_pBSPTree2->intersect(minB);
#else
            for (const auto &pPrim : m_vpPrims2) pPrim->intersect(minB);
#endif
            auto stateB = classifyRay(minB);
			// Since the normal of object B is inverted in constructor			
			stateB = stateB == IntersectionState::Enter ? IntersectionState::Exit : IntersectionState::Enter;
		
			// hit A, but miss B
            if (stateB == IntersectionState::Miss) return minA;

			// ray enters A and B
            if (stateA == IntersectionState::Enter && stateB == IntersectionState::Enter) {
                if (minA.t < minB.t) return minA;
                minRay.org = minB.hitPoint();
                continue;
            }
			
			// ray enters A and exits B
			if (stateA == IntersectionState::Enter && stateB == IntersectionState::Exit) {
				minRay.org = minA.t < minB.t ? minA.hitPoint() : minB.hitPoint();
				continue;
			}
			
			// ray leaves A and B
            if (stateA == IntersectionState::Exit && stateB == IntersectionState::Exit) {
                if (minB.t < minA.t) return minB;
                minRay.org = minA.hitPoint();
                continue;
            }
			
			// ray leaves A but enters B
			if (stateA == IntersectionState::Exit && stateB == IntersectionState::Enter) 
                return minA.t < minB.t ? minA : minB;
        } // iteration
		RT_WARNING("The maximum depth of calculations is reached.");
		return std::nullopt;
    }

    void CPrimBoolean::computeBoundingBox() 
	{
        CBoundingBox boxA, boxB;
        for (const auto &prim : m_vpPrims1)
            boxA.extend(prim->getBoundingBox());
        for (const auto &prim : m_vpPrims2)
            boxB.extend(prim->getBoundingBox());

        Vec3f minPt = Vec3f::all(0);
        Vec3f maxPt = Vec3f::all(0);
        switch (m_operation) {
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
            case BoolOp::Substraction:
                for (int i = 0; i < 3; i++) {
                    minPt[i] = boxA.getMinPoint()[i];
                    maxPt[i] = boxA.getMaxPoint()[i];
                }
                break;
            default: RT_ASSERT_MSG(false, "Unknown boolean operation");
        }
        m_boundingBox = CBoundingBox(minPt, maxPt);
    }
}
