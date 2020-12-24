#include <core/CompositeGeometry.h>
#include <fstream>
#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main()
{
    const Vec3f	bgColor = RGB(0, 0, 0);
    const Size	resolution = Size(1920, 1200);
    const float intensity = 5e4;

    // Scene
    CScene scene(bgColor);

    // Shaders
   // auto pShaderRed		= std::make_shared<CShaderPhong>(scene, RGB(1, 0, 0), 0.1f, 0.9f, 0, 40.0f);
   // auto pShaderBlue	= std::make_shared<CShaderPhong>(scene, RGB(0, 0, 1), 0.1f, 0.9f, 0, 40.0f);
   auto pShaderRed = std::make_shared<CShaderEyelight>(RGB(1, 0, 0));
   auto pShaderBlue = std::make_shared<CShaderEyelight>(RGB(0, 0, 1));
   //auto pShaderFloor = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
   auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);

    // Geometries
    //auto primSphere = std::make_shared<CPrimSphere>(pShaderRed, Vec3f(0, 0, -15), 3);
    auto solidCylinder2 = CSolidCylinder(pShaderRed, Vec3f(1, 0.1f, -13),1.5, 4.1f);
    auto solidCylinder = CSolidCylinder(pShaderBlue, Vec3f(0, 0.1f, -13),1.5, 4);
    float s = 100;
    //Floor
    scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
    //scene.add(primSphere);
    //scene.add(solidCylinder);
    //scene.add(solidCylinder2);
    scene.add(std::make_shared<CCompositeGeometry>(pShaderRed, solidCylinder2, solidCylinder, rt::Union));
    // cameras
    const float r = 10;
    auto front = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 7, 8), Vec3f(0, -0.4, -1), Vec3f(0, 1, 0), 45.0f);
    auto back = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 20, -30), Vec3f(0, -1, 1), Vec3f(0, 1, 0), 45.0f);
    auto top = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 22,-5), Vec3f(0, -1, -0.5), Vec3f(0, 0, -1), 45.0f);
    auto cam45 = std::make_shared<CCameraPerspective>(resolution, Vec3f(35, 20, -30), Vec3f(-2, -1.1, 1), Vec3f(0, 1, 0), 45.0f);
    auto frontTilted = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 22, 8), Vec3f(0, -1, -1), Vec3f(0, 1, 0), 45.0f);
    scene.add(frontTilted);

    scene.buildAccelStructure(20, 2);

    // Light
    auto pLight			= std::make_shared<CLightOmni>(intensity * RGB(1.0f, 0.839f, 0.494f), Vec3f(100, 100.0f, 100), false);

    // Add everything to scene

    scene.add(pLight);
    Timer::start("Rendering... ");
    Mat img = scene.render();
    Timer::stop();

    std::string counterPath = "../../../num.txt";

    int renderCount=0;
    std::ifstream i(counterPath,std::ios::binary);
    i.read((char*)&renderCount,sizeof(renderCount));
    imwrite("../../../render_" + std::to_string(renderCount) + ".png", img);
    renderCount++;
    std::ofstream o(counterPath,std::ios::binary);
    o.write((char*)&renderCount,sizeof(renderCount));
    o.close();
    imshow("image", img);
    waitKey();
    return 0;
}