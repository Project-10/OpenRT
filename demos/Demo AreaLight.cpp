#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main()
{
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size	resolution = Size(1920, 1200);
	const float intensity = 20;

	// Scene
	CScene scene(bgColor);
	
	// Shaders
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderBall	= std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.9f, 40.0f);
	auto pShaderGlass	= std::make_shared<CShaderGeneral>(scene, RGB(140, 166, 179), 0.0f, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderRed		= std::make_shared<CShaderFlat>(RGB(255, 0, 0));
	auto pShaderGreen	= std::make_shared<CShaderFlat>(RGB(0, 255, 0));
	auto pShaderBlue	= std::make_shared<CShaderFlat>(RGB(0, 0, 255));

	//Floor
	float s = 50;
	scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
	//Ball
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0.75f, 0), 0.75f));

	CSolidQuad 		areaLampRed(pShaderRed, Vec3f(0.5f, 0, 3.001f), Vec3f(-0.5f, 0, 3.001f), Vec3f(-0.5f, 10, 3.001f), Vec3f(0.5f, 10, 3.001f));
	CSolidQuad 		areaLampGreen(pShaderGreen, Vec3f(2.471f, 0, 1.771f), Vec3f(1.771f, 0, 2.471f), Vec3f(1.771f, 10, 2.471f), Vec3f(2.471f, 10, 1.771f));
	CSolidQuad 		areaLampBlue(pShaderBlue, Vec3f(3.001f, 0, -0.5f), Vec3f(3.001f, 0, 0.5f), Vec3f(3.001f, 10, 0.5f), Vec3f(3.001f, 10, -0.5f));

	scene.add(areaLampRed);
	scene.add(areaLampGreen);
	scene.add(areaLampBlue);

	// camera
	const float r = 4;
	auto pCamera		= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-4, 4, -4), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 45.0f);
	auto pLight			= std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 10, 0));
	auto pLightRed		= std::make_shared<CLightOmni>(intensity * RGB(255, 0, 0), Vec3f(0, 5, 3),  true);
	auto pLightGreen	= std::make_shared<CLightOmni>(intensity * RGB(0, 255, 0), Vec3f(2.12f, 5, 2.12f), true);
	auto pLightBlue		= std::make_shared<CLightOmni>(intensity * RGB(0, 0, 255), Vec3f(3, 5, 0), true);
	//auto pLightRed	= std::make_shared<CLightArea>(RGB(intensity, 0, 0 ), Vec3f(0.5f, 0, 3), Vec3f(-0.5f, 0, 3), Vec3f(-0.5f, 10, 3), Vec3f(0.5f, 10, 3), std::make_shared<CSamplerStratified>(1, false, false), false);
	//auto pLightGreen	= std::make_shared<CLightArea>(RGB(0, intensity, 0), Vec3f(2.47f, 0, 1.77f), Vec3f(1.77f, 0, 2.47f), Vec3f(1.77f, 10, 2.47f), Vec3f(2.47f, 10, 1.77f), std::make_shared<CSamplerStratified>(1, false, false));
	//auto pLightBlue	= std::make_shared<CLightArea>(RGB(0, 0, intensity), Vec3f(3, 0, -0.5f), Vec3f(3, 0, 0.5f), Vec3f(3, 10, 0.5f), Vec3f(3, 10, -0.5f), std::make_shared<CSamplerStratified>(1, false, false));
	
	scene.add(pCamera);
	//scene.add(pLight);
	scene.add(pLightRed);
	scene.add(pLightGreen);
	scene.add(pLightBlue);


	scene.buildAccelStructure(30, 3);

	Timer::start("Rendering... ");
	Mat img = scene.render(std::make_shared<CSamplerStratified>(1));
	Timer::stop();

	imshow("image", img);
	imwrite("D:\\arealight_1.png", img);
	waitKey();
	return 0;
}
