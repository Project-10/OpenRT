#include "openrt.h"
#include "core/timer.h"

using namespace rt;

std::shared_ptr<CScene> buildSceneStripes(const Vec3f& bgColor, const Size resolution) {
	
	auto pScene = std::make_shared<CScene>(bgColor);

	// Gradient for texture
	CGradient gradient({{0.0f, RGB(255, 255, 255)}, {0.5f, RGB(255, 255, 255)}, {0.501f, RGB(255, 0, 0)}, {1.0f, RGB(255, 0, 0)}});
	CGradient gradientMarble(RGB(166, 208, 229), RGB(175, 152, 123));
	gradientMarble.addColor(0.37f, RGB(128, 182, 222));
	gradientMarble.addColor(0.54f, RGB(90, 175, 213));
	gradientMarble.addColor(0.66f, RGB(103, 152, 176));
	gradientMarble.addColor(0.75f, RGB(28, 163, 215));
	gradientMarble.addColor(0.84f, RGB(19, 140, 183));
	gradientMarble.addColor(0.92f, RGB(55, 118, 149));

	auto pNoise = std::make_shared<CPerlinNoise>(2022, 3.0f, 0.04f, 10, 0.5f, 2.0f);
	
	// Textures
	auto pTextureStripes = std::make_shared<CTextureStripes>(gradient, 1, pNoise);
	auto pTextureRings	 = std::make_shared<CTextureRings>(gradient, 1);
	auto pTextureMarble	 = std::make_shared<CTextureMarble>(gradientMarble, 1, pNoise);
	auto pTexture		 = std::make_shared<CTexture>(dataPath + "b13.jpg");

	// Shaders
	auto pShaderFloor	= std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderStripes = std::make_shared<CShaderPhong>(*pScene, pTextureStripes, 0.1f, 0.9f, 4.0f, 320.0f);
	auto pShaderRings	= std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 2.0f, 320.0f);
	auto pShaderMarble	= std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 2.0f, 320.0f);
	auto pShader = std::make_shared<CShaderPhong>(*pScene, pTexture, 0.1f, 0.9f, 2.0f, 320.0f);
	
	// Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
	//pScene->add(CSolidBox(pShaderRings, Vec3f(0, 5, 0), 5));
	pScene->add(CSolidSphere(pShaderMarble, Vec3f(0, 5, 0), 5, 64));
	//pScene->add(std::make_shared<CPrimDisc>(pShader, Vec3f(0, 5, 0), normalize(Vec3f(0, 1, 0.7f)), 7.5f, 2.5f));
	//CSolid teapot(pShaderMarble, dataPath + "Stanford Dragon.obj");

	// Transformation
	CTransform t;
	//teapot.transform(t.scale(1.5f).get());
	//pScene->add(teapot);

	// Light
	const float	intensity = 5e3;
	const float radius = 66;
	const float alpha = 6;
	if (false) {
		pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, -10)));
	} else {
		pScene->add(std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(radius, 100, 0), Vec3f(0, 0, 0), alpha, 2 * alpha));
		pScene->add(std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(-radius/2, 100, sqrtf(3) * radius/2), Vec3f(0, 0, 0), alpha, 2 * alpha));
		pScene->add(std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(-radius/2, 100, -sqrtf(3) * radius/2), Vec3f(0, 0, 0), alpha, 2 * alpha));
	}


	// Cameras
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 33, 50), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 30.0f));

	return pScene;
}

