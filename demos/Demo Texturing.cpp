#include "openrt.h"
#include "core/timer.h"

using namespace rt;

static std::shared_ptr<CScene> buildSceneStripes(const Vec3f& bgColor, const Size resolution) {
	
	auto pScene = std::make_shared<CScene>(bgColor);
	pScene->setAmbientColor(Vec3f::all(0.2f));

	// Geometry
	pScene->addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 50);
	auto sphere = pScene->addSphere(Vec3f(0, 1, 0), 1.0f);

	// Gradient for texture
	CGradient gradient({{0.0f, RGB(255, 255, 255)}, {0.5f, RGB(255, 255, 255)}, { 0.501f, RGB(255, 0, 0) }, {1.0f, RGB(255, 0, 0)}});
	CGradient gradientMarble(RGB(166, 208, 229), RGB(175, 152, 123));
	gradientMarble.addColor(0.37f, RGB(128, 182, 222));
	gradientMarble.addColor(0.54f, RGB(90, 175, 213));
	gradientMarble.addColor(0.66f, RGB(103, 152, 176));
	gradientMarble.addColor(0.75f, RGB(28, 163, 215));
	gradientMarble.addColor(0.84f, RGB(19, 140, 183));
	gradientMarble.addColor(0.92f, RGB(55, 118, 149));

	auto pNoise = std::make_shared<CPerlinNoise>(2025, 15.0f, 0.04f, 10, 0.5f, 2.0f);
	
	// Textures
	auto pTextureStripes = std::make_shared<CTextureStripes>(gradient, 1);
	auto pTextureRings	 = std::make_shared<CTextureRings>(gradient, 5);
	auto pTextureMarble	 = std::make_shared<CTextureMarble>(gradientMarble, 1, pNoise);
	auto pTexture		 = std::make_shared<CTexture>(dataPath + "b13.jpg");

	// Shaders
	auto pShaderStripes = std::make_shared<CShaderPhong>(*pScene, pTextureStripes, 1.0f, 0.9f, 2.0f, 320.0f);
	auto pShaderRings	= std::make_shared<CShaderPhong>(*pScene, pTextureRings, 0.1f, 0.9f, 2.0f, 320.0f);
	auto pShaderMarble	= std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 2.0f, 320.0f);
	auto pShader = std::make_shared<CShaderPhong>(*pScene, pTexture, 1.0f, 1.0f, 0.0f, 0.0f);
	
	sphere->setShader(pShaderMarble);

	// Light
	const float	intensity = 15e3;
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
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 3, 5), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 35.0f));

	return pScene;
}

static std::shared_ptr<CScene> buildSceneTemplates(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);
	pScene->setAmbientColor(Vec3f::all(0.1f));

	// Geometry
	pScene->addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 100);
	auto sphere = pScene->addSphere(Vec3f(4, 1.5f, 0), 1.5f);
	
	// Wood shader
	CGradient gradientWood({ {0.0f, RGB(255, 205, 140)}, {0.1f, RGB(216, 139, 74)}, {0.4f, RGB(226, 147, 82)}, {0.6f, RGB(250, 180, 127)}, {1.0f, RGB(255, 205, 140)} });
	//CGradient gradientWood({{0.0f, RGB(255, 255, 255)}, {0.499f, RGB(255, 255, 255)}, {0.5f, RGB(255, 0, 0)}, {1.0f, RGB(255, 0, 0)}});
	auto pNoise			= std::make_shared<CPerlinNoise>(2022, 2.5f, 1.5f, 2, 0.5f, 2.0f);
	auto pTextureWood	= std::make_shared<CTextureRings>(gradientWood, 12.0f, pNoise);
	auto pShaderWood	= std::make_shared<CShaderDiffuse>(*pScene, pTextureWood);

	// Marble shader
	//CGradient gradientMarble(RGB(255, 255, 255), RGB(119, 135, 153));
	//auto pTextureMarble = std::make_shared<CTextureMarble>(gradientMarble, 0.5f, 6, 0.24f, 2.4f, 2.5f, 0.35f, false);
	//auto pShaderMarble = std::make_shared<CShaderPhong>(*pScene, pTextureMarble, 0.1f, 0.9f, 0.0f, 40.0f);

	// Geometries
	pScene->add(CSolidBox(pShaderWood, Vec3f(0, 0.5f, 0), 2.5f, 1.0f, 12.0f));

	sphere->setShader(pShaderWood);

	//Light
	const float intensity = 3e4;
	if (false) {
		pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 50)));
		pScene->add(std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, -100, -50), false));
	}
	else pScene->add(std::make_shared<CLightSky>(Vec3f::all(1), 5.0f, std::make_shared<CSamplerStratified>(4)));


	//Cameras
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(1.5f, 6, 12), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 45.0f);
	pScene->add(pCamera);

	return pScene;
}

