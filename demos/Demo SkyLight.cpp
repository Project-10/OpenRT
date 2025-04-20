#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() 
{
	const Vec3f	bgColor = RGB(255, 255, 255);
	const Size	resolution = Size(800, 600);
	const float intensity = 1000;

	// Scene
	CScene scene(bgColor);
	
	scene.addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 50.0f);

	// Shaders
	auto pShaderDragon = std::make_shared<CShaderDiffuse>(scene, RGB(255, 255, 255));
	auto pShaderGlass = std::make_shared<CShaderGeneral>(scene, RGB(140, 166, 179), 0.0f, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);

	// Stanford Dragon
	CSolid dragon(pShaderDragon, dataPath + "Stanford Dragon.obj");
	CTransform t;
	dragon.transform(t.scale(2.01f).rotate(Vec3f(0, 1, 0), 45).get());
	scene.add(dragon);
	

	// Camera
	float r = 35;
	auto pCamera	= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f::all(r), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
	auto pLightOmni	= std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 2 * r, 0));
	auto pLightSky	= std::make_shared<CLightSky>(Vec3f::all(1.0f), 0, std::make_shared<CSamplerStratified>(4, true));
	
	
	scene.add(pCamera);
	scene.add(pLightOmni);
	//scene.add(pLightSky);

	
	scene.buildAccelStructure(20, 3);
	
	Timer::start("Rendering... ");
	Mat img = scene.render(std::make_shared<CSamplerStratified>(4, true), 64);
	//Mat depth = scene.renderDepth(std::make_shared<CSamplerStratified>(4, true));
	//depth.convertTo(img, CV_8UC1);
	Timer::stop();

	imshow("image", img);
	imwrite("D:\\renders\\res2.jpg", img);
	waitKey();
	return 0;
}