std::shared_ptr<CScene> buildSceneTemplates(const Vec3f& bgColor, const Size resolution) {
	const float intensity = 1e4;
	auto pScene = std::make_shared<CScene>(bgColor);

	// Wood shader
	CGradient gradientWood({ {0.0f, RGB(255, 205, 140)}, {0.1f, RGB(216, 139, 74)}, {0.4f, RGB(226, 147, 82)}, {0.6f, RGB(250, 180, 127)}, {1.0f, RGB(255, 205, 140)} });
	//CGradient gradientWood({{0.0f, RGB(255, 255, 255)}, {0.499f, RGB(255, 255, 255)}, {0.5f, RGB(255, 0, 0)}, {1.0f, RGB(255, 0, 0)}});
	auto pNoise			= std::make_shared<CPerlinNoise>(2022, 2.5f, 1.5f, 2, 0.5f, 2.0f);
	auto pTextureWood	= std::make_shared<CTextureRings>(gradientWood, 12.0f, pNoise);
	auto pShaderWood	= std::make_shared<CShaderPhong>(*pScene, pTextureWood, 0.1f, 0.9f, 0.0f, 40.0f);

	// Marble shader
	//CGradient gradientMarble(RGB(255, 255, 255), RGB(119, 135, 153));
	//auto pTextureMarble = std::make_shared<CTextureMarble>(gradientMarble, 0.5f, 6, 0.24f, 2.4f, 2.5f, 0.35f, false);
	//auto pShaderMarble = std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 0.0f, 40.0f);

	// other shaders
	auto pShaderFloor = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), .0f, 1.0f, 0.0f, 40.0f);
	auto pShader = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1, 0, 40);
	pShader->setOpacity(1.0f);

	// Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(0, -0.52f, 0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
	pScene->add(CSolidBox(pShaderWood, Vec3f(0, 0, 0), 2.5f, 1.0f, 12.0f));
	//pScene->add(CSolidBox(pShaderRings, Vec3f(-3, 0, 0), 2.5f, 1.0f, 12.0f));


	//auto solidSphere = CSolidSphere(pShader, Vec3f(0, 0.5f, 3), 2, 32);
	//auto primSphere = std::make_shared<CPrimSphere>(pShader, Vec3f(3, 1, 0), 1.5f);

	//	pScene->add(std::make_shared<CPrimSphere>(pShaderWood, Vec3f(0, 0, 0), 1.5f));
	pScene->add(std::make_shared<CPrimSphere>(pShaderWood, Vec3f(4, 1, 0), 1.5f));

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

std::shared_ptr<CScene> buildSceneMoon(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);

	Mat diff = imread(dataPath + "lroc_color_poles_4k.tif");
	Mat bump = imread(dataPath + "ldem_16_uint.tif");

	//resize(diff, diff, Size(4000, 2000), 0, 0, INTER_AREA);
	//resize(bump, bump, Size(1400, 700), 0, 0, INTER_AREA);
	
	auto pShader = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1, 0, 0);
	pShader->setDiffuseColor(std::make_shared<CTexture>(diff));
	pShader->setBumpMap(std::make_shared<CTexture>(bump), 1.5f);
	//pShader->setBumpMap(std::make_shared<CTexture>(dataPath + "golfball.jpg"));

	auto moon = CSolidSphere(pShader, Vec3f(0, 0, 0), 1.7374f, 16);
	//CTransform t;
	//moon.transform(t.rotate(Vec3f(0, 1, 0), 90).get());
	
	//pScene->add(std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 1.7374f));
	pScene->add(moon);
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(2e16), Vec3f(-150e6 * cosf(Pif*60/180), 0, -150e6 * sinf(Pif * 60 / 180)), true));
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


std::shared_ptr<CScene> buildSceneMarble(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);

	// Texture
	// auto pTextureMarble = std::make_shared<CTexture>(dataPath + "marble-light.jpg");
	CGradient gradientRedWhite({ {0.0f, RGB(255, 255, 255)}, {1.0f, RGB(255, 0, 0)} });
	CGradient gradientMarble(RGB(166, 208, 229), RGB(175, 152, 123));
	gradientMarble.addColor(0.37f, RGB(128, 182, 222));
	gradientMarble.addColor(0.54f, RGB(90, 175, 213));
	gradientMarble.addColor(0.66f, RGB(103, 152, 176));
	gradientMarble.addColor(0.75f, RGB(28, 163, 215));
	gradientMarble.addColor(0.84f, RGB(19, 140, 183));
	gradientMarble.addColor(0.92f, RGB(55, 118, 149));
	auto noiseMarble = std::make_shared<CPerlinNoise>(2022, 3.0f, 0.2f, 10, 0.5f, 2.0f);
	auto pTextureMarble1 = std::make_shared<CTextureMarble>(gradientMarble, 0, noiseMarble);

//	auto pTextureMarble1 = std::make_shared<CTextureMarble>(gradientRedWhite, 2022, 0, 3.0f, 0.2f, 10, 0.5f, 2.0f);


	// Shader
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderFloor	= std::make_shared<CShaderBlinn>(*pScene, RGB(120, 120, 120), 0.1f, 0.9f, 0, 0);
	//auto pShaderMarble	= std::make_shared<CShaderGeneral>(*pScene, pTextureMarble, 0.1f, 0.9f, 0, 0, 0.2f, 0, 1);
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