static std::shared_ptr<CScene> buildSceneMoon(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);

	// Geometry
	auto moon = pScene->addSphere(Vec3f(0, 0, 0), 1.7374f);
	
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(7e16f), Vec3f(-150e6f * cosf(Pif * 60 / 180), 0, -150e6f * sinf(Pif * 60 / 180)), true));
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-384.4f, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0.8f));
	
	// Transforming the geometry
	CTransform t;
	moon->transform(t.rotate(Vec3f(0, 1, 0), 15).get());

	// Textures
	auto moon_diffuse	= std::make_shared<CTexture>(dataPath + "lroc_color_poles_4k.tif");
	auto moon_bump		= std::make_shared<CTexture>(dataPath + "ldem_16_uint.tif");

	// Shaders
	auto pShaderMoon	= std::make_shared<CShaderDiffuse>(*pScene, moon_diffuse, 20);
	pShaderMoon->setBumpMap(moon_bump);

	moon->setShader(pShaderMoon);

	return pScene;
}

static std::shared_ptr<CScene> buildSceneSaturn(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);

	// Geometry
	auto saturn = pScene->addSphere(Vec3f(0, 0, 0), 60.33f);
	auto rings = pScene->addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 142.0f, 72.0f);
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(6e18f), Vec3f(0, 0, 1430e6), true));													// sun
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-1000.0f, 300, 670), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 9.0f));	// camera

	// Transforming the geometry
	CTransform t;
	Mat T = t.rotate(Vec3f(1, 0, 0), 28.f).get();
	saturn->transform(T);
	rings->transform(T);

	// Textures
	auto saturn_diffuse = std::make_shared<CTexture>(dataPath + "1_saturn_8k.jpg");
	auto rings_diffuse = std::make_shared<CTexture>(dataPath + "8k_saturn_ring.png");
	auto rings_opacity = std::make_shared<CTexture>(dataPath + "8k_saturn_ring_alpha.png");

	// Shaders
	auto pShaderSaturn = std::make_shared<CShaderDiffuse>(*pScene, saturn_diffuse, 5.0f);
	auto pShaderRings = std::make_shared<CShaderDiffuse>(*pScene, rings_diffuse, 30.0f);
	pShaderRings->setOpacity(rings_opacity);

	saturn->setShader(pShaderSaturn);
	rings->setShader(pShaderRings);

	return pScene;
}

