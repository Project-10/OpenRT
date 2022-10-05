#include "openrt.h"
#include "core/timer.h"

using namespace rt;

std::shared_ptr<CScene> buildSceneStripes(const Vec3f& bgColor, const Size resolution) {
	const float		intensity = 5000;
	auto pScene = std::make_shared<CScene>(bgColor);

	//textures
	//                                                     (2.0,  6, 0.24, 2.3, 2.5, 0.35 , true)
	auto pTextureStripes = std::make_shared<CTextureStripes>(5);

	//Shaders
	auto pShaderStripes = std::make_shared<CShaderPhong>(*pScene, pTextureStripes, 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderFloor = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);

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

std::shared_ptr<CScene> buildSceneRings(const Vec3f& bgColor, const Size resolution) {
	const float		intensity = 5000;
	auto pScene = std::make_shared<CScene>(bgColor);

	//textures
	auto pTextureRings = std::make_shared<CTextureRings>(1.5f);

	//Shaders
	auto pShaderRings = std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderFloor = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);

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

std::shared_ptr<CScene> buildSceneTemplates(const Vec3f& bgColor, const Size resolution) {

	const float intensity = 1e4;
	auto pScene = std::make_shared<CScene>(bgColor);

	// --- Materials ---
	// Rings shader
	auto pTextureRings = std::make_shared<CTextureRings>(24.0f);
	auto pShaderRings = std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 0.0f, 40.0f);

	// Wood shader
	CGradient gradientWood({ {0.0f, RGB(255, 205, 140)}, {0.1f, RGB(216, 139, 74)}, {0.4f, RGB(226, 147, 82)}, {0.6f, RGB(250, 180, 127)}, {1.0f, RGB(255, 205, 140)} });
	//CGradient gradientWood({{0.0f, RGB(255, 255, 255)}, {0.499f, RGB(255, 255, 255)}, {0.5f, RGB(255, 0, 0)}, {1.0f, RGB(255, 0, 0)}});
	auto pTextureWood = std::make_shared<CTextureWood>(gradientWood, 2022, 12.0f);
	auto pShaderWood = std::make_shared<CShaderPhong>(*pScene, pTextureWood, 0.1f, 0.9f, 0.0f, 40.0f);

	// Marble shader
	//CGradient gradientMarble(RGB(255, 255, 255), RGB(119, 135, 153));
	//auto pTextureMarble = std::make_shared<CTextureMarble>(gradientMarble, 0.5f, 6, 0.24f, 2.4f, 2.5f, 0.35f, false);
	//auto pShaderMarble = std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 0.0f, 40.0f);

	// other shaders
	auto pShaderFloor = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.5f, 0.5f, 0.0f, 40.0f);

	// Earth shader
	auto pTextureEarth = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pShaderEarth = std::make_shared<CShaderBlinn>(*pScene, pTextureEarth, 0.2f, 0.7f, 0.0f, 40.0f);


	// Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(0, -0.52f, 0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));

	//pScene->add(CSolidBox(pShaderWood, Vec3f(0, 0, 0), 2.5f, 1.0f, 12.0f));
	//pScene->add(CSolidBox(pShaderRings, Vec3f(-3, 0, 0), 2.5f, 1.0f, 12.0f));

	auto sphere1 = std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(-4, 1, 0), 1.5f);
	auto sphere2 = CSolidSphere(pShaderEarth, Vec3f(0, 1, 0), 1.5f);
	auto sphere3 = std::make_shared<CPrimSphere>(pShaderWood, Vec3f(4, 1, 0), 1.5f);

	// Transform
	CTransform T;
	Mat rotation = T.rotate(Vec3f(0, 1, 0), 15).get();

	sphere1->transform(rotation);
	sphere2.transform(rotation);
	sphere3->transform(rotation);

	//auto solidSphere = CSolidSphere(pShaderWood, Vec3f(0, 0.5f, 3), 2, 32);
	//auto primSphere = std::make_shared<CPrimSphere>(pShaderWood, Vec3f(3, 1, 0), 1.5f);
	//primSphere->transform(T.rotate(Vec3f(0, 1, 0), -90).scale(2).get());
	//
	//pScene->add(std::make_shared<CPrimSphere>(pShaderWood, Vec3f(0, 0, 0), 1.5f));
	pScene->add(sphere1);
	pScene->add(sphere2);
	pScene->add(sphere3);

	//Light
	if (true) {
		pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 50)));
		pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, -100, -50), false));
	}
	else pScene->add(std::make_shared<CLightSky>(Vec3f::all(1), 0.0f));


	//Cameras
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(1.5f, 6, 12), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 45.0f);
	pScene->add(pCamera);

	return pScene;
}

