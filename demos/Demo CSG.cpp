#include <fstream>
#include "openrt.h"
#include "core/timer.h"

using namespace rt;


int main() {
    const Vec3f bgColor = RGB(1, 1, 1);
    const Size resolution = Size(1920, 1200);
    const float intensity = 5e4;

    // Scene
    CScene scene(bgColor);

    // Shaders
    auto pDarkBlue = std::make_shared<CShaderPhong>(scene, RGB(47 / 255.0, 60 / 255.0, 126 / 255.0), 0.3f, 0.9f, 0.7f, 40.0f);
    auto pSunsetOrange = std::make_shared<CShaderPhong>(scene, RGB(251 / 255.0, 234 / 255.0, 235 / 255.0), 0.1f, 0.9f, 0.6f, 40.0f);
    auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.5f, 0.9f, 0.1f, 40.0f);

    auto eyelight = std::make_shared<CShaderEyelight>(RGB(251 / 255.0, 234 / 255.0, 235 / 255.0));

    // Geometries
    ptr_prim_t primSphere = std::make_shared<CPrimSphere>(pSunsetOrange, Vec3f(0, 0.0f, -10), 1.0f);
    auto solidBox = CSolidBox(pDarkBlue, Vec3f(0, 0.0f, -10), 2, 2, 2);
    auto solidTorus = CSolidTorus(pSunsetOrange, Vec3f(0, 0.0f, -10), 1, 0.5, 10, false);
    solidTorus.transform(CTransform().rotate(Vec3f(1, 0, 0), 90).get());
    ptr_prim_t pComposize	 = std::make_shared<CCompositeGeometry>(solidBox, solidTorus, BoolOp::Difference);
    scene.add(pComposize);
    float s = 50;
    float elevation = -2.0f;
    scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, elevation, -s), Vec3f(-s, elevation, s), Vec3f(s, elevation, s), Vec3f(s, elevation, -s)));
    //auto floor = std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, elevation, 0), Vec3f(0, 1, 0));

    // cameras
    auto targetCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-2, 3, -5), pComposize->getBoundingBox().getCenter(), Vec3f(0, 1, 0), 45.0f);
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
