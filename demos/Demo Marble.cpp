#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {

    const Vec3f		bgColor = RGB(0.1f, 0.1f, 0.1f);
    const Size		resolution = Size(800, 600);
    const float		intensity = 5000;

     CScene scene(bgColor);
     CScene scene1(bgColor);

     //For another "weird" type of marble, please change the boolean value to true
     auto pTextureMarble = std::make_shared<CTextureMarble>(2.0f, 6, 0.08, 2.0, 2.0, 0.6, true);
     auto  pShaderMarble = std::make_shared<CShaderPhong>(scene1, pTextureMarble, 0.1f, 0.9f, 0.0f, 1000.0f);
     auto pTextureMarble1 = std::make_shared<CTextureMarble>();
     auto  pShaderMarble1 = std::make_shared<CShaderPhong>(scene, pTextureMarble1, 0.1f, 0.9f, 0.0f, 1000.0f);
     auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
     auto pShaderFloor1	= std::make_shared<CShaderPhong>(scene1, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);

     
   //Object
     auto solidBox = CSolidBox(pShaderMarble , Vec3f(0,-2,0) ,8);
     auto solidSphere = CSolidSphere(pShaderMarble1 , Vec3f(0,-2,0) ,13);
     scene.add(CSolidQuad(pShaderFloor, Vec3f(0,-10,-0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
     scene.add(solidSphere);
     scene1.add(CSolidQuad(pShaderFloor1, Vec3f(0,-10,-0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
     scene1.add(solidBox);

     
   
    auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-15, 30, 40), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
    auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 30));
    auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(0, 100, 30), Vec3f(0, 0, 0), 15.0f, 30.0f);
    scene.add(pCamera);
    scene1.add(pCamera);
     if (false) scene.add(pLightPoint);
    else scene.add(pLightSpot);
     if (false) scene1.add(pLightPoint);
    else scene1.add(pLightSpot);
    

     scene.buildAccelStructure(25, 5);
     scene1.buildAccelStructure(25,5);

   //Rendering
     Timer::start("Rendering...");
    Mat img = scene.render(std::make_shared<CSamplerStratified>(2, true, true));
    Timer::stop();
     Timer::start("Rendering...");
    Mat img1 = scene1.render(std::make_shared<CSamplerStratified>(2, true, true));
    Timer::stop();
    imshow("image", img);
    imshow("image1", img1);

    waitKey();
    return 0;
    
    }
