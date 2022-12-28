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
	
	// Textures
	auto pTextureStripes = std::make_shared<CTextureStripes>(gradient, 1);
	auto pTextureRings	 = std::make_shared<CTextureRings>(gradient, 1);
	auto pTextureMarble	 = std::make_shared<CTextureMarble>(gradientMarble, 2022, 0, 3.0f, 0.02f, 10, 0.5f, 2.0f);
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
	//pScene->add(CSolidSphere(pShaderStripes, Vec3f(0, 5, 0), 5, 64));
	pScene->add(std::make_shared<CPrimDisc>(pShader, Vec3f(0, 5, 0), normalize(Vec3f(0, 1, 0.7f)), 7.5f, 2.5f));
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

	// --- Materials ---
	// Rings shader
	//auto pTextureRings = std::make_shared<CTextureRings>(24.0f);
	//auto pShaderRings = std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 0.0f, 40.0f);

	// Wood shader
	CGradient gradientWood({ {0.0f, RGB(255, 205, 140)}, {0.1f, RGB(216, 139, 74)}, {0.4f, RGB(226, 147, 82)}, {0.6f, RGB(250, 180, 127)}, {1.0f, RGB(255, 205, 140)} });
	//CGradient gradientWood({{0.0f, RGB(255, 255, 255)}, {0.499f, RGB(255, 255, 255)}, {0.5f, RGB(255, 0, 0)}, {1.0f, RGB(255, 0, 0)}});
	auto pTextureWood = std::make_shared<CTextureWood>(gradientWood, 2022, 12.0f, 2.5f, 1.5f);
	auto pShaderWood = std::make_shared<CShaderPhong>(*pScene, pTextureWood, 0.1f, 0.9f, 0.0f, 40.0f);

	// Marble shader
	//CGradient gradientMarble(RGB(255, 255, 255), RGB(119, 135, 153));
	//auto pTextureMarble = std::make_shared<CTextureMarble>(gradientMarble, 0.5f, 6, 0.24f, 2.4f, 2.5f, 0.35f, false);
	//auto pShaderMarble = std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 0.0f, 40.0f);

	// other shaders
	auto pShaderFloor = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.5f, 0.5f, 0.0f, 40.0f);


	// Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(0, -0.52f, 0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));

	pScene->add(CSolidBox(pShaderWood, Vec3f(0, 0, 0), 2.5f, 1.0f, 12.0f));
	//pScene->add(CSolidBox(pShaderRings, Vec3f(-3, 0, 0), 2.5f, 1.0f, 12.0f));


	auto solidSphere = CSolidSphere(pShaderWood, Vec3f(0, 0.5f, 3), 2, 32);
	auto primSphere = std::make_shared<CPrimSphere>(pShaderWood, Vec3f(3, 1, 0), 1.5f);

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


std::shared_ptr<CScene> buildSceneMarble(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);

	// Texture
	// auto pTextureMarble = std::make_shared<CTexture>(dataPath + "marble-light.jpg");
	CGradient gradientMarble(RGB(166, 208, 229), RGB(175, 152, 123));
	gradientMarble.addColor(0.37f, RGB(128, 182, 222));
	gradientMarble.addColor(0.54f, RGB(90, 175, 213));
	gradientMarble.addColor(0.66f, RGB(103, 152, 176));
	gradientMarble.addColor(0.75f, RGB(28, 163, 215));
	gradientMarble.addColor(0.84f, RGB(19, 140, 183));
	gradientMarble.addColor(0.92f, RGB(55, 118, 149));
	auto pTextureMarble1 = std::make_shared<CTextureMarble>(gradientMarble, 2021, 0, 1.5f, 0.2f, 10, 0.5f, 2.0f);
	CGradient gradientRedWhite({{0.0f, RGB(255, 255, 255)}, {1.0f, RGB(255, 0, 0)} });
	// auto pTextureMarble1 = std::make_shared<CTextureMarble>(gradientRedWhite, 2022, 0, 3.0f, 0.2f, 10, 0.5f, 2.0f);


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


