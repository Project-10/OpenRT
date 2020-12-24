#include "CompositeGeometry.h"

#include <utility>
#include <macroses.h>
#include "Solid.h"
#include "Ray.h"

rt::CBoundingBox rt::CCompositeGeometry::getBoundingBox() const {
    return m_boundingBox;
}

bool rt::CCompositeGeometry::intersect(rt::Ray &ray) const {
    std::pair<Ray, Ray> range1(ray, ray);
    std::pair<Ray, Ray> range2(ray, ray);
    range1.second.t = -Infty;
    range2.second.t = -Infty;
    bool hasIntersection = false;
    for (const auto& prim : m_s1.getPrims())
    {
        Ray r = ray;
        if (prim->intersect(r))
        {
            if (r.t < range1.first.t)
                range1.first = r;
            if (r.t > range1.second.t)
                range2.second = r;
            hasIntersection = true;
        }
    }
    for (const auto& prim : m_s2.getPrims())
    {
        Ray r = ray;
        if (prim->intersect(r))
        {
            if (r.t < range2.first.t)
                range2.first = r;
            if (r.t > range2.second.t)
                range2.second = r;
            hasIntersection = true;
        }
    }
    if (!hasIntersection)
        return false;
    double t = 0;
    switch (m_opType) {
        case Union:
            t = MIN(range1.first.t, range2.first.t);
            if (abs(t - range1.first.t) < Epsilon)
                ray = range1.first;
            else if (abs(t - range2.first.t) < Epsilon)
                ray = range2.first;
            break;
        case Intersection:
            t = MAX(range1.first.t, range2.first.t);
            if (abs(t) >= Infty)
                return false;
            if (abs(t - range1.first.t) < Epsilon)
                ray = range1.first;
            else if (abs(t - range2.first.t) < Epsilon)
                ray = range2.first;
            break;
        case Subtraction:
            RT_WARNING("This functionality is not implemented yet");
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
                                           rt::OperationType operationType) : IPrim(std::move(pShader)){
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
            RT_WARNING("This functionality is not implemented yet");
            for (int i = 0; i < 3; i++)
            {
                minPt[i] = boxA.getMinPoint()[i];
                maxPt[i] = boxA.getMaxPoint()[i];
            }
            break;
        default:
            break;
    }
    m_boundingBox = CBoundingBox(minPt, maxPt);
}

rt::CCompositeGeometry::CCompositeGeometry(const rt::ptr_shader_t& pShader,
                                           const rt::CSolid &s1, const rt::ptr_prim_t &p2,
                                           rt::OperationType operationType) : CCompositeGeometry(pShader, s1, CSolid(p2), operationType) {
}

rt::CCompositeGeometry::CCompositeGeometry(const rt::ptr_shader_t &pShader, const rt::ptr_prim_t &p1, const rt::ptr_prim_t &p2,
                                           rt::OperationType operationType) : CCompositeGeometry(pShader, CSolid(p1), CSolid(p2), operationType) {
}