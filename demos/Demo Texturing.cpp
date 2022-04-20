//#include "openrt.h"
//#include "core/timer.h"
//
//using namespace rt;
//
//int main() {
//
//    const Vec3f bgColor = RGB(0, 0, 0);
//    const Vec3f color = RGB(255, 255, 255);
//    const Size resolution = Size(1920, 1200);
//    const float intensity = 20;
//
//    // Scene
//    auto scene = std::make_shared<CScene>(bgColor);
//
//    auto Texture = std::make_shared<CTexture>();
//   auto shaderFlat = std::make_shared<CShaderFlat>(Texture);
////    auto box = CSolidBox(shaderFlat, Vec3f(-5, 0, 0), 1);
////    scene->add(box);
//
//    // Tea Pot
//    CSolid teaPot(shaderFlat, dataPath + "Tea Pot.onj");
//    CTransform t;
//    teaPot.transform(t.scale(5.01f).get());
//    scene->add(teaPot);
//
//    auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 20, 40), Vec3f(0, 10, 0), Vec3f(0, 1, 0), 45.0f);
//    auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 0));
//    auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(0, 100, 0), Vec3f(0, 0, 0), 15.0f, 30.0f);
//    scene->add(pCamera);
//    if (false) scene->add(pLightPoint);
//    else scene->add(pLightSpot);
//
//    scene->buildAccelStructure(25, 5);
//
//    Timer::start("Rendering...");
//    Mat img = scene->render(std::make_shared<CSamplerStratified>(2, true, true));
//    Timer::stop();
//    imshow("image", img);
//    waitKey();
//    //imwrite("out1.jpg", img);
//    return 0;
//}



#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
    const Vec3f		bgColor = RGB(0.1f, 0.1f, 0.1f);
    const Size		resolution = Size(800, 600);
    const float		intensity = 5000;

    CScene scene(bgColor);
    
    // Textures
	auto pTextureRings	 = std::make_shared<CTextureRings>(0.75f);
	auto pTextureStripes = std::make_shared<CTextureStripes>(5);

	// Shaders 
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderRings	= std::make_shared<CShaderPhong>(scene, pTextureRings, 0.1f, 0.9f, 0.0f, 40.0f);
    auto pShaderStripes	= std::make_shared<CShaderPhong>(scene, pTextureStripes, 0.1f, 0.9f, 0.0f, 40.0f);
    
	// Geometry
	scene.add(CSolidQuad(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));

	CSolid teapot(pShaderRings, dataPath + "teapot.obj");

    CTransform t;
	teapot.transform(t.scale(5.0f).get());
    scene.add(teapot);
    
    auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-10, 30, 30), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
    auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 0));
    auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(0, 100, 0), Vec3f(0, 0, 0), 15.0f, 30.0f);
    scene.add(pCamera);
    if (false) scene.add(pLightPoint);
    else scene.add(pLightSpot);

    scene.buildAccelStructure(25, 5);
    
    Timer::start("Rendering...");
    Mat img = scene.render(std::make_shared<CSamplerStratified>(2, true, true));
    Timer::stop();
    imshow("image", img);
    waitKey();
    //imwrite("out1.jpg", img);
    return 0;
}