int main()
{
	const Vec3f		bgColor = RGB(12, 12, 12);
	const Size		resolution = Size(800, 600);
	
	//auto pScene = buildSceneStripes(bgColor, resolution);
	// auto pScene = buildSceneTemplates(bgColor, resolution);
	//auto pScene = buildSceneMarble(bgColor, resolution);


	auto pScene = std::make_shared<CScene>(bgColor);

	// Gradient for texture
	CGradient gradient({ {0.0f, RGB(255, 255, 255)}, {0.5f, RGB(255, 255, 255)}, {0.501f, RGB(255, 0, 0)}, {1.0f, RGB(255, 0, 0)} });
	CGradient gradientMarble(RGB(166, 208, 229), RGB(175, 152, 123));
	gradientMarble.addColor(0.37f, RGB(128, 182, 222));
	gradientMarble.addColor(0.54f, RGB(90, 175, 213));
	gradientMarble.addColor(0.66f, RGB(103, 152, 176));
	gradientMarble.addColor(0.75f, RGB(28, 163, 215));
	gradientMarble.addColor(0.84f, RGB(19, 140, 183));
	gradientMarble.addColor(0.92f, RGB(55, 118, 149));

	// Textures
	auto pTextureStripes	= std::make_shared<CTextureStripes>(gradient, 1);
	auto pTextureRings		= std::make_shared<CTextureRings>(gradient, 1);
	auto pTextureMarble		= std::make_shared<CTextureMarble>(gradientMarble, 2022, 0, 3.0f, 0.02f, 10, 0.5f, 2.0f);
	auto pTexture			= std::make_shared<CTexture>(dataPath + "b13.jpg");
	auto pTextureBump		= std::make_shared<CTexture>(dataPath + "b13.jpg");

	// Shaders
	auto pShaderFloor = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderStripes = std::make_shared<CShaderPhong>(*pScene, pTextureStripes, 0.1f, 0.9f, 4.0f, 320.0f);
	auto pShaderRings = std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 2.0f, 320.0f);
	auto pShaderMarble = std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 2.0f, 320.0f);
	auto pShader = std::make_shared<CShaderPhong>(*pScene, pTexture, 0.1f, 0.9f, 2.0f, 320.0f);
	pShader->setBumpMap(pTextureBump, 1.0f);

	// Geometries
	auto pGeom = std::make_shared<CPrimDisc>(pShader, Vec3f(0, 5.0f, 0), normalize(Vec3f(.0f, 1.0f, .7f)), 12.5f, 2.5f);
	pScene->add(CSolidQuad(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
	//pScene->add(CSolidBox(pShaderRings, Vec3f(0, 5, 0), 5));
	//pScene->add(CSolidSphere(pShaderStripes, Vec3f(0, 5, 0), 5, 64));
	pScene->add(pGeom);
	//CSolid teapot(pShaderMarble, dataPath + "Stanford Dragon.obj");

	// Transformation
	CTransform t;
	Mat T = t.rotate(Vec3f(0, 1, 0), 2).scale(1.0f).get();
	//teapot.transform(t.scale(1.5f).get());
	//pScene->add(teapot);

	// Light
	const float	intensity = 15e3;
	const float radius = 66;
	const float alpha = 6;
	if (false) {
		pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, -10)));
	}
	else {
		pScene->add(std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(radius, 100, 0), Vec3f(0, 0, 0), alpha, 2 * alpha));
		//pScene->add(std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(-radius / 2, 100, sqrtf(3) * radius / 2), Vec3f(0, 0, 0), alpha, 2 * alpha));
		//pScene->add(std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(-radius / 2, 100, -sqrtf(3) * radius / 2), Vec3f(0, 0, 0), alpha, 2 * alpha));
	}


	// Cameras
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 33, 50), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 30.0f));


	for (;;) {
		pScene->buildAccelStructure(20, 3);
		Timer::start("Rendering...");
		Mat img = pScene->render(std::make_shared<CSamplerStratified>(4, true, true));
		Timer::stop();
		imshow("Image", img);
		pGeom->transform(T);
		//-imwrite("D:\\renders\\procedural marble.png", img);
		char key = waitKey(1);
		if (key == 27) break;
	}
	return 0;
}
