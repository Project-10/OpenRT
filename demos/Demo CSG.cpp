#include <fstream>
#include "openrt.h"
#include "core/timer.h"

using namespace rt;

ptr_prim_t createDice(ptr_shader_t pDiceShader) {
    // First Side
    auto solidSphere_S1_1 = CSolidSphere(pDiceShader, Vec3f(-15, 0, -13), 2, 100, true);
    auto solidSphere_S1_2 = CSolidSphere(pDiceShader, Vec3f(-15, 7.5, -13), 2, 100, true);
    auto solidSphere_S1_3 = CSolidSphere(pDiceShader, Vec3f(-15, -7.5, -13), 2, 100, true);
    auto solidSphere_S1_4 = CSolidSphere(pDiceShader, Vec3f(-15, -7.5, -5.5), 2, 100, true);
    auto solidSphere_S1_5 = CSolidSphere(pDiceShader, Vec3f(-15, -7.5, -20.5), 2, 100, true);
    auto solidSphere_S1_6 = CSolidSphere(pDiceShader, Vec3f(-15, 7.5, -5.5), 2, 100, true);
    auto solidSphere_S1_7 = CSolidSphere(pDiceShader, Vec3f(-15, 7.5, -20.5), 2, 100, true);
    auto solidSphere_S1_8 = CSolidSphere(pDiceShader, Vec3f(-15, 0, -5.5), 2, 100, true);
    auto solidSphere_S1_9 = CSolidSphere(pDiceShader, Vec3f(-15, 0, -20.5), 2, 100, true);

    // Second Side
    auto solidSphere_S2_1 = CSolidSphere(pDiceShader, Vec3f(0, 0, -28), 2, 100, true);
    auto solidSphere_S2_2 = CSolidSphere(pDiceShader, Vec3f(-7.5, 0, -28), 2, 100, true);
    auto solidSphere_S2_3 = CSolidSphere(pDiceShader, Vec3f(7.5, 0, -28), 2, 100, true);
    auto solidSphere_S2_4 = CSolidSphere(pDiceShader, Vec3f(0, 7.5, -28), 2, 100, true);
    auto solidSphere_S2_5 = CSolidSphere(pDiceShader, Vec3f(-7.5, 7.5, -28), 2, 100, true);
    auto solidSphere_S2_6 = CSolidSphere(pDiceShader, Vec3f(7.5, 7.5, -28), 2, 100, true);
    auto solidSphere_S2_7 = CSolidSphere(pDiceShader, Vec3f(0, -7.5, -28), 2, 100, true);
    auto solidSphere_S2_8 = CSolidSphere(pDiceShader, Vec3f(-7.5, -7.5, -28), 2, 100, true);
    auto solidSphere_S2_9 = CSolidSphere(pDiceShader, Vec3f(7.5, -7.5, -28), 2, 100, true);

    // Box
    auto solidBox = CSolidBox(pDiceShader, Vec3f(Vec3f(0, 0, -13)), 30, 30, 30);

    // All together
    ptr_prim_t pComposize_1	 = std::make_shared<CCompositeGeometry>(solidBox, solidSphere_S2_1, BoolOp::Difference);
    ptr_prim_t pComposize_2	 = std::make_shared<CCompositeGeometry>(pComposize_1, solidSphere_S2_2, BoolOp::Difference);
    ptr_prim_t pComposize_3	 = std::make_shared<CCompositeGeometry>(pComposize_2, solidSphere_S2_3, BoolOp::Difference);
    ptr_prim_t pComposize_4	 = std::make_shared<CCompositeGeometry>(pComposize_3, solidSphere_S2_4, BoolOp::Difference);
    ptr_prim_t pComposize_5	 = std::make_shared<CCompositeGeometry>(pComposize_4, solidSphere_S2_5, BoolOp::Difference);
    ptr_prim_t pComposize_6	 = std::make_shared<CCompositeGeometry>(pComposize_5, solidSphere_S2_6, BoolOp::Difference);
    ptr_prim_t pComposize_7 = std::make_shared<CCompositeGeometry>(pComposize_6, solidSphere_S2_7, BoolOp::Difference);
    ptr_prim_t pComposize_8	 = std::make_shared<CCompositeGeometry>(pComposize_7, solidSphere_S2_8, BoolOp::Difference);
    ptr_prim_t pComposize_9	 = std::make_shared<CCompositeGeometry>(pComposize_8, solidSphere_S2_9, BoolOp::Difference);
    ptr_prim_t pComposize	 = std::make_shared<CCompositeGeometry>(pComposize_9, solidSphere_S1_1, BoolOp::Difference);
    ptr_prim_t pComposize2	 = std::make_shared<CCompositeGeometry>(pComposize, solidSphere_S1_2, BoolOp::Difference);
    ptr_prim_t pComposize3	 = std::make_shared<CCompositeGeometry>(pComposize2, solidSphere_S1_3, BoolOp::Difference);
    ptr_prim_t pComposize4	 = std::make_shared<CCompositeGeometry>(pComposize3, solidSphere_S1_4, BoolOp::Difference);
    ptr_prim_t pComposize5	 = std::make_shared<CCompositeGeometry>(pComposize4, solidSphere_S1_5, BoolOp::Difference);
    ptr_prim_t pComposize6	 = std::make_shared<CCompositeGeometry>(pComposize5, solidSphere_S1_6, BoolOp::Difference);
    ptr_prim_t pComposize7	 = std::make_shared<CCompositeGeometry>(pComposize6, solidSphere_S1_7, BoolOp::Difference);
    ptr_prim_t pComposize8	 = std::make_shared<CCompositeGeometry>(pComposize7, solidSphere_S1_8, BoolOp::Difference);
    ptr_prim_t pComposize9	 = std::make_shared<CCompositeGeometry>(pComposize8, solidSphere_S1_9, BoolOp::Difference);
    return pComposize9;
}


int main() {
    const Vec3f bgColor = RGB(0, 0, 0);
    const Size resolution = Size(1920, 1200);
    const float intensity = 5e4;

    // Scene
    CScene scene(bgColor);

    // Shaders
    auto pDiceShader = std::make_shared<CShaderPhong>(scene, RGB(0.447, 0.345, 0.019), 0.4f, 0.9f, 0.3f, 40.0f);
    auto pShaderDice = std::make_shared<CShaderPhong>(scene, RGB(0.153f, 0.682f, 0.376f), 0.2f, 0.8f, 0.5f, 40.0f);

    // Geometries
    auto pComposite = createDice(pShaderDice);
    scene.add(pComposite);

    // Floor
    auto pGlossinessSampler = std::make_shared<CSamplerRandom>(2);
    auto pShaderFloor = std::make_shared<CShaderChrome>(scene, pGlossinessSampler);
    float s = 1000;
    scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, -25, -s), Vec3f(-s, -25, s), Vec3f(s, -25, s), Vec3f(s, -25, -s)));

    // cameras
    auto targetCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-125, 10, -100), pComposite->getBoundingBox().getCenter(), Vec3f(0, 1, 0), 45.0f);
    scene.add(targetCamera);

    scene.buildAccelStructure(20, 2);

    // Light
    auto pLight = std::make_shared<CLightOmni>(intensity * RGB(1.0f, 0.839f, 0.494f), Vec3f(-120, 200.0f, -100), true);

    // Add everything to scene
    scene.add(pLight);
    Timer::start("Rendering... ");
    Mat img = scene.render(std::make_shared<CSamplerStratified>(2, true, true));
    Timer::stop();

    imshow("image", img);
    waitKey();
    return 0;
}
