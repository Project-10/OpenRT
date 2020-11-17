#include "TestCamera.h"
#include "core/Ray.h"

using namespace rt;

TEST(CTestSolidSphere, solid_sphere) {
    auto shader = std::make_shared<CShaderFlat>(RGB(1, 1, 1));
    auto sphere = CSolidSphere(shader, Vec3f::all(0), 2, 10);
    // we multiply by 2 because each quad contains 2 triangles.
    EXPECT_EQ(2*(11)*10, sphere.getPrims().size());
}

// Test that checks that the solid sphere is within the radius value.
TEST(CTestSolidSphere, solid_sphere_box) {
    auto radius = 3.0f;
    auto shader = std::make_shared<CShaderFlat>(RGB(1, 1, 1));
    auto sphere = CSolidSphere(shader, Vec3f::all(0), radius, 10);
    // we multiply by 2 because each quad contains 2 triangles.
    CBoundingBox box;
    for (const auto& prim : sphere.getPrims())
        box.extend(prim->getBoundingBox());
    for (auto pt_value : box.getMaxPoint().val)
        EXPECT_NEAR(pt_value, radius, 0.2);
}
