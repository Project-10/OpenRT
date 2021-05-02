#include "PrimDummy.h"
#include "macroses.h"

namespace rt {
bool CPrimDummy::intersect(rt::Ray &ray) const {
    RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
}

bool CPrimDummy::if_intersect(const rt::Ray &ray) const {
    RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
}

void CPrimDummy::transform(const Mat &T) {
    RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
}

CBoundingBox CPrimDummy::getBoundingBox(void) const {
    RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
}

Vec3f CPrimDummy::getOrigin(void) const {
    RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
}
}
