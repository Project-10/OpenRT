#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	const Vec3f	bgColor = RGB(0, 0, 0);
	
	CScene scene(bgColor);
																			
	// Geometry
	scene.addPlane(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 50.0f);
	scene.addSphere(Vec3f(0, 0.5f, 0), 0.5f);

	const float r = 4;
	auto pCamera	= std::make_shared<CCameraPerspectiveTarget>(Size(640, 480), Vec3f(4, 4, 4), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 45.0f);
	auto pLightRed	= false ? 
		std::make_shared<CLightOmni>(20 * RGB(255, 0, 0), Vec3f(r, 3, 0)) : 
		std::make_shared<CLightSpotTarget>(20 * RGB(255, 0, 0), Vec3f(r, 3, 0), Vec3f(0, 0, 0), 20.0f, 10.0f);
	auto pLightGreen = false ?
		std::make_shared<CLightOmni>(20 * RGB(0, 255, 0), Vec3f(r, 3, 0)) :
		std::make_shared<CLightSpotTarget>(20 * RGB(0, 255, 0), Vec3f(r, 3, 0), Vec3f(0, 0, 0), 20.0f, 10.0f);
	auto pLightBlue = false ?
		std::make_shared<CLightOmni>(20 * RGB(0, 0, 255), Vec3f(0, 3, r)) :
		std::make_shared<CLightSpotTarget>(20 * RGB(0, 0, 255), Vec3f(0, 3, r), Vec3f(0, 0, 0), 20.0f, 10.0f);


	scene.add(pCamera);
	scene.add(pLightRed);
	scene.add(pLightBlue);
	scene.add(pLightGreen);
	
#ifdef ENABLE_BSP
	scene.buildAccelStructure(0, 0);
#endif
	Timer::start("Rendering 1 frame... ");
	for (int i = 0; ; i++) {
		float x = r * sinf(i * Pif / 180);
		float z = r * cosf(i * Pif / 180);
		Vec3f org(x, 3, z);
		pLightRed->setOrigin(org);

		Mat img = scene.render(std::make_shared<CSamplerStratified>(1));
		imshow("image", img);
		auto key = waitKey(5);
		if (key == 27 || key == 'q') break;
		if (i % 60 == 0) {
			Timer::stop();
			Timer::start("Rendering 60 frames... ");
		}
	}
	return 0;
}