std::shared_ptr<CScene> buildSceneSaturn(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);

	Mat saturn_diff = imread(dataPath + "1_saturn_8k.jpg");
	auto pShaderSaturn = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1, 0, 0);
	pShaderSaturn->setDiffuseColor(std::make_shared<CTexture>(saturn_diff));

	auto pTextureDiff		= std::make_shared<CTexture>(dataPath + "8k_saturn_ring.png");
	auto pTextureOpacity	= std::make_shared<CTexture>(dataPath + "8k_saturn_ring_alpha.png");
	auto pSahderRings		= std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1.5f, 0, 0);
	pSahderRings->setDiffuseColor(pTextureDiff);
	pSahderRings->setOpacity(pTextureOpacity);

	auto saturn = std::make_shared<CPrimSphere>(pShaderSaturn, Vec3f(0, 0, 0), 60.33f);
	auto rings = std::make_shared<CPrimDisc>(pSahderRings, Vec3f(0, 0, 0), Vec3f(0, 1, 0), 142.0f, 72.0f);
	CTransform t;
	Mat T = t.rotate(Vec3f(1, 0, 0), 28.f).get();
	saturn->transform(T);
	rings->transform(T);

	//pScene->add(std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 1.7374f));
	pScene->add(saturn);
	pScene->add(rings);
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(2e18), Vec3f(0, 0, 1430e6), true));
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-1000.0f, 300, 670), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 9.0f));

	return pScene;
}

int main()
{
	const Vec3f		bgColor = RGB(0, 0, 0);
	const Size		resolution = Size(1920, 1080);
	
	//auto pScene = buildSceneStripes(bgColor, resolution);
	//auto pScene = buildSceneTemplates(bgColor, resolution);
	//auto pScene = buildSceneMarble(bgColor, resolution);
	//auto pScene = buildSceneSaturn(bgColor, resolution);
	//auto pScene = buildSceneMoon(bgColor, resolution);
	//pScene->buildAccelStructure(20, 3);
	//Timer::start("Rendering...");
	//Mat img = pScene->render(std::make_shared<CSamplerStratified>(2, true, true));
	//Timer::stop();
	//imshow("Image", img);
	////imwrite("D:\\renders\\Saturn.jpg", img);
	//char key = waitKey();

	auto pScene = std::make_shared<CScene>(bgColor);

	Mat diff = imread(dataPath + "lroc_color_poles_4k.tif");
	Mat bump = imread(dataPath + "ldem_16_uint.tif");

	//resize(diff, diff, Size(4000, 2000), 0, 0, INTER_AREA);
	//resize(bump, bump, Size(1400, 700), 0, 0, INTER_AREA);

	auto pShader = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1, 0, 0);
	pShader->setDiffuseColor(std::make_shared<CTexture>(diff));
	pShader->setBumpMap(std::make_shared<CTexture>(bump), 1.0f);
	//pShader->setBumpMap(std::make_shared<CTexture>(dataPath + "golfball.jpg"));

	auto moon = CSolidSphere(pShader, Vec3f(0, 0, 0), 1.7374f, 64);
	//auto moon = std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 1.7374f);
	CTransform t;
	auto T = t.rotate(Vec3f(0, 1, 0), 0.25f).get();
	//moon.transform(t.rotate(Vec3f(0, 1, 0), 90).get());
	auto pLight = std::make_shared<CLightOmni>(Vec3f::all(2e16), Vec3f(-150e6 * cosf(Pif * 60 / 180), 0, -150e6 * sinf(Pif * 60 / 180)), true);

	//pScene->add(std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 1.7374f));
	pScene->add(moon);
	pScene->add(pLight);
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-384.4f, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0.8f));
	pScene->buildAccelStructure(20, 3);

	VideoWriter videoWriter;
	auto codec = VideoWriter::fourcc('M', 'J', 'P', 'G');		// Native windows codec
	//auto codec = VideoWriter::fourcc('H', '2', '6', '4');		// Try it on MacOS
	videoWriter.open("D:\\Renders\\moon.avi", codec, 30, resolution);
	if (!videoWriter.isOpened()) printf("ERROR: Can't open vide file for writing\n");

	for (int i = 30; i < 330; i+= 1) {
		pLight->setOrigin(Vec3f(150e6 * cosf(Pif * i / 180), 150e6 * sinf(Pif * i / 180), 0));
		Timer::start("Rendering...");
		Mat img = pScene->render(std::make_shared<CSamplerStratified>(4, false, true));
		Timer::stop();
		videoWriter << img;
		imshow("Image", img);
		
		//moon.transform(T);
		//-imwrite("D:\\renders\\procedural marble.png", img);
		char key = waitKey(1);
		if (key == 27) break;
	}
	return 0;
}
