#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() 
{
	const Vec3f	bgColor = RGB(200, 200, 200);
	const Size	resolution = Size(800, 600);
	const float intensity = 15e3;

	// Scene
	CScene scene(bgColor);
	
	auto floor = scene.addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 50.0f);

	// Shaders
	auto pShaderDragon = std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.0f, 1.0f, 0.15f, 250.0f);
	auto pShaderGlass = std::make_shared<CShaderGeneral>(scene, RGB(140, 166, 179), 0.0f, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderShadow = std::make_shared<CShaderShadow>(scene);

	// Stanford Dragon
	CSolid dragon(pShaderDragon, dataPath + "Stanford Dragon.obj");
	CTransform t;
	dragon.transform(t.scale(2.01f).rotate(Vec3f(0, 1, 0), 45).get());
	scene.add(dragon);
	
	floor->setShader(pShaderShadow);

	// Camera
	float r = 35;
	auto pCamera	= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f::all(r), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
	auto pLightOmni	= std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(r, 2 * r, 0));
	auto pLightSky	= std::make_shared<CLightSky>(Vec3f::all(1.0f), 50.0f, std::make_shared<CSamplerStratified>(4));
	
	
	scene.add(pCamera);
	scene.add(pLightOmni);
//	scene.add(pLightSky);

	
	scene.buildAccelStructure(20, 3);
	
	Timer::start("Rendering... ");
	Mat img = scene.render(std::make_shared<CSamplerStratified>(4), 0);
	//Mat depth = scene.renderDepth(std::make_shared<CSamplerStratified>(4));
	//depth.convertTo(img, CV_8UC1);
	Timer::stop();

	imshow("image", img);
	imwrite("D:\\renders\\res phong.jpg", img);
	waitKey();
	return 0;
}
