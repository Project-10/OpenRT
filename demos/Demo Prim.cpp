#include "openrt.h"
#include "core/timer.h"
#include "core/random.h"

using namespace rt;

std::shared_ptr<CScene> buildpSceneColorSphere(const Vec3f& bgColor, const Size resolution)
{
	auto pScene		= std::make_shared<CScene>(bgColor);
	auto pLight1	= std::make_shared<CLightOmni>(Vec3f(0, 0, 200), Vec3f(10, 10, 0), true);
	auto pLight2	= std::make_shared<CLightOmni>(Vec3f(0, 200, 0), Vec3f(-5, 10, 8.66f), true);
	auto pLight3	= std::make_shared<CLightOmni>(Vec3f(200, 0, 0), Vec3f(-5, 10, -8.66f), true);
	auto pCamera	= std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 10, 0), Vec3f(0, -1, 0), Vec3f(1, 0, 0), 30.0f);

	pScene->addPlane();
	pScene->addSphere();
	pScene->add(pLight1);
	pScene->add(pLight2);
	pScene->add(pLight3);
	pScene->add(pCamera);

	return pScene;
}

std::shared_ptr<CScene> buildSceneMirrorSphere(const Vec3f& bgColor, const Size resolution)
{
	auto pScene			= std::make_shared<CScene>(bgColor);
	
	// Geometry
	const float R		= 150.0f;		// The size of the world
	auto floor			= pScene->addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), R, 0.0f, RGB(133, 153, 180));
	auto environment	= pScene->addSphere(Vec3f(0, 0, 0), R);
	auto sphere_center	= pScene->addSphere(Vec3f(0, 1, 0), 1.0f, RGB(230, 191, 179));
	auto sphere_left	= pScene->addSphere(Vec3f(-2, 1, 0), 1.0f, RGB(230, 191, 179));
	auto sphere_right	= pScene->addSphere(Vec3f(2, 1, 0), 1.0f, RGB(230, 191, 179));

	environment->flipNormal();

	//pScene->add(std::make_shared<CLightSky>(Vec3f::all(0.5f)));	// light source
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 5, 10), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 23.0f));

	// Shaders
	//auto pShaderEnvironment	= std::make_shared<CShaderFlat>(std::make_shared<CTexture>(dataPath + "earth_color_43K.tif"));
	auto pShaderEnvironment = std::make_shared<CShaderFlat>(RGB(255, 255, 255));
	auto pShaderMirror		= std::make_shared<CShaderGeneral>(*pScene, Vec3f::all(0), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	auto pShaderChrome		= std::make_shared<CShaderChrome>(*pScene, std::make_shared<CSamplerStratified>(4, true, true));
	auto pShaderGlass		= std::make_shared<CShaderGeneral>(*pScene, Vec3f::all(0), 0, 0, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	//auto pShaderGlobal1		= std::make_shared<CShaderGlobal>(*pScene, RGB(133, 153, 180), std::make_shared<CSamplerStratified>(4, true, true));
	//auto pShaderGlobal2		= std::make_shared<CShaderGlobal>(*pScene, RGB(230, 191, 179), std::make_shared<CSamplerStratified>(4, true, true));

	pShaderChrome->setDiffuseColor(RGB(255, 127, 0));

	environment->setShader(pShaderEnvironment);
	sphere_left->setShader(pShaderMirror);
	//floor->setShader(pShaderGlobal1);
	//sphere_center->setShader(pShaderGlobal2);
	sphere_right->setShader(pShaderChrome);
	
	return pScene;
}

std::shared_ptr<CScene> buildScenePlanets(const Vec3f& bgColor, const Size resolution)
{
	auto pScene				= std::make_shared<CScene>(bgColor);

	// Geometry
	auto floor		= pScene->addPlane();
	auto mercury	= pScene->addSphere(Vec3f(-3, 0.383f, -1), 0.383f); 
	auto venus		= pScene->addSphere(Vec3f(2.5f, 0.95f, 5), 0.95f);
	auto earth		= pScene->addSphere(Vec3f(-3, 1.0f, -2.6f), 1.0f);
	auto mars		= pScene->addSphere(Vec3f(-2.5f, 0.5321f, 1.5f), 0.5321f);
	//auto jupiter	= pScene->addSphere(Vec3f(0, 3.3f, 0), 3.3f); // real r = 10.973f
	auto neptune	= pScene->addSphere(Vec3f(0, 3.8647f, 0), 3.8647f);

	pScene->add(std::make_shared<CLightSky>(Vec3f::all(1), 0.0f, std::make_shared<CSamplerStratified>(4, true, true)));	// light
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-10, 5, 0), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 40.0f));	// camera

	// Textures
	auto pTextureMercury	= std::make_shared<CTexture>(dataPath + "1_mercury_8k.jpg");
	auto pTextureVenus		= std::make_shared<CTexture>(dataPath + "1_venus_4k.jpg");
	auto pTextureEarth		= std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureMars		= std::make_shared<CTexture>(dataPath + "1_mars_8k.jpg");
	auto pTextureJupiter	= std::make_shared<CTexture>(dataPath + "1_jupiter_8k.jpg");
	auto pTextureNeptune	= std::make_shared<CTexture>(dataPath + "1_neptune_2k.jpg");

	// Shaders
	auto pShaderFloor		= std::make_shared<CShaderPhong>(*pScene, std::make_shared<CTexture>()/*RGB(0.522f, 0.6f, 0.7f)*/, 0.0f, 1.0f, 0.0f, 40.0f);
	auto pShaderMercury		= std::make_shared<CShaderPhong>(*pScene, pTextureMercury, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderVenus		= std::make_shared<CShaderPhong>(*pScene, pTextureVenus, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderEarth		= std::make_shared<CShaderPhong>(*pScene, pTextureEarth, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderMars		= std::make_shared<CShaderPhong>(*pScene, pTextureMars, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderJupiter		= std::make_shared<CShaderPhong>(*pScene, pTextureJupiter, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderNeptune		= std::make_shared<CShaderPhong>(*pScene, pTextureNeptune, 0.3f, 1.2f, 0.0f, 40.0f);

	floor->setShader(pShaderFloor);
	mercury->setShader(pShaderMercury);
	venus->setShader(pShaderVenus);
	earth->setShader(pShaderEarth);
	mars->setShader(pShaderMars);
	//jupiter->setShader(pShaderJupiter);
	neptune->setShader(pShaderNeptune);

	return pScene;
}

std::shared_ptr<CScene> buildSceneBox(const Vec3f& bgColor, const Size resolution)
{
	bool usePrims = true;
	
	
	auto pScene = std::make_shared<CScene>(bgColor);


	// textures
	auto pTextureEarth	= std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureB13	= std::make_shared<CTexture>(dataPath + "b13.jpg");

	// shaders
	auto pShaderTop = std::make_shared<CShaderBlinn>(*pScene, RGB(230, 191, 179), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderSide = std::make_shared<CShaderBlinn>(*pScene, RGB(140, 166, 179), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderFloor = std::make_shared<CShaderBlinn>(*pScene, RGB(133, 153, 180), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderEarth = std::make_shared<CShaderBlinn>(*pScene, pTextureEarth, 0.2f, 0.7f, 0.0f, 40.0f);
	auto pShaderWhite = std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderChrome = std::make_shared<CShaderChrome>(*pScene, std::make_shared<CSamplerStratified>(4, true, true));
	auto pShaderGlass = std::make_shared<CShaderGeneral>(*pScene, RGB(140, 166, 179), 0.0f, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderMirror = std::make_shared<CShaderGeneral>(*pScene, RGB(140, 166, 179), 0.0f, 0.1f, 2.0f, 80.0f, 1.0f, 0.0f, 1.5f);

	// primitives
	
	// floor
	//pScene->add(std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0)));
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0), Vec3f(100, 0, 0)));

	// --- light panel ---
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(0, 10.01f, 0), Vec3f(0, -1, 0), Vec3f(10, 0, 0)));

	// --- cube ---
	pScene->add(CSolidQuad(pShaderTop, Vec3f(0, 2, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0)));
	pScene->add(CSolidQuad(pShaderSide, Vec3f(1, 1, 0), Vec3f(1, 0, 0), Vec3f(0, 0, 1)));
	pScene->add(CSolidQuad(pShaderSide, Vec3f(-1, 1, 0), Vec3f(1, 0, 0), Vec3f(0, 0, -1)));
	pScene->add(CSolidQuad(pShaderSide, Vec3f(0, 1, 1), Vec3f(0, 0, 1), Vec3f(1, 0, 0)));
	pScene->add(CSolidQuad(pShaderSide, Vec3f(0, 1, -1), Vec3f(0, 0, -1), Vec3f(-1, 0, 0)));
	// --- ---- ---

	//pScene->add(std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(3, 1.0f, 0), 1.0f));
	//pScene->add(std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(-3, 1.0f, 0), 1.0f));
	//pScene->add(CSolidSphere(pShaderChrome, Vec3f(3, 1.0f, 0), 1, 24));
	//pScene->add(CSolidSphere(pShaderChrome, Vec3f(-3, 1.0f, 0), 1, 24));		


	
	CTransform t;

	//pScene->add(std::make_shared<CPrimSphere>(std::make_shared<CShaderEyelight>(Vec3f::all(1)), Vec3f::all(0), 3.0f));
	auto earth = std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0, 0), 4.0f);
	auto cylinder = CSolidCylinder(pShaderEarth, Vec3f(0, 0, 0), 4, 4, 5, 36, true);
	auto cone = CSolidCone(pShaderEarth, Vec3f(0, 0, 0), 4, 5, 5, 24, true);
	//	auto cube		= CSolidBox(pShaderFloorTxt, Vec3f(0, 1, 0), 1);
	//cylinder.transform(CTransform().reflectY().reflectX().get());
	pScene->add(cone);
	//	pScene->add(std::make_shared<CPrimSphere>(std::make_shared<CShaderBlinn>(scene, RGB(0, 0, 255),   0.2f, 0.5f, 0.5f, 40.0f), Vec3f(2, 1.8f, -3), 2));
	//	pScene->add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderBlinn>(scene, RGB(0, 255, 255), 0.2f, 0.5f, 0.5f, 40.0f), Vec3f(-3, 4.7f, -1), Vec3f(0, 3, 0), Vec3f(2, 3.8f, -3)));
	//	pScene->add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderBlinn>(scene, RGB(1, 255, 255), 0.2f, 0.5f, 0.5f, 40.0f), Vec3f(2, 3, 2), Vec3f(2, 3, -4), Vec3f(-4, 3, -4)));

	// lights
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(30), Vec3f(-4, 6, 3), true));
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(30), Vec3f(0, 10, 0), true));
	//pScene->add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(4, true, true)));

	// camera
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-10, 10, 0), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 45.0f));

	return pScene;
}

