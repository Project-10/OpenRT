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
	auto pTextureWood = std::make_shared<CTextureWood>(gradientWood, 12.0f);
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

int main()
{
	//Mat m(100, 600, CV_32FC3);
	//CGradient g(RGB(0, 0, 0), RGB(255, 255, 255));
	//g.addColor(0.5f, RGB(255, 0, 0));
	//g.addColor(0.75f, RGB(255, 255, 0));
	//
	//for (int y = 0; y < m.rows; y++) {
	//	Vec3f *pm = m.ptr<Vec3f>(y);
	//	for (int x = 0; x < m.cols; x++) {
	//		float val = static_cast<float>(x) / (m.cols - 1);
	//		pm[x] =  g.getColor(val);
	//	}
	//}
	//m.convertTo(m, CV_8UC3, 255);

	//imshow("img", m);
	//waitKey();
	//return 0;


	const Vec3f		bgColor = RGB(0.1f, 0.1f, 0.1f);
	const Size		     resolution = Size(800, 600);
	//	 auto pScene = buildSceneTemplates(bgColor, resolution);
		 //auto pSceneStripes = buildSceneStripes(bgColor, resolution);
	  //   auto pSceneRings = buildSceneRings(bgColor, resolution);


	const float intensity = 1e4;
	auto pScene = std::make_shared<CScene>(bgColor);

	// --- Materials ---
	// Rings shader
	auto pTextureRings = std::make_shared<CTextureRings>(24.0f);
	auto pShaderRings = std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 0.0f, 40.0f);

	// Wood shader
	CGradient gradientWood({ {0.0f, RGB(255, 205, 140)}, {0.1f, RGB(216, 139, 74)}, {0.4f, RGB(226, 147, 82)}, {0.6f, RGB(250, 180, 127)}, {1.0f, RGB(255, 205, 140)} });
	//CGradient gradientWood({{0.0f, RGB(255, 255, 255)}, {0.499f, RGB(255, 255, 255)}, {0.5f, RGB(255, 0, 0)}, {1.0f, RGB(255, 0, 0)}});
	auto pTextureWood = std::make_shared<CTextureWood>(gradientWood, 12.0f);
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
	auto sphere2 = CSolidSphere(pShaderWood, Vec3f(0, 1, 0), 1.5f);
	sphere2.setPivot(Vec3f(0, 1, 0));
	auto sphere3 = std::make_shared<CPrimSphere>(pShaderWood, Vec3f(4, 1, 0), 1.5f);

	// Transform
	CTransform T;
	Mat rotation = T.rotate(Vec3f(0, 1, 0), 1).get();

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
		pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 50)));
		pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, -100, -50), false));
	}
	else pScene->add(std::make_shared<CLightSky>(Vec3f::all(1), 0.0f));


	//Cameras
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(1.5f, 6, 12), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 45.0f);
	pScene->add(pCamera);


	//pScene->buildAccelStructure(20, 3);
	//pSceneRings-> buildAccelStructure(20, 3);
	//pSceneWood-> buildAccelStructure(20, 3);



	//Mat imgStripes = pSceneStripes->render(std::make_shared<CSamplerStratified>(2, true, true));
	//imshow("Stripes Texture", imgStripes);

	//Mat imgRings = pSceneRings->render(std::make_shared<CSamplerStratified>(2, true, true));
	//imshow("Rings Texture", imgRings);

	for (;;) {
		pScene->buildAccelStructure(20, 3);
		//		 Timer::start("Rendering...");
		Mat img = pScene->render(std::make_shared<CSamplerStratified>(2, true, true));
		//		 Timer::stop();
		imshow("Marble Texture", img);
		char key = waitKey(1);

		sphere1->transform(rotation);
		sphere2.transform(rotation);
		sphere3->transform(rotation);
		if (key == 27) break;
	}
	return 0;
}