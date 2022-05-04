#include "openrt.h"
#include "core/timer.h"
#include"core/TextureWood.h"

using namespace rt;

int main() {
    const Vec3f		bgColor = RGB(0.1f, 0.1f, 0.1f);
    const Size		resolution = Size(800, 600);
    const float		intensity = 5000;

    CScene scene(bgColor);
    CScene scene1(bgColor);
    CScene scene2(bgColor);
    
    // Textures
	auto pTextureRings	 = std::make_shared<CTextureRings>(1.0f);
	auto pTextureStripes = std::make_shared<CTextureStripes>(5);
     auto pTextureWood = std::make_shared<CTextureWood>(1.5f);
     auto pTextureMarble = std::make_shared<CTextureMarble>(1.0f);

	// Shaders
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
 	auto pShaderFloor1	= std::make_shared<CShaderPhong>(scene1, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
   	auto pShaderFloor2	= std::make_shared<CShaderPhong>(scene2, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderRings	= std::make_shared<CShaderPhong>(scene, pTextureRings, 0.1f, 0.9f, 0.0f, 40.0f);
     auto pShaderStripes	= std::make_shared<CShaderPhong>(scene, pTextureStripes, 0.1f, 0.9f, 0.0f, 40.0f);
     auto pShaderWood	= std::make_shared<CShaderPhong>(scene1, pTextureWood, 0.1f, 0.9f, 0.0f, 200.0f);
     auto pShaderMarble	= std::make_shared<CShaderPhong>(scene2, pTextureMarble, 0.1f, 0.9f, 0.0f, 200.0f);

    
    
	// Geometry
	scene.add(CSolidQuad(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
     scene1.add(CSolidQuad(pShaderFloor1, Vec3f(0,-10,-0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
     scene2.add(CSolidQuad(pShaderFloor2, Vec3f(0,-10,-0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));


	CSolid teapot(pShaderStripes, dataPath + "teapot.obj");
     //CSolid teapot1(pShaderMarble, dataPath + "teapot.obj");
     auto solidSphere2 = CSolidSphere(pShaderWood , Vec3f(0,0,0) ,13);
     auto solidBox = CSolidBox(pShaderMarble , Vec3f(0,0,0) , 9);
     scene1.add(solidSphere2);
     scene2.add(solidBox);

    CTransform t;
	teapot.transform(t.scale(5.0f).get());
 	//teapot1.transform(t.scale(5.0f).get());
    scene.add(teapot);
    //scene1.add(teapot1);
    
    auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-15, 30, 40), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
    auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, -10));
    auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(20, 100, -10), Vec3f(0, 0, 0), 15.0f, 30.0f);
    scene.add(pCamera);
    scene1.add(pCamera);
    scene2.add(pCamera);
    if (false) scene.add(pLightPoint);
    else scene.add(pLightSpot);
    if (false) scene1.add(pLightPoint);
    else scene1.add(pLightSpot);
     if (false) scene2.add(pLightPoint);
    else scene2.add(pLightSpot);

    scene.buildAccelStructure(25, 5);
    scene1.buildAccelStructure(25,5);
    scene2.buildAccelStructure(25,5);

   int x = 312;
   x  = x & 2;
   std::cout << x << std::endl;
    
    Timer::start("Rendering...");
    Mat img = scene.render(std::make_shared<CSamplerStratified>(2, true, true));
    Mat img1 = scene1.render(std::make_shared<CSamplerStratified>(2, true, true));
    Mat img2 = scene2.render(std::make_shared<CSamplerStratified>(2, true, true));


    Timer::stop();
    imshow("image", img);
    imshow("image1", img1);
    imshow("image2", img2);
    waitKey();
    imwrite("out1.jpg", img);
    return 0;
}


