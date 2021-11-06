#include "openrt.h"
#include "core/timer.h"

using namespace rt;

std::shared_ptr<CScene> buildpSceneColorSphere(const Vec3f& bgColor, const Size resolution)
{
	auto pScene		= std::make_shared<CScene>(bgColor);
	auto pShader	= std::make_shared<CShaderBlinn>(*pScene, Vec3f::all(1), 0.1f, 0.9f, 0.0f, 0.0f);
	auto pPlane		= std::make_shared<CPrimPlane>(pShader, Vec3f::all(0), Vec3f(0, 1, 0));
	auto pSphere	= std::make_shared<CPrimSphere>(pShader, Vec3f::all(0), 1.0f);
	auto pLight1	= std::make_shared<CLightOmni>(Vec3f(0, 0, 200), Vec3f(10, 10, 0), true);
	auto pLight2	= std::make_shared<CLightOmni>(Vec3f(0, 200, 0), Vec3f(-5, 10, 8.66f), true);
	auto pLight3	= std::make_shared<CLightOmni>(Vec3f(200, 0, 0), Vec3f(-5, 10, -8.66f), true);
	auto pCamera	= std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 10, 0), Vec3f(0, -1, 0), Vec3f(1, 0, 0), 30.0f);

	pScene->add(pPlane);
	pScene->add(pSphere);
	pScene->add(pLight1);
	pScene->add(pLight2);
	pScene->add(pLight3);
	pScene->add(pCamera);

	return pScene;
}

std::shared_ptr<CScene> buildSceneMirrorSphere(const Vec3f& bgColor, const Size resolution)
{
	auto pScene			= std::make_shared<CScene>(bgColor);
	
	// texture
	auto pTextureRoom	= std::make_shared<CTexture>(dataPath + "room.jpg");

	// shaders
	auto pShaderFloor	= std::make_shared<CShaderBlinn>(*pScene, RGB(0.522f, 0.6f, 0.706f), 0.1f, 0.9f, 0.0f, 0.0f);
	auto pShaderMirror	= std::make_shared<CShaderGeneral>(*pScene, Vec3f::all(0), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	auto pShaderTop		= std::make_shared<CShaderBlinn>(*pScene, RGB(0.90f, 0.75f, 0.70f), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderChrome	= std::make_shared<CShaderChrome>(*pScene, std::make_shared<CSamplerStratified>(4, true, true));
	auto pShaderRoom	= std::make_shared<CShaderFlat>(pTextureRoom);

	// geometry
	auto pFloor			= std::make_shared<CPrimDisc>(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), 5.0f);
	auto pSphere1		= std::make_shared<CPrimSphere>(pShaderMirror, Vec3f(-2, 1, 0), 1.0f);
	auto pSphere2		= std::make_shared<CPrimSphere>(pShaderTop, Vec3f(0, 1, 0), 1.0f);
	auto pSphere3		= std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(2, 1, 0), 1.0f);
	auto pSphereRoom	= std::make_shared<CPrimSphere>(pShaderRoom, Vec3f(2, 1, 0), 100.0f);

	auto pLight			= std::make_shared<CLightSky>(Vec3f::all(1));
	auto pCamera		= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 5, 10), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 23.0f);

	pScene->add(pFloor);
	pScene->add(pSphere1);
	pScene->add(pSphere2);
	pScene->add(pSphere3);
	pScene->add(pSphereRoom);
	pScene->add(pLight);
	pScene->add(pCamera);

	return pScene;
}