std::shared_ptr<CScene> buildSceneTorusKnot(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);
	
	// Geometry
	auto floor	= pScene->addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 10.0f, 0.0f, RGB(133, 153, 180));
	auto sphere	= pScene->addSphere(Vec3f(0, 0.5f, 0), 0.5f);
	
	// Shaders
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1.2f));
	auto pShaderGlass	= std::make_shared<CShaderGeneral>(*pScene, RGB(140, 166, 179), 0, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	//auto pShaderGlobal  = std::make_shared<CShaderHemisphere>(*pScene, RGB(133, 153, 180), std::make_shared<CSamplerStratified>(4, true, true));

	//floor->setShader(pShaderGlobal);
	//sphere->setShader(pShaderGlass);
	
	// geometry
	CSolidQuad lightPanel(pShaderWhite, Vec3f(0, 2.1f, 0), Vec3f(0, -1, 0), Vec3f(1, 0, 0), 1);
	CSolid torusKnot(std::make_shared<CShaderDiffuse>(*pScene, Vec3f::all(0.8f)), dataPath + "Torus Knot.obj");
	
	// light
	//auto pLight = std::make_shared<CLightOmni>(Vec3f::all(3e2), Vec3f(0, 20, 0));
	auto pLight				= std::make_shared<CLightArea>(Vec3f::all(1), Vec3f(-1, 2, -1), Vec3f(1, 2, -1), Vec3f(1, 2, 1), Vec3f(-1, 2, 1), std::make_shared<CSamplerStratified>(4, true, true));
	//auto pLight		= std::make_shared<CLightSky>(Vec3f::all(1));

	// camera
	auto pCamera			= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-5, 4, 10), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 10.0f);
	
	pScene->add(floor);
	pScene->add(lightPanel);
	pScene->add(torusKnot);
	
	pScene->add(sphere);
	pScene->add(pLight);
	pScene->add(pCamera);
		
	return pScene;
}