std::shared_ptr<CScene> buildSceneMarble(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);

	// Texture
	auto pTextureMarble = std::make_shared<CTexture>(dataPath + "marble-light.jpg");
	CGradient gradientMarble;
	auto pTextureMarble1 = std::make_shared<CTextureMarble>(gradientMarble);

	// Shader
	auto pShaderWhite	= std::make_shared<CShaderFlat>(RGB(255, 255, 255));
	auto pShaderFloor	= std::make_shared<CShaderBlinn>(*pScene, RGB(120, 120, 120), 0.1f, 0.9f, 0, 0);
	auto pShaderMarble	= std::make_shared<CShaderGeneral>(*pScene, pTextureMarble, 0.1f, 0.9f, 0, 0, 0.2f, 0, 1);
	auto pShaderMarble1	= std::make_shared<CShaderGeneral>(*pScene, pTextureMarble1, 0.1f, 0.9f, 0, 0, 0.2f, 0, 1);

	// Geometry
	pScene->add(std::make_shared<CPrimDisc>(pShaderWhite, Vec3f(0, 5.1f, 0), Vec3f(0, -1, 0), 1));
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(3.1f, 3, -2), Vec3f(-1, 0, 0), Vec3f(0, 0, -1), 0.45f));
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(3.1f, 3, -3), Vec3f(-1, 0, 0), Vec3f(0, 0, -1), 0.45f));
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(3.1f, 2, -2), Vec3f(-1, 0, 0), Vec3f(0, 0, -1), 0.45f));
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(3.1f, 2, -3), Vec3f(-1, 0, 0), Vec3f(0, 0, -1), 0.45f));
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0), 100));

	//pScene->add(CSolidSphere(pShaderMarble, Vec3f(0, 1.3f, 0), 1, 64));
	pScene->add(std::make_shared<CPrimSphere>(pShaderMarble1, Vec3f(0, 1.3f, 0), 1));

	// Light
	pScene->add(std::make_shared<CLightArea>(Vec3f::all(9), Vec3f(3, 3.5f, -1.5f), Vec3f(3, 3.5f, -3.5f), Vec3f(3, 1.5f, -3.5f), Vec3f(3, 1.5f, -1.5f), std::make_shared<CSamplerStratified>(4, true, true)));
	pScene->add(std::make_shared<CLightArea>(Vec3f::all(9), Vec3f(-1, 5, -1), Vec3f(1, 5, -1), Vec3f(1, 5, 1), Vec3f(-1, 5, 1), std::make_shared<CSamplerStratified>(4, true, true)));

	// Camera
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 1.5f, -3), Vec3f(0, 1.2f, 0), Vec3f(0, 1, 0), 60));

	return pScene;
}