std::shared_ptr<CScene> buildScenePlanets(const Vec3f& bgColor, const Size resolution)
{
	auto pScene				= std::make_shared<CScene>(bgColor);

	// textures
	auto pTextureMercury	= std::make_shared<CTexture>(dataPath + "1_mercury_8k.jpg");
	auto pTextureVenus		= std::make_shared<CTexture>(dataPath + "1_venus_4k.jpg");
	auto pTextureEarth		= std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureMars		= std::make_shared<CTexture>(dataPath + "1_mars_8k.jpg");
	auto pTextureJupiter	= std::make_shared<CTexture>(dataPath + "1_jupiter_8k.jpg");
	auto pTextureNeptune	= std::make_shared<CTexture>(dataPath + "1_neptune_2k.jpg");

	// shaders
	auto pShaderFloor		= std::make_shared<CShaderPhong>(*pScene, std::make_shared<CTexture>()/*RGB(0.522f, 0.6f, 0.7f)*/, 0.0f, 1.0f, 0.0f, 40.0f);
	auto pShaderMercury		= std::make_shared<CShaderPhong>(*pScene, pTextureMercury, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderVenus		= std::make_shared<CShaderPhong>(*pScene, pTextureVenus, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderEarth		= std::make_shared<CShaderPhong>(*pScene, pTextureEarth, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderMars		= std::make_shared<CShaderPhong>(*pScene, pTextureMars, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderJupiter		= std::make_shared<CShaderPhong>(*pScene, pTextureJupiter, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderNeptune		= std::make_shared<CShaderPhong>(*pScene, pTextureNeptune, 0.3f, 1.2f, 0.0f, 40.0f);

	// primitives
	auto floor				= std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0));
	auto mercury			= std::make_shared<CPrimSphere>(pShaderMercury, Vec3f(-3, 0.383f, -1), 0.383f);
	auto venus				= std::make_shared<CPrimSphere>(pShaderVenus, Vec3f(2.5f, 0.95f, 5), 0.95f);
	auto earth				= std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(-3, 1.0f, -2.6f), 1.0f);
	auto mars				= std::make_shared<CPrimSphere>(pShaderMars, Vec3f(-2.5f, 0.5321f, 1.5f), 0.5321f);
	auto jupiter			= std::make_shared<CPrimSphere>(pShaderJupiter, Vec3f(0, 3.3f, 0), 3.3f); // real r = 10.973f
	auto neptune			= std::make_shared<CPrimSphere>(pShaderNeptune, Vec3f(0, 3.8647f, 0), 3.8647f);

	// light
	auto pLight				= std::make_shared<CLightSky>(Vec3f::all(1), 0.0f);

	// camera
	auto pCamera			= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-10, 5, 0), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 40.0f);

	pScene->add(floor);
	pScene->add(mercury);
	pScene->add(venus);
	pScene->add(earth);
	pScene->add(mars);
	//pScene->add(jupiter);
	pScene->add(neptune);
	pScene->add(pLight);
	pScene->add(pCamera);

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
	auto pShaderTop = std::make_shared<CShaderBlinn>(*pScene, RGB(0.90f, 0.75f, 0.70f), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderSide = std::make_shared<CShaderBlinn>(*pScene, RGB(0.55f, 0.65f, 0.70f), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderFloor = std::make_shared<CShaderBlinn>(*pScene, RGB(0.522f, 0.6f, 0.706f), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderEarth = std::make_shared<CShaderBlinn>(*pScene, pTextureEarth, 0.2f, 0.7f, 0.0f, 40.0f);
	auto pShaderWhite = std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderChrome = std::make_shared<CShaderChrome>(*pScene, std::make_shared<CSamplerStratified>(4, true, true));
	auto pShaderGlass = std::make_shared<CShaderGeneral>(*pScene, RGB(0.55f, 0.65f, 0.70f), 0.0f, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderMirror = std::make_shared<CShaderGeneral>(*pScene, RGB(0.55f, 0.65f, 0.70f), 0.0f, 0.1f, 2.0f, 80.0f, 1.0f, 0.0f, 1.5f);

	// primitives
	
	// floor
	pScene->add(std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0)));
	//pScene->add(CSolidQuad(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0), Vec3f(100, 0, 0)));

	// --- light panel ---
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(0, 10.01f, 0), Vec3f(0, -1, 0), Vec3f(10, 0, 0)));

	// --- cube ---
	pScene->add(CSolidQuad(pShaderTop, Vec3f(0, 2, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0)));
	pScene->add(CSolidQuad(pShaderSide, Vec3f(1, 1, 0), Vec3f(1, 0, 0), Vec3f(0, 0, 1)));
	pScene->add(CSolidQuad(pShaderSide, Vec3f(-1, 1, 0), Vec3f(1, 0, 0), Vec3f(0, 0, -1)));
	pScene->add(CSolidQuad(pShaderSide, Vec3f(0, 1, 1), Vec3f(0, 0, 1), Vec3f(1, 0, 0)));
	pScene->add(CSolidQuad(pShaderSide, Vec3f(0, 1, -1), Vec3f(0, 0, -1), Vec3f(-1, 0, 0)));
	// --- ---- ---

	pScene->add(std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(3, 1.0f, 0), 1.0f));
	pScene->add(std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(-3, 1.0f, 0), 1.0f));
	//pScene->add(CSolidSphere(pShaderChrome, Vec3f(3, 1.0f, 0), 1, 24));
	//pScene->add(CSolidSphere(pShaderChrome, Vec3f(-3, 1.0f, 0), 1, 24));		


	
	CTransform t;

	//pScene->add(std::make_shared<CPrimSphere>(std::make_shared<CShaderEyelight>(Vec3f::all(1)), Vec3f::all(0), 3.0f));
	auto earth = std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0, 0), 4.0f);
	auto cylinder = CSolidCylinder(pShaderEarth, Vec3f(0, 0, 0), 4, 4, 5, 36, true);
	auto cone = CSolidCone(pShaderEarth, Vec3f(0, 0, 0), 4, 5, 5, 24, true);
	//	auto cube		= CSolidBox(pShaderFloorTxt, Vec3f(0, 1, 0), 1);
	//cylinder.transform(CTransform().reflectY().reflectX().get());
	//	pScene->add(earth);
	//	pScene->add(std::make_shared<CPrimSphere>(std::make_shared<CShaderBlinn>(scene, RGB(0, 0, 1),   0.2f, 0.5f, 0.5f, 40.0f), Vec3f(2, 1.8f, -3), 2));
	//	pScene->add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderBlinn>(scene, RGB(0, 1, 1), 0.2f, 0.5f, 0.5f, 40.0f), Vec3f(-3, 4.7f, -1), Vec3f(0, 3, 0), Vec3f(2, 3.8f, -3)));
	//	pScene->add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderBlinn>(scene, RGB(1, 1, 1), 0.2f, 0.5f, 0.5f, 40.0f), Vec3f(2, 3, 2), Vec3f(2, 3, -4), Vec3f(-4, 3, -4)));

	// lights
	//scene.add(std::make_shared<CLightOmni>(Vec3f::all(30), Vec3f(-4, 6, 3), true));
	//scene.add(std::make_shared<CLightOmni>(Vec3f::all(30), Vec3f(0, 10, 0), true));
	pScene->add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(4, true, true)));

	// camera
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(10, 10, 0), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 45.0f));

	return pScene;
}







int main(int argc, char* argv[])
{
	const Vec3f	bgColor = RGB(0.77f, 0.82f, 0.89f);
	const Size resolution(2 * 960, 2 * 600);
	// const Size resolution(3072, 1920);

	//auto pScene = buildpSceneColorSphere(bgColor, resolution);
	auto pScene = buildSceneMirrorSphere(bgColor, resolution);
	//auto pScene = buildScenePlanets(bgColor, resolution);
	//auto pScene = buildSceneBox(bgColor, resolution);

	pScene->buildAccelStructure(0, 3);

	Timer::start("Rendering...");
	Mat render = pScene->render(std::make_shared<CSamplerStratified>(4, true, true));
	Timer::stop();
	imshow("pScene", render);
	imwrite("D:\\renders\\Boxes.png", render);
	waitKey();
	return 0;
}
