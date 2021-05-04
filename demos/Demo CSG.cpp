#include <fstream>
#include "openrt.h"
#include "core/timer.h"

using namespace rt;

ptr_prim_t createCompositeDice(const ptr_shader_t& shader) {
    auto solidSphere2 = CSolidSphere(shader, Vec3f(0, -3.0f, -7), 0.2, 24, true);
    auto solidSphere3 = CSolidSphere(shader, Vec3f(0.5, -3.0f, -7), 0.2, 24, true);
    auto solidSphere4 = CSolidSphere(shader, Vec3f(-0.5, -3.0f, -7), 0.2, 24, true);
    auto solidSphere5 = CSolidSphere(shader, Vec3f(0, -2.5f, -7), 0.2, 24, true);
    auto solidSphere6 = CSolidSphere(shader, Vec3f(0.5, -2.5f, -7), 0.2, 24, true);
    auto solidSphere7 = CSolidSphere(shader, Vec3f(-0.5, -2.5f, -7), 0.2, 24, true);
    auto solidSphere8 = CSolidSphere(shader, Vec3f(0, -3.5f, -7), 0.2, 24, true);
    auto solidSphere9 = CSolidSphere(shader, Vec3f(0.5, -3.5f, -7), 0.2, 24, true);
    auto solidSphere10 = CSolidSphere(shader, Vec3f(-0.5, -3.5f, -7), 0.2, 24, true);
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
    const Vec3f bgColor = RGB(1, 1, 1);
    const Size resolution = Size(1920, 1200);
    const float intensity = 5e4;

    // Scene
    CScene scene(bgColor);

    // Shaders
    auto pDarkBlue = std::make_shared<CShaderPhong>(scene, RGB(47 / 255.0, 60 / 255.0, 126 / 255.0), 0.3f, 0.9f, 0.0f, 40.0f);
    auto pSunsetOrange = std::make_shared<CShaderPhong>(scene, RGB(251 / 255.0, 234 / 255.0, 235 / 255.0), 0.1f, 0.8f, 0.0f, 40.0f);
    auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.5f, 0.9f, 0.0f, 40.0f);

    auto eyelight = std::make_shared<CShaderEyelight>(RGB(251 / 255.0, 234 / 255.0, 235 / 255.0));

    // Geometries
    ptr_prim_t primSphere = std::make_shared<CPrimSphere>(pDarkBlue, Vec3f(0, 0.0f, -10), 1.4f);
    auto solidCylinder = CSolidCylinder(pSunsetOrange, Vec3f(0, -2, -10), 0.8f, 4.0f, 10, 24, true);
    auto solidCylinder2 = CSolidCylinder(pSunsetOrange, Vec3f(2, 0, -10), 0.8f, 4.0f, 10, 24, true);
    auto solidCylinder3 = CSolidCylinder(pSunsetOrange, Vec3f(0, 0, -12), 0.8f, 4.0f, 10, 24, true);
    solidCylinder2.transform(CTransform().rotate(Vec3f(0, 0, 1), 90).get());
    solidCylinder3.transform(CTransform().rotate(Vec3f(1, 0, 0), 90).get());
    ptr_prim_t pComposite1 = std::make_shared<CCompositeGeometry>(solidCylinder, solidCylinder2, BoolOp::Union);
    ptr_prim_t pComposite2 = std::make_shared<CCompositeGeometry>(pComposite1, solidCylinder3, BoolOp::Union);
    ptr_prim_t finalComposite = std::make_shared<CCompositeGeometry>(primSphere, pComposite2, BoolOp::Difference);
    //scene.add(finalComposite);

    auto pDiceShader = std::make_shared<CShaderPhong>(scene, RGB(6 / 255.0, 214 / 255.0, 160 / 255.0), 0.3f, 0.9f, 0.0f, 40.0f);
    auto pDiceShader2 = std::make_shared<CShaderPhong>(scene, RGB(239 / 255.0, 71 / 255.0, 111 / 255.0), 0.1f, 0.8f, 0.0f, 40.0f);
    auto solidBox = CSolidBox(pDiceShader, Vec3f(0, -3, -8), 2, 2, 2);
    ptr_prim_t dice = std::make_shared<CCompositeGeometry>(solidBox, createCompositeDice(pDiceShader2), BoolOp::Difference);
    scene.add(dice);

    auto torusShader = std::make_shared<CShaderPhong>(scene, RGB(255 / 255.0, 209 / 255.0, 102 / 255.0), 0.3f, 0.9f, 0.3f, 40.0f);
    auto solidBox2 = CSolidBox(pDiceShader, Vec3f(3, -3, -8), 2, 2, 2);
    auto solidTorus = CSolidTorus(torusShader,Vec3f(3, -3, -8), 2, 1, 24, true);
    auto solidTorus2 = CSolidTorus(torusShader,Vec3f(3, -3, -8), 2, 1, 24, true);
    auto solidTorus3 = CSolidTorus(torusShader,Vec3f(3, -3, -8), 2, 1, 24, true);
    solidTorus2.transform(CTransform().rotate(Vec3f(1, 0, 0), 90).get());
    solidTorus3.transform(CTransform().rotate(Vec3f(0, 1, 0), 90).get());
    ptr_prim_t tempComposite = std::make_shared<CCompositeGeometry>(solidTorus, solidTorus2, BoolOp::Union);
    ptr_prim_t tempComposite2 = std::make_shared<CCompositeGeometry>(tempComposite, solidTorus3, BoolOp::Union);
    ptr_prim_t finalTorusComposite = std::make_shared<CCompositeGeometry>(solidBox2, tempComposite2, BoolOp::Union);
    //scene.add(finalTorusComposite);


    float s = 30;
    float elevation = -5.0f;
    auto pGlossinessSampler = std::make_shared<CSamplerRandom>(3);
    scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, elevation, -s), Vec3f(-s, elevation, s), Vec3f(s, elevation, s), Vec3f(s, elevation, -s)));

    // cameras
    auto targetCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-3, 4, 3), dice->getBoundingBox().getCenter(), Vec3f(0, 1, 0), 45.0f);
    scene.add(targetCamera);

    scene.buildAccelStructure(20, 3);

    // Light
    auto pLight = std::make_shared<CLightOmni>(intensity * RGB(1.0f, 0.839f, 0.494f), Vec3f(150.0f, 150.0f, 150.0f), true);

    // Add everything to scene
    scene.add(pLight);
    Timer::start("Rendering... ");
    Mat img = scene.render();
    Timer::stop();

    imshow("image", img);
    waitKey();
    return 0;
}
