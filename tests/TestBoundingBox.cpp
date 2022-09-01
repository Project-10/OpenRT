#include "TestBoundingBox.h"
#include "core/BoundingBox.h"

using namespace rt;

TEST_F(CTestBoundingBox, solid_sphere) {
    auto boundingBox = rt::CBoundingBox(Vec3f(0, 0, 0), Vec3f(1, 1, 1));
    for (auto pt_value : boundingBox.getCenter().val)
        EXPECT_NEAR(pt_value, 0.5f, Epsilon);

    auto boundingBox2 = rt::CBoundingBox(Vec3f(-1, -1, -1), Vec3f(0, 0, 0));
    for (auto pt_value : boundingBox2.getCenter().val)
        EXPECT_NEAR(pt_value, -0.5f, Epsilon);

    auto boundingBox3 = rt::CBoundingBox(Vec3f(-100, -100, -100), Vec3f(100, 100, 100));
    for (auto pt_value : boundingBox3.getCenter().val)
        EXPECT_NEAR(pt_value, 0, Epsilon);

    auto boundingBox4 = rt::CBoundingBox(Vec3f(-100, -100, -100), Vec3f(100, 100, 100));
    auto pShaderSphere = std::make_shared<CShaderEyelight>(RGB(255, 255, 255));
    auto solidSphere1 = CSolidSphere(pShaderSphere, Vec3f(0, 0, 0), 1.0f, 24, true);
    auto solidSphere2 = CSolidSphere(pShaderSphere, Vec3f(1, 0, 0), 1.0f, 24, true);
    ptr_prim_t 	pComposite = std::make_shared<CPrimBoolean>(solidSphere1, solidSphere2, BoolOp::Union);
    auto boxCenter = pComposite->getBoundingBox().getCenter();
    EXPECT_NEAR(boxCenter[0], 0.5, Epsilon);
    EXPECT_NEAR(boxCenter[1], 0, Epsilon);
    EXPECT_NEAR(boxCenter[2], 0, Epsilon);
}
