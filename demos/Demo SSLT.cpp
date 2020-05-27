#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	CScene scene(Vec3f::all(0.0f));

	auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 5), 0.1f, 0.9f, 0.9f, 40.0f);
	auto pShaderWall = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 5), 0.1f, 0.9f, 0.9f, 40.0f);
	auto pShaderBall = std::make_shared<CShaderFlat>(RGB(0.5f,0.5f,0.5f));// , 0.1f, 0.5f, 0.2f, 40.0f);

	float s = 4;
	//Ball
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0, 1), 1));
	//Floor
	scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, s, 0), Vec3f(s, s, 0), Vec3f(s, -s, 0), Vec3f(-s, -s, 0)));
	//Walls
	scene.add(CSolidQuad(pShaderWall, Vec3f(-s, s, 0), Vec3f(s, s, 0), Vec3f(s, s, s), Vec3f(-s, s, s)));
	scene.add(CSolidQuad(pShaderWall, Vec3f(-s, s, 0), Vec3f(-s, -s, 0), Vec3f(-s, -s, s), Vec3f(-s, s, s)));
	scene.add(CSolidQuad(pShaderWall, Vec3f(s, s, 0), Vec3f(s, -s, 0), Vec3f(s, -s, s), Vec3f(s, s, s)));

	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(Vec3f(0, -8, 5), Vec3f(0, 0, 1), Vec3f(0, 0, 1), 50.0f, Size(640, 480));
	auto pLightPoint = std::make_shared<CLightPoint>(RGB(25, 25, 25), Vec3f(0, -20, 5));

	scene.add(pCamera);
	scene.add(pLightPoint);
	
#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif

	Mat img = scene.render(std::make_shared<CSamplerStratified>(2));
	imshow("Subsurface Scattering", img);
	waitKey();
	imwrite("SSLTout1.jpg", img);
	return 0;
}
