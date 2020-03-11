#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	CScene scene(Vec3f::all(0.0f));
	auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderBall = std::make_shared<CShaderPhong>(scene, RGB(1, 0.8f, 0.6f), 0.1f, 0.9f, 0.9f, 40.0f);
	auto pShaderL = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.9f, 0.4f, 0.9f, 1.0f);
	float s = 3;
	//Ball
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0.5, 0), 1.5f));
	//Floor
	scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(Vec3f(4, 4, 4), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 45.0f, Size(720, 720));
	scene.add(std::make_shared<CLightPoint>(RGB(10, 10, 10), Vec3f(4, 4, 0)));

	auto pSkyLight = std::make_shared<CShaderAmbientOccluson>(scene, Vec3f(1, -1, 1), 0.7, 100);
	scene.add(pCamera);
	scene.add(pSkyLight);

	#ifdef ENABLE_BSP
		scene.buildAccelStructure();
	#endif

	Mat img = scene.render(std::make_shared<CSamplerStratified>(2));
	imshow("image", img);
	waitKey();
	imwrite("out.png", img);

	return 0;
}