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

std::shared_ptr<CScene> buildSceneMoon(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);

	Mat diff = imread(dataPath + "lroc_color_poles.tif");
	Mat bump = imread(dataPath + "ldem_64.tif");

	resize(diff, diff, Size(4000, 2000), 0, 0, INTER_AREA);
	resize(bump, bump, Size(1400, 700), 0, 0, INTER_AREA);
	
	auto pShader = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1, 0, 0);
	pShader->setDiffuseColor(std::make_shared<CTexture>(diff));
	pShader->setBumpMap(std::make_shared<CTexture>(bump), 0.05f);
	//pShader->setBumpMap(std::make_shared<CTexture>(dataPath + "golfball.jpg"));

	auto moon = CSolidSphere(pShader, Vec3f(0, 0, 0), 1.7374f, 24);
	//CTransform t;
	//moon.transform(t.rotate(Vec3f(0, 1, 0), 90).get());
	
	//pScene->add(std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 1.7374f));
	pScene->add(moon);
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(2e16), Vec3f(-150e6 * cosf(Pif*60/180), 0, -150e6 * sinf(Pif * 60 / 180)), false));
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-384.4f, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0.8f));

	return pScene;
}

// --- Test Gradient ---
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
//
//imshow("img", m);
//waitKey();
//return 0;

// --- The Moon ---
//const Vec3f		bgColor = RGB(0, 0, 0);
//const Size		resolution = Size(1280, 720);
//
//auto pScene = std::make_shared<CScene>(bgColor);
//
//auto pShader = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1, 0, 160);
//Mat diff = imread(dataPath + "lroc_color_poles.tif");
//Mat bump = imread(dataPath + "ldem_64.tif");
//
//resize(diff, diff, Size(4000, 2000), 0, 0, INTER_AREA);
//resize(bump, bump, Size(1400, 700), 0, 0, INTER_AREA);
//
//pShader->setDiffuseColor(std::make_shared<CTexture>(diff));
//pShader->setDiffuseColor(std::make_shared<CTexture>(dataPath + "golfball.jpg"));
//pShader->setDiffuseColor(std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg"));
//pShader->setBumpMap(std::make_shared<CTexture>(bump));
//pShader->setBumpMap(std::make_shared<CTexture>(dataPath + "golfball.jpg"));
//pShader->setBumpMap(std::make_shared<CTexture>(dataPath + "ldem_64.tif"));
//
//auto sphere = std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 1.7374f);
//auto sphere = std::make_shared<CPrimDisc>(pShader, Vec3f(0, 0, 0), Vec3f(-1, 0, 0), 1.7374f);
//pScene->add(sphere);
//
//auto sun = std::make_shared<CLightOmni>(Vec3f::all(20e15), Vec3f(-150e6 * cosf(Pif * 60 / 180), 0, -150e6 * sinf(Pif * 60 / 180)), true);
//pScene->add(sun);
//
//pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-384.4f, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0.8f));


int main()
{
	const Vec3f		bgColor = RGB(0, 0, 0);
	const Size		resolution = Size(1280, 720);
	//auto pScene = buildSceneTemplates(bgColor, resolution);
	//auto pSceneStripes = buildSceneStripes(bgColor, resolution);
	//auto pSceneRings = buildSceneRings(bgColor, resolution);
	auto pScene = buildSceneMoon(bgColor, resolution);
	pScene->buildAccelStructure(20, 1);

	//auto pScene = std::make_shared<CScene>(bgColor);

	//auto pShader = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1, 0, 160);
	////pShader->setDiffuseColor(std::make_shared<CTexture>(dataPath + "golfball.jpg"));
	////pShader->setDiffuseColor(std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg"));
	////Mat diff = imread(dataPath + "lroc_color_poles.tif");
	////Mat diff = imread(dataPath + "lroc_color_poles.tif");
	////Mat diff = imread(dataPath + "A.png");
	////Mat bump = imread(dataPath + "ldem_64.tif");
	//
	////resize(diff, diff, Size(100, 100), 0, 0, INTER_NEAREST);
	////resize(bump, bump, Size(1400, 700), 0, 0, INTER_AREA);

	////pShader->setDiffuseColor(std::make_shared<CTexture>(diff));
	////pShader->setDiffuseColor(std::make_shared<CTexture>(dataPath + "A.png"));
	////pShader->setBumpMap(std::make_shared<CTexture>(bump));
	//
	//pShader->setBumpMap(std::make_shared<CTexture>(dataPath + "A.png"), 0.5f);
	////pShader->setBumpMap(std::make_shared<CTexture>(dataPath + "ldem_64.tif"));

	//pScene->add(std::make_shared<CPrimPlane>(pShader, Vec3f(0, 0, 0), Vec3f(0, 1, 0)));
	////auto sphere = std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 1.7374f);
	//auto sphere = std::make_shared<CPrimDisc>(pShader, Vec3f(0, 1.0f, 0), Vec3f(-1, 0, 0), 1.0f);
	//pScene->add(sphere);


	//pScene->add(std::make_shared<CLightOmni>(Vec3f(1e1, 0, 0), Vec3f(5, 5, 0), true));
	//pScene->add(std::make_shared<CLightOmni>(Vec3f::all(3e1), Vec3f(-5, 5, 0), true));
	//pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-5, 4, -5), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 30.0f));

	//CTransform T;
	//Mat t = T.rotate(Vec3f(0, 1, 0), 3.0f).get();

	
	//float alpha = -90;
	//VideoWriter videoWriter;
	//auto codec = VideoWriter::fourcc('M', 'J', 'P', 'G');		// Native windows codec
	//videoWriter.open("D:\\Renders\\moon.avi", codec, 60, resolution);
	//if (!videoWriter.isOpened()) printf("ERROR: Can't open vide file for writing\n");
	for (; ; ) {
		//sun->setOrigin(Vec3f(-150e6 * cosf(Pif * alpha / 180), 0, -150e6 * sinf(Pif * alpha / 180)));
		//alpha += 1.0f;

		Timer::start("Rendering...");
		Mat img = pScene->render(std::make_shared<CSamplerStratified>(4, false, false));
		Timer::stop();
		//sphere->transform(t);
		//videoWriter << img;
		imshow("Image", img);
		//imwrite("D:\\renders\\moon.png", img);
		char key = waitKey(1);
		if (key == 27) break;
	}
    return 0;
}
