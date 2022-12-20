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

	// Shaders
	auto pShaderFloor	= std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderStripes = std::make_shared<CShaderPhong>(*pScene, pTextureStripes, 0.1f, 0.9f, 2.0f, 320.0f);
	auto pShaderRings	= std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 2.0f, 320.0f);
	auto pShaderMarble	= std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 2.0f, 320.0f);
	
	// Geometries
	pScene->add(CSolidQuad(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
	//pScene->add(CSolidBox(pShaderRings, Vec3f(0, 5, 0), 5));
	//pScene->add(CSolidSphere(pShaderRings, Vec3f(0, 5, 0), 5));
	CSolid teapot(pShaderMarble, dataPath + "Stanford Dragon.obj");

	// Transformation
	CTransform t;
	teapot.transform(t.scale(1.5f).get());
	pScene->add(teapot);

	// Light
	const float	intensity = 3e3;
	const float radius = 66;
	const float alpha = 8;
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

std::shared_ptr<CScene> buildSceneMarble(const Vec3f& bgColor, const Size resolution)
{
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
	auto pTextureMarble1 = std::make_shared<CTextureMarble>(gradientMarble, 2022, 0, 3.0f, 0.2f, 10, 0.5f, 2.0f);
	CGradient gradientRedWhite({{0.0f, RGB(255, 255, 255)}, {1.0f, RGB(255, 0, 0)} });
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

int main()
{
	const Vec3f		bgColor = RGB(12, 12, 12);
	const Size		resolution = Size(800, 600);
	
	auto pScene = buildSceneStripes(bgColor, resolution);
//	auto pScene = buildSceneRings(bgColor, resolution);
	// auto pScene = buildSceneTemplates(bgColor, resolution);
	// auto pScene = buildSceneMarble(bgColor, resolution);

	pScene->buildAccelStructure(20, 3);
	Timer::start("Rendering...");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(2, true, true));
	Timer::stop();
	imshow("Image", img);
	//-imwrite("D:\\renders\\procedural marble.png", img);
	waitKey();
	 
	return 0;
}
