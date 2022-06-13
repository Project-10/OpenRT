#include "openrt.h"
#include "core/timer.h"

using namespace rt;

std::shared_ptr<CScene> buildSceneStripes(const Vec3f&bgColor, const Size resolution) {
     
     const float		intensity = 5000;
     auto pScene  = std::make_shared<CScene>(bgColor);
     
     //textures
	auto pTextureStripes = std::make_shared<CTextureStripes>(5);
     
     //Shaders
     auto pShaderStripes	= std::make_shared<CShaderPhong>(*pScene, pTextureStripes, 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderFloor	= std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
 
     //Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
	CSolid teapot(pShaderStripes, dataPath + "teapot.obj");

     //Transformation
     CTransform t;
	teapot.transform(t.scale(5.0f).get());
     pScene->add(teapot);
     
     //Light
     auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, -10));
     auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(20, 100, -10), Vec3f(0, 0, 0), 15.0f, 30.0f);
     if (false) pScene->add(pLightPoint);
     else pScene->add(pLightSpot);
     
     
     //Cameras
    auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-15, 30, 40), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
    pScene->add(pCamera);
    
    return pScene;
}


std::shared_ptr<CScene> buildSceneRings(const Vec3f&bgColor, const Size resolution) {
     
     const float		intensity = 5000;
     auto pScene  = std::make_shared<CScene>(bgColor);
     
     //textures
	auto pTextureRings = std::make_shared<CTextureRings>(1.5f);
     
     //Shaders
     auto pShaderRings	= std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderFloor	= std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
 
     //Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
	CSolid teapot(pShaderRings, dataPath + "teapot.obj");

     //Transformation
     CTransform t;
	teapot.transform(t.scale(5.0f).get());
     pScene->add(teapot);
     
     //Light
     auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, -10));
     auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(20, 100, -10), Vec3f(0, 0, 0), 15.0f, 30.0f);
     if (false) pScene->add(pLightPoint);
     else pScene->add(pLightSpot);
     
     
     //Cameras
    auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-15, 30, 40), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
    pScene->add(pCamera);
    
    return pScene;
}

std::shared_ptr<CScene> buildSceneWood(const Vec3f&bgColor, const Size resolution) {
     
     const float		intensity = 5000;
     auto pScene  = std::make_shared<CScene>(bgColor);
     
     //textures
	auto pTextureWood = std::make_shared<CTextureWood>(1.5f);
     
     //Shaders
     auto pShaderWood	= std::make_shared<CShaderPhong>(*pScene, pTextureWood, 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderFloor	= std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
 
     //Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(0,-10,0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
     auto solidSphere = CSolidSphere(pShaderWood , Vec3f(0,0,0) ,13);
     pScene->add(solidSphere);
     
     //Light
     auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, -10));
     auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(20, 100, -10), Vec3f(0, 0, 0), 15.0f, 30.0f);
     if (false) pScene->add(pLightPoint);
     else pScene->add(pLightSpot);
     
     
     //Cameras
    auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-15, 30, 40), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
    pScene->add(pCamera);
    
    return pScene;
}


std::shared_ptr<CScene> buildSceneMarble(const Vec3f&bgColor, const Size resolution) {
     
     const float		intensity = 5000;
     auto pScene  = std::make_shared<CScene>(bgColor);
     
     //textures
	auto pTextureMarble = std::make_shared<CTextureMarble>(1.0f);
     
     //Shaders
     auto pShaderMarble	= std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderFloor	= std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
 
     //Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(0,-10,0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
     auto solidBox = CSolidBox(pShaderMarble , Vec3f(0,0,0) ,9);
     pScene->add(solidBox);
     
     //Light
     auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, -10));
     auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(20, 100, -10), Vec3f(0, 0, 0), 15.0f, 30.0f);
     if (false) pScene->add(pLightPoint);
     else pScene->add(pLightSpot);
     
     
     //Cameras
    auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-15, 30, 40), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
    pScene->add(pCamera);
    
    return pScene;
}


int main() {

     const Vec3f		bgColor = RGB(0.1f, 0.1f, 0.1f);
    const Size		     resolution = Size(800, 600);
    
     auto pSceneStripes = buildSceneStripes(bgColor, resolution);
     auto pSceneRings = buildSceneRings(bgColor, resolution);
     auto pSceneWood = buildSceneWood(bgColor, resolution);
     auto pSceneMarble = buildSceneMarble(bgColor, resolution);
     
     pSceneStripes->buildAccelStructure(25,5);
     pSceneRings-> buildAccelStructure(25,5);
     pSceneWood-> buildAccelStructure(25,5);
     pSceneMarble-> buildAccelStructure(25,5);

     
     Timer::start("Rendering...");
     Mat imgStripes = pSceneStripes->render(std::make_shared<CSamplerStratified>(2, true, true));
     Mat imgRings = pSceneRings->render(std::make_shared<CSamplerStratified>(2, true, true));
     Mat imgWood = pSceneWood->render(std::make_shared<CSamplerStratified>(2, true, true));
     Mat imgMarble = pSceneMarble->render(std::make_shared<CSamplerStratified>(2, true, true));


     Timer::stop();
     imshow("Stripes Texture", imgStripes);
     imshow("Rings Texture", imgRings);
     imshow("Wood Texture", imgWood);
     imshow("Marble Texture", imgMarble);
     waitKey();
     return 0;
}
