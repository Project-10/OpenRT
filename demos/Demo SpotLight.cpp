#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main(int argc, char* argv) {
	CScene scene(Vec3f::all(0.0f));
																				//  a    d      s    e
	auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(2.5, 2.5, 2.5), 0.1f, 0.9f, 0.9f, 0.1f);
	auto pShaderBall = std::make_shared<CShaderPhong>(scene, RGB(3, 2.5 ,2), 0.1f, 0.4f, 0.9f, 0.0f);
	auto pShaderL = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.9f, 0.4f, 0.9f, 1.0f);
	

	float s = 10;
	//Ball
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(4, 4, 1), 0.5));
	//Floor
	scene.add(std::make_shared<CPrimTriangle>(pShaderFloor, Vec3f(0, s,0), Vec3f(s, s,0), Vec3f(0,0,0)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderFloor, Vec3f(0,0,0), Vec3f(s, 0,0), Vec3f(s, s,0)));
	//
	const float h = 3;
	auto pCamera = std::make_shared<CCameraPerspective>(Vec3f(6, 2, h), normalize(Vec3f(-1, 1.5, -2.5)), Vec3f(0, 1, 1), 70.0f, Size(400, 400));
	auto pLightSpot = std::make_shared<CLightSpot>(RGB(10, 10,10), Vec3f(4, 4, 7), normalize(Vec3f(0.5, 0, -3)), 13.0f, true);
	scene.add(std::make_shared<CPrimSphere>(pShaderL, Vec3f(3, 3, 10), 0.05));
	scene.add(pCamera);
	scene.add(pLightSpot);


#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif

	Mat img = scene.render(std::make_shared<CSamplerStratified>(2));
	imshow("image", img);
	waitKey();
	imwrite("out1.jpg", img);
	return 0;
}