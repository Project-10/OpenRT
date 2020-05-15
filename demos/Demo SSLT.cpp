#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	CScene scene(Vec3f::all(0.0f));
	auto pShaderFloor = std::make_shared<CShaderFlat>(Vec3f::all(1));

	float s = 50;
	//Ball
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 1, 0), 0.5f));
	//Floor
	scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));


	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(Vec3f(4, 4, 4), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 45.0f, Size(640, 480));
	auto pLightPoint = std::make_shared<CLightPoint>(RGB(10, 10, 10), Vec3f(4, 4, 0));
	auto pLightSpot = std::make_shared<CLightSpotDirected>(RGB(10, 10, 10), Vec3f(4, 4, 0), Vec3f(0, 0, 0), 20.0f, 10.0f);
	scene.add(pCamera);
	if (false) scene.add(pLightPoint);
	else scene.add(pLightSpot);



#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif

	Mat img = scene.render(std::make_shared<CSamplerStratified>(2));
	imshow("image", img);
	waitKey();
	imwrite("out1.jpg", img);
	return 0;
}