static std::shared_ptr<CScene> buildSceneEarth(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);
	pScene->setAmbientColor(Vec3f::all(1.0f));

	// Geometry
	auto surface	= pScene->addSphere(Vec3f(0, 0, 0), 6.371f);
	auto clouds		= pScene->addSphere(Vec3f(0, 0, 0), 6.383f);
	auto atmosphere = pScene->addSphere(Vec3f(0, 0, 0), 6.451f);
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(1e11), Vec3f(149600, 0, 0), true));		// sun
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(2, 0, 6.3f), Vec3f(149600, 0, -100000), Vec3f(0, 0, 1), 60.0f));
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(10, 12, 24), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 35.0f));

	// Transforming the geometry
	CTransform t;
	Mat T = t.rotate(Vec3f(0, 1, 0), 60).rotate(Vec3f(0, 0, 1), -23.5f).get();
	surface->transform(T);
	clouds->transform(T);

	// Textures
	bool highres = false;
	auto surface_ambient	= std::make_shared<CTexture>(dataPath + "1_earth_night_map_8k.jpg");
	auto surface_diffuse	= std::make_shared<CTexture>(dataPath + (highres ? "earth_color_43K.tif" : "8081_earthmap10k.jpg"));
	auto surface_bump		= std::make_shared<CTexture>(dataPath + (highres ? "topography_21K.png" : "8081_earthbump10k.jpg"));
	auto surface_specular	= std::make_shared<CTexture>(dataPath + "8081_earthspec10k.jpg");
	auto clouds_opacity		= std::make_shared<CTexture>(dataPath + (highres ? "earth_clouds_43K.tif" : "earth_clouds_8K.tif"));
	

	// Shaders
	auto pShaderSurface = std::make_shared<CShaderPhong>(*pScene, surface_diffuse, 0.0f, 1.0f, 0.01f, 15.0f);
	pShaderSurface->setAmbientColor(surface_ambient);
	pShaderSurface->setBumpMap(surface_bump, 0.1f);
	pShaderSurface->setSpecularColor(surface_specular);
	surface->setShader(pShaderSurface);

	auto pShaderClouds = std::make_shared<CShaderDiffuse>(*pScene, 1.4f * RGB(255, 255, 255), 30.0f);
	pShaderClouds->setAmbientColor(Vec3f::all(0));
	pShaderClouds->setOpacity(clouds_opacity);
	pShaderClouds->setBumpMap(clouds_opacity, 0.01f);
	clouds->setShader(pShaderClouds);

	auto pShaderAtmosphere = std::make_shared<CShaderVolumeScatter>(*pScene, 0.5f * RGB(0, 127, 255), nullptr, 0.05f);
	atmosphere->setShader(pShaderAtmosphere);

	return pScene;
}

static std::shared_ptr<CScene> buildSceneMarble(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(RGB(12, 12, 12));
	pScene->setAmbientColor(Vec3f::all(0.1f));

	// Geometry
	auto floor	= pScene->addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 100.0f, .0f, RGB(120, 120, 120));
	auto disc	= pScene->addDisc(Vec3f(0, 5.1f, 0), Vec3f(0, -1, 0), 1);
	auto sphere = pScene->addSphere(Vec3f(0, 1.3f, 0), 1);
	
	// Light
	pScene->add(std::make_shared<CLightArea>(Vec3f::all(10), Vec3f(3, 3.5f, -1.5f), Vec3f(3, 3.5f, -3.5f), Vec3f(3, 1.5f, -3.5f), Vec3f(3, 1.5f, -1.5f), std::make_shared<CSamplerStratified>(4)));
	pScene->add(std::make_shared<CLightArea>(Vec3f::all(10), Vec3f(-1, 5, -1), Vec3f(1, 5, -1), Vec3f(1, 5, 1), Vec3f(-1, 5, 1), std::make_shared<CSamplerStratified>(4)));

	// Camera
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 1.5f, -3), Vec3f(0, 1.2f, 0), Vec3f(0, 1, 0), 60));

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
	//auto pShaderMarble	= std::make_shared<CShaderPrincipled>(*pScene, pTextureMarble, 1.0f, 1.0f, 0, 0, 0.2f, 0, 1);
	auto pShaderMarble1 = std::make_shared<CShaderPrincipled>(*pScene, pTextureMarble1, 1.0f, 1.0f, 0, 0, 0.2f, 0, 1);

	// Geometry
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(3.1f, 3, -2), Vec3f(-1, 0, 0), Vec3f(0, 0, -1), 0.45f));
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(3.1f, 3, -3), Vec3f(-1, 0, 0), Vec3f(0, 0, -1), 0.45f));
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(3.1f, 2, -2), Vec3f(-1, 0, 0), Vec3f(0, 0, -1), 0.45f));
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(3.1f, 2, -3), Vec3f(-1, 0, 0), Vec3f(0, 0, -1), 0.45f));


	disc->setShader(pShaderWhite);
	sphere->setShader(pShaderMarble1);

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

