#include "openrt.h"
#include "core/timer.h"

using namespace rt;

std::shared_ptr<CScene> buildScenePlanets(const Vec3f& bgColor, const Size resolution)
{
	auto pScene	= std::make_shared<CScene>(bgColor);
	
	// textures
	auto pTextureMercury	= std::make_shared<CTexture>(dataPath + "1_mercury_8k.jpg");
	auto pTextureVenus		= std::make_shared<CTexture>(dataPath + "1_venus_4k.jpg");
	auto pTextureEarth  	= std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureMars		= std::make_shared<CTexture>(dataPath + "1_mars_8k.jpg");
	auto pTextureJupiter	= std::make_shared<CTexture>(dataPath + "1_jupiter_8k.jpg");
	auto pTextureNeptune	= std::make_shared<CTexture>(dataPath + "1_neptune_2k.jpg");

	// shaders
	auto pShaderFloor		= std::make_shared<CShaderPhong>(*pScene, std::make_shared<CTexture>()/*RGB(0.522f, 0.6f, 0.7f)*/, 0.0f, 1.0f, 0.0f, 40.0f);
	auto pShaderMercury		= std::make_shared<CShaderPhong>(*pScene, pTextureMercury, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderVenus		= std::make_shared<CShaderPhong>(*pScene, pTextureVenus, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderEarth 		= std::make_shared<CShaderPhong>(*pScene, pTextureEarth, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderMars 		= std::make_shared<CShaderPhong>(*pScene, pTextureMars, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderJupiter 	= std::make_shared<CShaderPhong>(*pScene, pTextureJupiter, 0.3f, 1.2f, 0.0f, 40.0f);
	auto pShaderNeptune		= std::make_shared<CShaderPhong>(*pScene, pTextureNeptune, 0.3f, 1.2f, 0.0f, 40.0f);
	
	// primitives
	auto floor 				= std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0));
	auto mercury			= std::make_shared<CPrimSphere>(pShaderMercury, Vec3f(-3, 0.383f, -1), 0.383f);
	auto venus				= std::make_shared<CPrimSphere>(pShaderVenus, Vec3f(2.5f, 0.95f, 5), 0.95f);
	auto earth 				= std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(-3, 1.0f, -2.6f), 1);
	auto mars				= std::make_shared<CPrimSphere>(pShaderMars, Vec3f(-2.5f, 0.5321f, 1.5f), 0.5321f);
	auto jupiter			= std::make_shared<CPrimSphere>(pShaderJupiter, Vec3f(0, 3.3f, 0), 3.3f); // real r = 10.973f
	auto neptune			= std::make_shared<CPrimSphere>(pShaderNeptune, Vec3f(0, 3.8647f, 0), 3.8647f);

	// light
	auto pLight = std::make_shared<CLightSky>(Vec3f::all(1), 0);
	
	// camera
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-10, 5, 0), Vec3f(0,  1, 0), Vec3f(0, 1, 0), 40.0f);

	
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
	auto pScene	= std::make_shared<CScene>(bgColor);
	
	return pScene;
}

int main(int argc, char* argv[])
{
	const Vec3f	bgColor = RGB(0.75f, 0.75f, 0.75f);
	// const Size resolution(3072, 1920);
	const Size resolution(1920, 1200);

	auto pScene = buildScenePlanets(bgColor, resolution);
	
	pScene->buildAccelStructure(0, 3);
	
	Timer::start("Rendering... ");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(4, true, true));
	Timer::stop();
	imshow("Render", img);
	waitKey();

	return 0;
}
