

#include <macroses.h>
#include "PrimDummy.h"


namespace rt {

    Vec2f CPrimDummy::getTextureCoords(const Ray &) const {
        return m_textureCoord;
    }

    bool CPrimDummy::intersect(Ray &) const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }

    bool CPrimDummy::if_intersect(const Ray &) const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }

    void CPrimDummy::transform(const Mat &T) {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");

    }

    Vec3f CPrimDummy::getOrigin() const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }

    Vec3f CPrimDummy::getNormal(const Ray &) const {
        return m_normal;
    }

    CBoundingBox CPrimDummy::getBoundingBox() const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }
};