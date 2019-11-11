#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main(int argc, char* argv[])
{
	const Size resolution(1000, 600);

	CScene scene(Vec3f::all(0.4f));

	auto pShaderTop  	= std::make_shared<CShaderPhong>(scene, RGB(0.90f, 0.75f, 0.70f), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderSide 	= std::make_shared<CShaderPhong>(scene, RGB(0.55f, 0.65f, 0.70f), 0.7f, 0.5f, 0.0f, 40);
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	
	// primitives
	//scene.add(std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0)));
	const float s = 100;
	scene.add(std::make_shared<CPrimTriangle>(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, -s)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderFloor, Vec3f(s, 0, s), Vec3f(-s, 0, s), Vec3f(s, 0, -s)));
	// --- cube ---
	scene.add(std::make_shared<CPrimTriangle>(pShaderTop,  Vec3f(1, 2, 1), Vec3f(-1, 2, 1), Vec3f(-1, 2, -1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderTop,  Vec3f(1, 2, 1), Vec3f(1, 2, -1), Vec3f(-1, 2, -1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(-1, 2, 1), Vec3f(-1, 0, 1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 0, 1), Vec3f(-1, 0, 1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 2, -1), Vec3f(1, 0, -1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 0, 1), Vec3f(1, 0, -1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(1, 2, -1), Vec3f(1, 0, -1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 0, -1), Vec3f(1, 0, -1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 2, 1), Vec3f(-1, 0, 1)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 0, -1), Vec3f(-1, 0, 1)));
	// --- ---- ---
	scene.add(std::make_shared<CPrimTriangle>(pShaderWhite, Vec3f(-10, 10.01f, -10), Vec3f(-10, 10.01f, 10), Vec3f(10, 10.01f, -10)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderWhite, Vec3f(10, 10.01f, 10), Vec3f(-10, 10.01f, 10), Vec3f(10, 10.01f, -10)));
	
//	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderMirror>(scene), Vec3f(0, 1, 0), 1));
	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderMirror>(scene), Vec3f(-2, 1, 2), 1));
	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderGlass>(scene), Vec3f(2, 1, -2), 1));

	// lights
	//scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(-10, 10, -10)));
	//scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(-10, 10, 10)));
	//scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(10, 10, 10)));
	//scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(10, 10, -10)));
	scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(0, 2, 10), false));
	scene.add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(2, true, true)));

	// camera
	const float r = 17.5f;
	Vec3f camPos(sqrt(r), sqrt(r), sqrt(r));
	scene.add(std::make_shared<CCameraPerspective>(camPos, normalize(Vec3f(0, 0.5f, 0) - camPos), Vec3f(0, 1, 0), 45, resolution));
	
#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif

	// render three images with different camera settings
	Timer::start("Rendering... ");
	Mat img1 = scene.render();
	Timer::stop();
	imshow("Image1", img1);
	imwrite("cube.jpg", img1);
	waitKey();
	return 0;
}


