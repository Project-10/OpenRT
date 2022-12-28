#include "openrt.h"
#include "core/timer.h"
#include "core/random.h"

using namespace rt;

std::shared_ptr<CScene> buildSceneLightPoint(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);
	auto pShaderWhite = std::make_shared<CShaderFlat>(Vec3f::all(10));
	auto pCamera = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 0, -4), Vec3f(0, 0, 1), Vec3f(0, 1, 0), 46.8f);
	pScene->add(std::make_shared<CCameraThinLens>(pCamera, 0.357f, 4.0f, 5));
	//for (int i = 0; i < 10; i++)
	//	scene.add(std::make_shared<CPrimSphere>(pShaderWhite, Vec3f(random::u<float>(-50, 50), random::u<float>(-50, 50), random::u<float>(0,100)), 1));
	pScene->add(std::make_shared<CPrimSphere>(pShaderWhite, Vec3f(0, 0, 100), 1));
	return pScene;
}

std::shared_ptr<CScene> buildSceneBalls(const Vec3f& bgColor, const Size resolution)
{
	const float intensity = 5e2;
	
	auto pScene = std::make_shared<CScene>(bgColor);
	
	// Shaders
	auto pTexture = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pShaderFloor = std::make_shared<CShaderPhong>(*pScene, pTexture, 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderBall = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 3.9f, 120.0f);
	
	//Floor
	float s = 50;
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
	//Ball
	for (int i = -4; i <= 16; i += 2)
		pScene->add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0.75f, i), 0.75f));
	
	std::cout << "dist: " << (norm(Vec3f(0, 0.75f, 0), Vec3f(-4, 4, -4))) << std::endl;

	// camera
	const float r = 4;
	auto pCamera		= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-2, 3, -4), Vec3f(0, 0.75f, 0), Vec3f(0, 1, 0), 45.0f);
	auto pCameraDoF		= std::make_shared<CCameraThinLens>(pCamera, 0.3f, 6.5f, 5);
	auto pLight			= std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 25, 0));
	auto pLightRed		= std::make_shared<CLightOmni>(intensity * RGB(255, 0, 0), Vec3f(0, 5, 3), true);
	auto pLightGreen	= std::make_shared<CLightOmni>(intensity * RGB(0, 255, 0), Vec3f(2.12f, 5, 2.12f), true);
	auto pLightBlue		= std::make_shared<CLightOmni>(intensity * RGB(0, 0, 255), Vec3f(3, 5, 0), true);

	pScene->add(pCameraDoF);
	//pScene->add(std::make_shared<CLightSky>(Vec3f::all(1), 0, std::make_shared<CSamplerStratified>(1, false, false)));
	pScene->add(pLight);
	//pScene->add(pLightRed);
	//pScene->add(pLightGreen);
	//pScene->add(pLightBlue);
	
	return pScene;
}

int main()
{
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size	resolution = Size(640, 480);

	//auto pScene = buildSceneLightPoint(bgColor, resolution);
	auto pScene = buildSceneBalls(bgColor, resolution);

	pScene->buildAccelStructure(20, 3);
	
	Timer::start("Rendering... ");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(16));
	Timer::stop();

	imshow("image", img);
	imwrite("D://Renders//dof.bmp", img);
	waitKey();
	return 0;	
}
