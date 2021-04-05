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
    auto pDarkBlue = std::make_shared<CShaderPhong>(scene, RGB(47 / 255.0, 60 / 255.0, 126 / 255.0), 0.1f, 0.9f, 0, 40.0f);
    auto pSunsetOrange = std::make_shared<CShaderPhong>(scene, RGB(251 / 255.0, 234 / 255.0, 235 / 255.0), 0.1f, 0.9f, 0, 40.0f);
    auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);

    auto pShaderBlue = std::make_shared<CShaderEyelight>(RGB(240.0/ 255.0, 240.0/255.0, 230.0/255.0));
    auto pShaderOrange = std::make_shared<CShaderEyelight>((217.0/ 255.0, 4.0/255.0, 41/255.0));


    // Geometries
    auto solidSphere1 = CSolidSphere(pShaderBlue, Vec3f(1, 0.1f, -13), 1.3f, 30, false);
    auto solidSphere2 = CSolidSphere(pShaderBlue, Vec3f(1, 0.1f, -12), 1.0f, 30, false);
    auto solidBox = CSolidBox(pShaderOrange, Vec3f(Vec3f(1, 0.1f, -13)), 2, 2, 2);
    auto pComposize	 = std::make_shared<CCompositeGeometry>(solidBox, solidSphere1, BoolOp::Difference);
    scene.add(pComposize);

    // cameras
    auto targetCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-2, 3, -3), pComposize->getBoundingBox().getCenter(), Vec3f(0, 1, 0), 45.0f);
    scene.add(targetCamera);

    scene.buildAccelStructure(20, 2);
    //pComposize->buildAccelStructure();

    // Light
    auto pLight = std::make_shared<CLightOmni>(intensity * RGB(1.0f, 0.839f, 0.494f), Vec3f(100, 150.0f, 100), false);

    // Add everything to scene
    scene.add(pLight);
    Timer::start("Rendering... ");
    Mat img = scene.render();
    Timer::stop();

    imshow("image", img);
    waitKey();
    return 0;
}
