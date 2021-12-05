#include "PrimDummy.h"
#include <macroses.h>

namespace rt {
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

    CBoundingBox CPrimDummy::getBoundingBox() const {
        RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
    }
};