int main()
{
	const Vec3f		bgColor = RGB(0, 0, 0);
	const Size		resolution = Size(1200, 800);
	//const Size		resolution = Size(3072, 1920);
	
	//auto pScene = buildSceneStripes(bgColor, resolution);
	//auto pScene = buildSceneTemplates(bgColor, resolution);
	//auto pScene = buildSceneMoon(bgColor, resolution);
	//auto pScene = buildSceneSaturn(bgColor, resolution);
	//auto pScene = buildSceneEarth(bgColor, resolution);
	auto pScene = buildSceneMarble(bgColor, resolution);
	//pScene->buildAccelStructure(20, 3);
	//Timer::start("Rendering...");
	//Mat img = pScene->render(std::make_shared<CSamplerStratified>(2));
	//Timer::stop();
	//imshow("Image", img);
	////imwrite("D:\\renders\\Saturn.jpg", img);
	//char key = waitKey();

	//auto pScene = std::make_shared<CScene>(bgColor);

	//Mat diff = imread(dataPath + "lroc_color_poles_4k.tif");
	//Mat bump = imread(dataPath + "ldem_16_uint.tif");

	//resize(diff, diff, Size(4000, 2000), 0, 0, INTER_AREA);
	//resize(bump, bump, Size(1400, 700), 0, 0, INTER_AREA);

	//auto pShader = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0, 1, 0, 0);
	//pShader->setDiffuseColor(std::make_shared<CTexture>(diff));
	////pShader->setBumpMap(std::make_shared<CTexture>(bump), 1.0f);
	////pShader->setBumpMap(std::make_shared<CTexture>(dataPath + "golfball.jpg"));

	//auto moon = CSolidSphere(pShader, Vec3f(0, 0, 0), 1.7374f, 64);
	//CTransform t;
	//auto T = t.rotate(Vec3f(0, 1, 0), 0.25f).get();
	////moon.transform(t.rotate(Vec3f(0, 1, 0), 90).get());
	//auto pLight = std::make_shared<CLightOmni>(Vec3f::all(2e16), Vec3f(-150e6 * cosf(Pif * 60 / 180), 0, -150e6 * sinf(Pif * 60 / 180)), true);

	//pScene->add(moon);
	//pScene->add(pLight);
	//pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-384.4f, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0.8f));
	
	pScene->buildAccelStructure(20, 3);
	Timer::start("Rendering...");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(4), 64);
	Timer::stop();
	imwrite("D:/renders/Render30.jpg", img);
	imshow("Image", img);
	waitKey();

	//VideoWriter videoWriter;
	//auto codec = VideoWriter::fourcc('M', 'J', 'P', 'G');		// Native windows codec
	//auto codec = VideoWriter::fourcc('H', '2', '6', '4');		// Try it on MacOS
	//videoWriter.open("D:\\Renders\\moon.avi", codec, 30, resolution);
	//if (!videoWriter.isOpened()) printf("ERROR: Can't open vide file for writing\n");

	//for (int i = 130; i < 330; i+= 1) {
	//	pLight->setOrigin(Vec3f(150e6 * cosf(Pif * i / 180), 150e6 * sinf(Pif * i / 180), 0));
	//	Timer::start("Rendering...");
	//	Mat img = pScene->render(std::make_shared<CSamplerStratified>(4));
	//	Timer::stop();
	//	//videoWriter << img;
	//	imshow("Image", img);
	//	
	//	//moon.transform(T);
	//	imwrite("D:\\renders\\moon no bump.png", img);
	//	char key = waitKey();
	//	if (key == 27) break;
	//}
	return 0;
}