int main()
{

	const Vec3f		bgColor = RGB(100, 100, 100);
	const Size		resolution = Size(800, 600);
	//	 auto pScene = buildSceneTemplates(bgColor, resolution);
		 //auto pSceneStripes = buildSceneStripes(bgColor, resolution);
	  //   auto pSceneRings = buildSceneRings(bgColor, resolution);

	pScene->buildAccelStructure(25, 3);
	Timer::start("Rendering...");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(2, true, true));
	Timer::stop();
	imshow("Marble Texture", img);
	imwrite("D:\\renders\\marble.jpg", img);
	waitKey();


	const float intensity = 1e4;
	auto pScene = std::make_shared<CScene>(bgColor);

	// --- Materials ---
	// Rings shader
	auto pSHaderWhite = std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pTextureRings = std::make_shared<CTextureRings>(24.0f);
	auto pShaderRings = std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 0.0f, 40.0f);

	// Wood shader
	CGradient gradientWood({ {0.0f, RGB(255, 205, 140)}, {0.1f, RGB(216, 139, 74)}, {0.4f, RGB(226, 147, 82)}, {0.6f, RGB(250, 180, 127)}, {1.0f, RGB(255, 205, 140)} });
	//CGradient gradientWood({{0.0f, RGB(255, 255, 255)}, {0.499f, RGB(255, 255, 255)}, {0.5f, RGB(255, 0, 0)}, {1.0f, RGB(255, 0, 0)}});
	auto pTextureWood1 = std::make_shared<CTextureWood>(gradientWood, 2021, 12.0f);
	auto pTextureWood2 = std::make_shared<CTextureWood>(gradientWood, 2022, 12.0f);
	auto pShaderWood1 = std::make_shared<CShaderPhong>(*pScene, pTextureWood1, 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderWood2 = std::make_shared<CShaderPhong>(*pScene, pTextureWood2, 0.1f, 0.9f, 0.0f, 40.0f);

	// Marble shader
	//CGradient gradientMarble(RGB(255, 255, 255), RGB(119, 135, 153));
	//auto pTextureMarble = std::make_shared<CTextureMarble>(gradientMarble, 0.5f, 6, 0.24f, 2.4f, 2.5f, 0.35f, false);
	//auto pShaderMarble = std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 0.0f, 40.0f);

	// other shaders
	auto pShaderFloor = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.5f, 0.5f, 0.0f, 40.0f);

	// Earth shader
	auto pTextureEarth = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pShaderEarth = std::make_shared<CShaderBlinn>(*pScene, pTextureEarth, 0.2f, 0.7f, 0.0f, 40.0f);



	//Cameras
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(1.5f, 6, 12), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 45.0f);
	pScene->add(pCamera);


	 // Geometries
	 //pScene->add(CSolidQuad(pShaderFloor, Vec3f(0, -0.52f, 0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));

	 //pScene->add(CSolidBox(pShaderWood, Vec3f(0, 0, 0), 2.5f, 1.0f, 12.0f));
	 //pScene->add(CSolidBox(pShaderRings, Vec3f(-3, 0, 0), 2.5f, 1.0f, 12.0f));

	 auto sphere1 = CSolid(std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(-4, 1, 0), 1.5f));
	 auto sphere2 = CSolidSphere(pShaderWood1, Vec3f(0, 1, 0), 1.5f, 64);
	 //auto sphere2 = CSolidTorus(pShaderWood, Vec3f(0, 1, 0), 1.5f, 1.0f, 24);
	 auto sphere3 = CSolid(std::make_shared<CPrimSphere>(pShaderWood2, Vec3f(4, 1, 0), 1.5f));

	 // Transform
	 CTransform T;
	 Mat rotation = T.rotate(Vec3f(0, 1, 0), 5).get();

	 //sphere1->transform(rotation);
	 //sphere2.transform(rotation);
	 //sphere3->transform(rotation);

	 //auto solidSphere = CSolidSphere(pShaderWood, Vec3f(0, 0.5f, 3), 2, 32);
	 //auto primSphere = std::make_shared<CPrimSphere>(pShaderWood, Vec3f(3, 1, 0), 1.5f);
	 //primSphere->transform(T.rotate(Vec3f(0, 1, 0), -90).scale(2).get());
	 //
	 //pScene->add(std::make_shared<CPrimSphere>(pShaderWood, Vec3f(0, 0, 0), 1.5f));
	 pScene->add(sphere1);
	 pScene->add(sphere2);
	 pScene->add(sphere3);

	 //Light
	 if (true) {
		 pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 50), false));
		 pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, -100, -50), false));
	 }
	 else pScene->add(std::make_shared<CLightSky>(Vec3f::all(1), 0.0f));



	//Mat imgStripes = pSceneStripes->render(std::make_shared<CSamplerStratified>(2, true, true));
	//imshow("Stripes Texture", imgStripes);


     //pSceneRings-> buildAccelStructure(20, 3);
     //pSceneWood-> buildAccelStructure(20, 3);
     
     
     
     //Mat imgStripes = pSceneStripes->render(std::make_shared<CSamplerStratified>(2, true, true));
	 //imshow("Stripes Texture", imgStripes);
	 
	 //Mat imgRings = pSceneRings->render(std::make_shared<CSamplerStratified>(2, true, true));
	 //imshow("Rings Texture", imgRings);
	 
	 for (;;) {
		 pScene->buildAccelStructure(20, 3);
		 Timer::start("Rendering...");
		 Mat img = pScene->render(std::make_shared<CSamplerStratified>(2, true, true));
		 Timer::stop();
		 imshow("Image", img);
		 char key = waitKey(1);
		 
		 sphere1.transform(rotation);
		 sphere2.transform(rotation);
		 sphere3.transform(rotation);
		 
		 if (key == 27) break;
	 }
     return 0;
}