std::shared_ptr<CScene> buidSceneOcclusions(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);

	// Geometry
	//auto plane	= pScene->addPlane();
	//auto sphere	= pScene->addSphere();

	for (int i = 0; i < 1000; i++) {
		auto pShader = std::make_shared<CShaderDiffuse>(*pScene, RGB(random::u(0, 255), random::u(0, 255), random::u(0, 255)));
		pShader->setOpacity(static_cast<float>(random::u(100, 500)) / 1000);
		auto solid = CSolidQuad(pShader, Vec3f(random::u(-40, 40), static_cast<float>(random::u(1000, 60000)) / 1000, random::u(-40, 40)), Vec3f(0, 1, 0), Vec3f(1, 0, 0), static_cast<float>(random::u(1000, 5000)) / 1000);
		pScene->add(solid);
	}

	auto s2 = std::make_shared<CShaderDiffuse>(*pScene, RGB(20, 155, 20));
	s2->setOpacity(0.5f);
	auto s3 = std::make_shared<CShaderDiffuse>(*pScene, RGB(155, 20, 20));
	s3->setOpacity(0.4f);

	
	auto q2 = CSolidQuad(s2, Vec3f(-2, 30, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0), 4);
	auto q3 = CSolidQuad(s3, Vec3f(-2, 40, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0), 1);

	//pScene->add(q2);
	//pScene->add(q3);
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(5e3), Vec3f(0, 100, 0)));
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(20, 100, 20), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 35.0f));

	return pScene;
}

int main(int argc, char* argv[])
{
	//const Vec3f	bgColor = RGB(196, 209, 227);
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size resolution(960, 600);
	//const Size resolution(3072, 1920);

	//auto pScene = buildpSceneColorSphere(bgColor, resolution);
	//auto pScene = buildSceneMirrorSphere(bgColor, resolution);
	auto pScene = buildScenePlanets(bgColor, resolution);
	//auto pScene = buildSceneBox(bgColor, resolution);
	//auto pScene = buildSceneTorusKnot(bgColor, resolution);
	//auto pScene = buidSceneOcclusions(bgColor, resolution);
	
	pScene->buildAccelStructure(0, 3);

	Timer::start("Rendering...");
	Mat render = pScene->render(std::make_shared<CSamplerStratified>(4, true, true), 64);
	Timer::stop();
	imshow("pScene", render);
	imwrite("D:\\renders\\Render.png", render);
	waitKey();
	return 0;
}
