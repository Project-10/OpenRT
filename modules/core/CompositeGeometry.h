#pragma once

#include "IPrim.h"
#include "IntersectionRange.h"
#include "Solid.h"

namespace rt {
    enum OperationType {Intersection, Subtraction, Union};
    class CCompositeGeometry : public IPrim {
    public:
        DllExport explicit CCompositeGeometry(ptr_shader_t pShader, const CSolid& s1, const CSolid& s2, OperationType operationType);

        DllExport bool 			intersect(Ray& ray) const override;

        DllExport bool 			if_intersect(const Ray& ray) const override;

        DllExport void 			transform(const Mat& T) override;

        DllExport Vec3f 		getNormal(const Ray& ray) const override;

        DllExport Vec2f			getTextureCoords(const Ray& ray) const override;

        DllExport CBoundingBox	getBoundingBox() const override;
    private:
        CSolid m_s1;
        CSolid m_s2;
        OperationType m_opType;
        CBoundingBox m_boundingBox;
    };

}