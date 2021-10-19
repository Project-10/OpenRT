#include "openrt.h"
#include "core/timer.h"

using namespace rt;

ptr_prim_t createCompositeDice(const ptr_shader_t& shader) {
    auto solidSphere2 = CSolidSphere(shader, Vec3f(0, -3.0f, -7), 0.2f, 24, true);
    auto solidSphere3 = CSolidSphere(shader, Vec3f(0.5f, -3.0f, -7), 0.2f, 24, true);
    auto solidSphere4 = CSolidSphere(shader, Vec3f(-0.5f, -3.0f, -7), 0.2f, 24, true);
    auto solidSphere5 = CSolidSphere(shader, Vec3f(0, -2.5f, -7), 0.2f, 24, true);
    auto solidSphere6 = CSolidSphere(shader, Vec3f(0.5f, -2.5f, -7), 0.2f, 24, true);
    auto solidSphere7 = CSolidSphere(shader, Vec3f(-0.5f, -2.5f, -7), 0.2f, 24, true);
    auto solidSphere8 = CSolidSphere(shader, Vec3f(0, -3.5f, -7), 0.2f, 24, true);
    auto solidSphere9 = CSolidSphere(shader, Vec3f(0.5f, -3.5f, -7), 0.2f, 24, true);
    auto solidSphere10 = CSolidSphere(shader, Vec3f(-0.5f, -3.5f, -7), 0.2f, 24, true);
    ptr_prim_t temp = std::make_shared<CCompositeGeometry>(solidSphere2, solidSphere3, BoolOp::Union);
    ptr_prim_t row1 = std::make_shared<CCompositeGeometry>(temp, solidSphere4, BoolOp::Union);
    ptr_prim_t temp2 = std::make_shared<CCompositeGeometry>(solidSphere5, solidSphere6, BoolOp::Union);
    ptr_prim_t row2 = std::make_shared<CCompositeGeometry>(temp2, solidSphere7, BoolOp::Union);
    ptr_prim_t temp3 = std::make_shared<CCompositeGeometry>(solidSphere8, solidSphere9, BoolOp::Union);
    ptr_prim_t row3 = std::make_shared<CCompositeGeometry>(temp3, solidSphere10, BoolOp::Union);
    ptr_prim_t temp4 = std::make_shared<CCompositeGeometry>(row1, row2, BoolOp::Union);
    return std::make_shared<CCompositeGeometry>(row3, temp4, BoolOp::Union);
}

int main() {
    const Vec3f bgColor     = RGB(0, 0, 0);
    const Size  resolution  = Size(1000, 1000);
    const float intensity   = 1e9;

    // Scene
    CScene scene(bgColor);

    // textures
    auto pTextureEarth  = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");

    // Shaders
    auto pShaderEarth   = std::make_shared<CShaderPhong>(scene, pTextureEarth, 0.1f, 0.9f, 0.1f, 5.0f);
    auto pShaderCore    = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 0), 0.8f, 0.2f, 0.0f, 40.0f);
    auto pShaderCut     = std::make_shared<CShaderPhong>(scene, RGB(0.8f, 0.2f, 0), 0.3f, 0.7f, 0, 40);

    // Geometries
    auto earth              = CSolidSphere(pShaderEarth, Vec3f(0, 0, 0), 1, 24);
    auto core               = CSolidSphere(pShaderCore, Vec3f(0, 0, 0), 0.55f, 24);
    //ptr_prim_t earth        = std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0, 0), 1);
    //ptr_prim_t core         = std::make_shared<CPrimSphere>(pShaderCore, Vec3f(0, 0, 0), 0.55f);

    auto box                = CSolidBox(pShaderCut, Vec3f(0.5f, 0.5f, 0.5f), 0.5f);
    ptr_prim_t composite1   = std::make_shared<CCompositeGeometry>(earth, box, BoolOp::Difference);
    ptr_prim_t composite2   = std::make_shared<CCompositeGeometry>(composite1, core, BoolOp::Union);

    CTransform t;
    composite2->transform(t.rotate(Vec3f(0, 1, 0), -15).scale(2, 1, 1).get());

    scene.add(composite2);
    //scene.add(core);

    // Light
    auto sun            = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(23500, 0, 0), true);
    scene.add(sun);

    // cameras
    auto camera         = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(3, 2, 3), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 35.0f);
    scene.add(camera);

    scene.buildAccelStructure(20, 3);

    // Add everything to scene
    Timer::start("Rendering... ");
    Mat img = scene.render(std::make_shared<CSamplerStratified>(3, true, true));
    Timer::stop();

    imshow("image", img);
    waitKey();
    return 0;
}
