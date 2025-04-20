#include "openrt.h"
#include "core/timer.h"
#include "core/random.h"

using namespace rt;

std::shared_ptr<CScene> buildSceneLightPoint(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);
	
	// Geometry
	//for (int i = 0; i < 10; i++)
	//	pScene->addSphere(Vec3f(random::u(-50, 50), random::u(-50, 50), random::u(-50,50)), 1));
	pScene->addSphere();

	// Light
	auto light = std::make_shared<CLightOmni>(Vec3f::all(1e5), Vec3f(0, 100, 0));
	pScene->add(light);
	
	// Camera
	auto camera = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 0, -100), Vec3f(0, 0, 1), Vec3f(0, 1, 0), 46.8f);
	pScene->add(std::make_shared<CCameraThinLens>(camera, 0.357f, 4.0f, 5));
	
	return pScene;
}

std::shared_ptr<CScene> buildSceneBalls(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);

	// Shaders
	auto pShaderFloor = std::make_shared<CShaderDiffuse>(*pScene, std::make_shared<CTexture>());
	auto pShaderBall = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 255), 0.1f, 0.9f, 4.0f, 120.0f);

	
	// Geometry
	auto floor = pScene->addPlane();
	floor->setShader(pShaderFloor);

	for (int i = -4; i <= 16; i += 2) {
		auto sphere = pScene->addSphere(Vec3f(0, 0.75f, i), 0.75f);
		sphere->setShader(pShaderBall);
	}

	std::cout << "dist: " << (norm(Vec3f(0, 0.75f, 0), Vec3f(-4, 4, -4))) << std::endl;

	// camera
	const float r = 4;
	auto pCamera		= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-2, 3, -4), Vec3f(0, 0.75f, 0), Vec3f(0, 1, 0), 45.0f);
	auto pCameraDoF		= std::make_shared<CCameraThinLens>(pCamera, 0.3f, 6.5f, 6);
	auto pLightOmni		= std::make_shared<CLightOmni>(Vec3f::all(1e4), Vec3f(0, 100, 40));
	auto pLightSky		= std::make_shared<CLightSky>(Vec3f::all(1), 0, std::make_shared<CSamplerStratified>(1, false));

	pScene->add(pCameraDoF);
	pScene->add(pLightOmni);
	
	return pScene;
}

int main()
{
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size	resolution = Size(640, 480);

	//auto pScene = buildSceneLightPoint(bgColor, resolution);
	auto pScene = buildSceneBalls(bgColor, resolution);

	pScene->buildAccelStructure(0, 0);
	
	Timer::start("Rendering... ");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(32), 64);
	Timer::stop();

	imshow("image", img);
	imwrite("D://Renders//dof.bmp", img);
	waitKey();
	return 0;	
}
