#include "TestSolid.h"
#include "core/BoundingBox.h"

using namespace rt;
TEST_F(CTestSolid, solid_sphere) {
    auto shader = std::make_shared<CShaderFlat>(RGB(1, 1, 1));
    auto radius = 3.0f;
    auto n_sides = 22;
    auto sphere = CSolidSphere(shader, Vec3f::all(0), radius, n_sides, true);
    // we multiply by 2 because each quad contains 2 triangles.
    // On n sides input number of tris is total = n^2 - 2*n.
    EXPECT_EQ(n_sides * (n_sides - 2), sphere.getPrims().size());

    // The bounding
    CBoundingBox box;
    for (const auto& prim : sphere.getPrims())
        box.extend(prim->getBoundingBox());
    for (auto pt_value : box.getMaxPoint().val)
        EXPECT_NEAR(pt_value, radius, 0.2);
}
