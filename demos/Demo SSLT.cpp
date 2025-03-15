#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	const Vec3f	bgColor = RGB(26, 26, 26);
	const Size	resolution = Size(800, 600);
	const float intensity = 5000;

	CScene scene(bgColor);
	
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderSSLT	= std::make_shared<CShaderSSLT>(scene, RGB(39, 174, 96), 0.2f);
	
	scene.add(CSolidQuad(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), Vec3f(0, 0, 1), 500));
	
	// Stanford Dragon
	CSolid dragon(pShaderSSLT, dataPath + "Stanford Dragon.obj");
	CTransform t;
	dragon.transform(t.scale(2.01f).get());
	scene.add(dragon);
	
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 20, 40), Vec3f(0, 10, 0), Vec3f(0, 1, 0), 45.0f);
	auto pLightPoint = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 0));
	auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(0, 100, 0), Vec3f(0, 0, 0), 15.0f, 30.0f);
	scene.add(pCamera);
	if (false) scene.add(pLightPoint);
	else scene.add(pLightSpot);

	scene.buildAccelStructure(25, 5);

	Timer::start("Rendering...");
	Mat img = scene.render(std::make_shared<CSamplerStratified>(2, true, true), 32);
	Timer::stop();
	imshow("image", img);
	waitKey();
	//imwrite("out1.jpg", img);
	return 0;
}
