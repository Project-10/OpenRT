#include "CompositeGeometry.h"

#include <utility>
#include "Solid.h"
#include "Ray.h"

rt::CBoundingBox rt::CCompositeGeometry::getBoundingBox() const {
    return m_boundingBox;
}

bool rt::CCompositeGeometry::intersect(rt::Ray &ray) const {
    Ray min1 = ray;
    Ray min2 = ray;
    Ray max1 = ray;
    Ray max2 = ray;
    max1.t = -Infty;
    max2.t = -Infty;
    bool hasIntersection = false;
    // TODO: Investigate multi threading this?
    for (const auto& prim : m_s1.getPrims())
    {
        Ray r = ray;
        if (prim->intersect(r))
        {
            if (r.t < min1.t)
                min1 = r;
            if (r.t > max1.t)
                max1 = r;
            hasIntersection = true;
        }
    }
    for (const auto& prim : m_s2.getPrims())
    {
        Ray r = ray;
        if (prim->intersect(r))
        {
            if (r.t < min2.t)
                min2 = r;
            if (r.t > max2.t)
                max2 = r;
            hasIntersection = true;
        }
    }
    if (!hasIntersection)
        return false;
    IntersectionRange res;
    double t = 0;
    switch (m_opType) {
        case Union:
            t = IntersectionRange(min1.t, max1.t).union_op(IntersectionRange(min2.t, max2.t)).getIn();
            if (abs(t - min1.t) < Epsilon)
                ray = min1;
            else if (abs(t - min2.t) < Epsilon)
                ray = min2;
            break;
        case Intersection:
            t = IntersectionRange(min1.t, max1.t).intersection_op(IntersectionRange(min2.t, max2.t)).getIn();
            // This is because the ray might be intersecting only one of the solids.
            if (abs(t) >= Infty)
                return false;
            if (abs(t - min1.t) < Epsilon)
                ray = min1;
            else if (abs(t - min2.t) < Epsilon)
                ray = min2;
            break;
        case Subtraction:
            t = IntersectionRange(min1.t, max1.t).subtract_op(IntersectionRange(min2.t, max2.t)).getIn();
            if (abs(t) >= Infty)
                return false;
            if (t - max1.t < Epsilon)
                ray = max1;
            else if (t - max2.t < Epsilon)
                ray = max2;
            break;
        default:
            break;
    }
    return true;
}

Vec2f rt::CCompositeGeometry::getTextureCoords(const rt::Ray &ray) const {
    return cv::Vec2f();
}

Vec3f rt::CCompositeGeometry::getNormal(const rt::Ray &ray) const {
    return cv::Vec3f();
}

void rt::CCompositeGeometry::transform(const Mat &T) {

}

bool rt::CCompositeGeometry::if_intersect(const rt::Ray &ray) const {
    Ray r = ray;
    return intersect(r);
}

rt::CCompositeGeometry::CCompositeGeometry(rt::ptr_shader_t pShader, const rt::CSolid& s1, const rt::CSolid& s2,
                                           rt::OperationType operationType) : IPrim(pShader){
    m_s1 = s1;
    m_s2 = s2;
    m_opType = operationType;
    CBoundingBox boxA, boxB;
    for (const auto& prim : s1.getPrims())
        boxA.extend(prim->getBoundingBox());
    for (const auto& prim : s2.getPrims())
        boxB.extend(prim->getBoundingBox());
    Vec3f minPt = Vec3f::all(0);
    Vec3f maxPt = Vec3f::all(0);
    switch (m_opType) {
        case Union:
            for (int i = 0; i < 3; i++)
            {
                minPt[i] = MIN(boxA.getMinPoint()[i], boxB.getMinPoint()[i]);
                maxPt[i] = MAX(boxA.getMaxPoint()[i], boxB.getMaxPoint()[i]);
            }
            break;
        case Intersection:
            for (int i = 0; i < 3; i++)
            {
                minPt[i] = MAX(boxA.getMinPoint()[i], boxB.getMinPoint()[i]);
                maxPt[i] = MIN(boxA.getMaxPoint()[i], boxB.getMaxPoint()[i]);
            }
            break;
        case Subtraction:
            for (int i = 0; i < 3; i++)
            {
                minPt[i] = boxA.getMinPoint()[i];
                maxPt[i] = boxA.getMaxPoint()[i];
            }
            break;
        default:
#ifdef DEBUG_PRINT_INFO
            std::cout << "Unknown composite geometry operation\n";
#endif
            break;
    }
    m_boundingBox = CBoundingBox(minPt, maxPt);
}

