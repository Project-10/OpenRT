#include <fstream>
#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
    const Vec3f bgColor = RGB(0.3, 0.3, 0.3);
    const Size resolution = Size(1920, 1200);
    const float intensity = 5e4;

    // Scene
    CScene scene(bgColor);

    auto pTextureEarth = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
    auto pShaderEarth = std::make_shared<CShaderPhong>(scene, pTextureEarth, 0.2f, 0.7f, 0.0f, 40.0f);

    // Shaders
    auto pDarkBlue = std::make_shared<CShaderPhong>(scene, RGB(47 / 255.0, 60 / 255.0, 126 / 255.0), 0.1f, 0.9f, 0, 40.0f);
    auto pSunsetOrange = std::make_shared<CShaderPhong>(scene, RGB(251 / 255.0, 234 / 255.0, 235 / 255.0), 0.1f, 0.9f, 0, 40.0f);
    auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);
    // auto pShaderFloor = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
    // auto pShaderRed = std::make_shared<CShaderEyelight>(RGB(1, 0, 0));
    // auto pShaderBlue = std::make_shared<CShaderEyelight>(RGB(0, 0, 1));

    // Geometries
    auto 		solidSphere1 = CSolidSphere(pShaderEarth, Vec3f(1, 0.1f, -13), 1.5f, 24, true);
    auto 		solidSphere2 = CSolidSphere(pShaderEarth, Vec3f(0, 0.1f, -13), 1.5f, 24, true);
	ptr_prim_t 	pPrimSphere  = std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0.1f, -13), 1.5f);
	ptr_prim_t 	pComposize	 = std::make_shared<CCompositeGeometry>(solidSphere1, solidSphere2, BoolOp::Union);
	scene.add(pComposize);

    // Try it with Cylinders!
    //auto solidCylinder2 = CSolidCylinder(pDarkBlue, Vec3f(1, 0.1f, -13),1.5, 4.1f);
    //auto solidCylinder = CSolidCylinder(pSunsetOrange, Vec3f(0, 0.1f, -13),1.5, 4);
    //scene.add(std::make_shared<CCompositeGeometry>(pShaderRed, solidCylinder2, solidCylinder, rt::Union));
    float s = 100;

    //Floor
    //scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));

    // cameras
    const float r = 10;
    auto front = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 7, 8), Vec3f(0, -0.4, -1), Vec3f(0, 1, 0), 45.0f);
    auto back = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 20, -30), Vec3f(0, -1, 1), Vec3f(0, 1, 0), 45.0f);
    auto top = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 22, -5), Vec3f(0, -1, -0.5), Vec3f(0, 0, -1), 45.0f);
    auto cam45 = std::make_shared<CCameraPerspective>(resolution, Vec3f(35, 20, -30), Vec3f(-2, -1.1, 1), Vec3f(0, 1, 0), 45.0f);
    auto frontTilted = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 22, 8), Vec3f(0, -1, -1), Vec3f(0, 1, 0), 45.0f);
    scene.add(cam45);

    scene.buildAccelStructure(20, 2);

    // Light
    auto pLight = std::make_shared<CLightOmni>(intensity * RGB(1.0f, 0.839f, 0.494f), Vec3f(100, 150.0f, 100), false);

    // Add everything to scene

    scene.add(pLight);
    Timer::start("Rendering... ");
    Mat img = scene.render();
    Timer::stop();

    //std::string counterPath = "../../../num.txt";

    //int renderCount = 0;
	//std::ifstream i(counterPath, std::ios::binary);
    //i.read((char *) &renderCount, sizeof(renderCount));
    //imwrite("../../../render_" + std::to_string(renderCount) + ".png", img);
    //renderCount++;
    //std::ofstream o(counterPath, std::ios::binary);
    //o.write((char *) &renderCount, sizeof(renderCount));
    //o.close();
    imshow("image", img);
    waitKey();
    return 0;
}
