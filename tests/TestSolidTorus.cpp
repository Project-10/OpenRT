#include "TestSolidTorus.h"
#include "core/BoundingBox.h"

using namespace rt;

TEST_F(CTestSolidTorus, solid_torus) {
    auto shader = std::make_shared<CShaderFlat>(RGB(1, 1, 1));
    auto innerRadius = 3.0f;
    auto outerRadius = 1.0f;
    auto sides = 30;
    auto torus = CSolidTorus(shader, Vec3f::all(0), innerRadius, outerRadius, sides);

    // we multiply by 2 because each quad contains 2 triangles.
    // On n sides input number of tris is total = (n^2) * 2.
    EXPECT_EQ((sides * sides) * 2, torus.getPrims().size());

    // Check assertions
    EXPECT_DEATH(CSolidTorus(shader, Vec3f::all(0), 2, 1, 2), "");
    EXPECT_DEATH(CSolidTorus(shader, Vec3f::all(0), 1, 2, 6), "");
}
