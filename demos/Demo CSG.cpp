#include <core/CompositeGeometry.h>
#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main()
{
    const Vec3f	bgColor = RGB(0, 0, 0);
    const Size	resolution = Size(1920, 1200);
    const float intensity = 30;

    // Scene
    CScene scene(bgColor);

    // Shaders
    auto pShaderRed		= std::make_shared<CShaderEyelight>(RGB(1, 0, 0));
    auto pShaderBlue	= std::make_shared<CShaderEyelight>(RGB(0, 0, 1));

    //Floor
    scene.add(std::make_shared<CCompositeGeometry>(pShaderRed, CSolidCylinder(pShaderRed, Vec3f(4, 0, 0), 1.2, 5), CSolidCylinder(pShaderBlue, Vec3f(5, 0, 0), 1.5, 5), rt::Union));
    //scene.add(std::make_shared<CCompositeGeometry>(pShaderBlue, CSolidCylinder(pShaderRed, Vec3f(5, 0, 0), 2, 5), CSolidCylinder(pShaderBlue2, Vec3f(4, 0, 0), 2, 5), rt::Intersection));
    //scene.add(CSolidCylinder(pShaderBlue, Vec3f(4, 0, 0), 2, 5));
    //scene.add(CSolidCylinder(pShaderRed, Vec3f(5, 0, 0), 2, 5));

    // camera
    auto mainCam = std::make_shared<CCameraPerspective>(resolution, Vec3f(5, 8, 8), Vec3f(0, -0.5, -1), Vec3f(0, 1, 0), 60.0f);

    //scene.buildAccelStructure();

    // Light
    auto pLight			= std::make_shared<CLightArea>(intensity * RGB(1.0f, 0.839f, 0.494f), Vec3f(343, 548.78f, 227), Vec3f(343, 548.78f, 332), Vec3f(213, 548.78f, 332), Vec3f(213, 548.78f, 227), std::make_shared<CSamplerStratified>(6, true, true));

    // Add everything to scene

    scene.add(mainCam);
    scene.add(pLight);
    Timer::start("Rendering... ");
    Mat img = scene.render(nullptr, true);
    Timer::stop();

    imwrite("../../../csg_1.png", img);
    imshow("image", img);
    waitKey();
    return 0;
}