#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	const Vec3f col_white = RGB(255, 255, 255);
	const Vec3f col_jade = RGB(39, 174, 96);
	const Vec3f col_gold = RGB(255, 215, 0);

	const Vec3f	bgColor = 0 * RGB(255, 255, 255);
	//const Size	resolution = Size(800, 600);
	const Size	resolution = Size(3072, 1920);
	const float intensity = 5e3;

	CScene scene(bgColor);

	//scene.addDisc(Vec3f::all(0), Vec3f(0, 1, 0), 50.0f);

	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderSSLT	= std::make_shared<CShaderSubsurfaceScattering>(scene, col_white, std::make_shared<CSamplerStratified>(4, true, true));
	
	//auto disc = scene.addDisc(Vec3f(0, 15, -40.1f), Vec3f(0, 0, -1), 50.0f);
	//disc->setShader(pShaderWhite);

	// Stanford Dragon
	CSolid dragon(pShaderSSLT, dataPath + "Stanford Dragon.obj");
	CTransform t;
	dragon.transform(t.scale(2.01f).get());
	scene.add(dragon);
	
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 20, 40), Vec3f(0, 10, 0), Vec3f(0, 1, 0), 45.0f);
	auto pLightOmni = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 100, 0));
	auto pLightSpot = std::make_shared<CLightSpotTarget>(Vec3f::all(intensity), Vec3f(0, 100, 0), Vec3f(0, 0, 0), 15.0f, 30.0f);
	scene.add(pCamera);
	scene.add(std::make_shared<CLightOmni>(intensity * col_gold, Vec3f(-15, 1.5f, -40)));
	scene.add(std::make_shared<CLightSky>(Vec3f::all(0.2f), 0, std::make_shared<CSamplerStratified>(4, true, true)));
	//if (true) scene.add(pLightOmni);
	//else scene.add(pLightSpot);

	scene.buildAccelStructure(25, 5);

	Timer::start("Rendering...");
	Mat img = scene.render(std::make_shared<CSamplerStratified>(4, true, true), 64);
	Timer::stop();
	imshow("image", img);
	waitKey();
	imwrite("D:\\renders\\sslt.jpg", img);
	return 0;
}
