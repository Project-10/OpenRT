#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main(int argc, char* argv[])
{
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size resolution(800, 600);

	CScene scene(bgColor);

	// textures
	auto pTextureEarth = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");

	// matherials
	auto pShaderTop  	= std::make_shared<CShaderPhong>(scene, RGB(0.90f, 0.75f, 0.70f), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderSide 	= std::make_shared<CShaderPhong>(scene, RGB(0.55f, 0.65f, 0.70f), 0.7f, 0.5f, 0.0f, 40);
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderEarth 	= std::make_shared<CShaderPhong>(scene, pTextureEarth, 0.2f, 0.7f, 0.0f, 40);
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	
	// primitives
//	auto floor = std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0));

	//scene.add(floor);
	//const float s = 100;
	//scene.add(std::make_shared<CPrimTriangle>(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, -s)));
	//scene.add(std::make_shared<CPrimTriangle>(pShaderFloor, Vec3f(s, 0, s), Vec3f(-s, 0, s), Vec3f(s, 0, -s)));
	// --- cube ---
//	scene.add(std::make_shared<CPrimTriangle>(pShaderTop,  Vec3f(1, 2, 1), Vec3f(-1, 2, 1), Vec3f(-1, 2, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderTop,  Vec3f(1, 2, 1), Vec3f(1, 2, -1), Vec3f(-1, 2, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(-1, 2, 1), Vec3f(-1, 0, 1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 0, 1), Vec3f(-1, 0, 1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 2, -1), Vec3f(1, 0, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(1, 2, 1), Vec3f(1, 0, 1), Vec3f(1, 0, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(1, 2, -1), Vec3f(1, 0, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 0, -1), Vec3f(1, 0, -1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 2, 1), Vec3f(-1, 0, 1)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderSide, Vec3f(-1, 2, -1), Vec3f(-1, 0, -1), Vec3f(-1, 0, 1)));
	// --- ---- ---
//	scene.add(std::make_shared<CPrimTriangle>(pShaderWhite, Vec3f(-10, 10.01f, -10), Vec3f(-10, 10.01f, 10), Vec3f(10, 10.01f, -10)));
//	scene.add(std::make_shared<CPrimTriangle>(pShaderWhite, Vec3f(10, 10.01f, 10), Vec3f(-10, 10.01f, 10), Vec3f(10, 10.01f, -10)));
	
//	scene.parseOBJ("/Users/creator/Projects/CG/eyden-tracer-03/data/cow.obj");
	
//	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderMirror>(scene), Vec3f(0, 1, 0), 2));
//	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(1, 0, 0), 0.2f, 0.5f, 0.5f, 40), Vec3f(-3, 2.7f, -1), 2));
	auto sphere		= std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0, 0), 4);
	auto cylinder	= CSolidCylinder(pShaderEarth, Vec3f(0, 0, 0), 4, 4, 5, 36, true);
	auto cone		= CSolidCone(pShaderEarth, Vec3f(0, 0, 0), 4, 5, 5, 24, true);
//	auto cube		= CSolidBox(pShaderFloorTxt, Vec3f(0, 1, 0), 1);
	//cylinder.transform(CTransform().reflectY().reflectX().get());
	scene.add(sphere);
//	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(0, 0, 1),   0.2f, 0.5f, 0.5f, 40), Vec3f(2, 1.8f, -3), 2));
//	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderPhong>(scene, RGB(0, 1, 1), 0.2f, 0.5f, 0.5f, 40), Vec3f(-3, 4.7f, -1), Vec3f(0, 3, 0), Vec3f(2, 3.8f, -3)));
//	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.2f, 0.5f, 0.5f, 40), Vec3f(2, 3, 2), Vec3f(2, 3, -4), Vec3f(-4, 3, -4)));

	// lights
	scene.add(std::make_shared<CLightOmni>(Vec3f::all(50), Vec3f(-4, 6, 3), false));
//	scene.add(std::make_shared<CLightOmni>(Vec3f::all(50), Vec3f(0, 10, 0), false));
//	scene.add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(10, true, true)));

	// camera	
	const float r = 10;
	auto mainCam = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 0, r), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 60);
	scene.add(mainCam);
	scene.add(std::make_shared<CCameraPerspective>(resolution, Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45));
	scene.add(std::make_shared<CCameraPerspective>(resolution, Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45));
	
	scene.setActiveCamera(0);
#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif
	Timer::start("Rendering 1 frame... ");
	for (int i = 0; ; i++) {
		float x = r * sinf(i * Pif / 180);
		float z = r * cosf(i * Pif / 180);
		Vec3f pos(x, 5, z);
		mainCam->setPosition(pos);
		float angle = mainCam->getAngle();
		angle -= 0.1f;
		mainCam->setAngle(angle);

		Mat img = scene.render(std::make_shared<CSamplerStratified>(1));
		imshow("Image", img);
		auto key = waitKey(5);
		if (key == 27 || key == 'q') break;
		if (i % 60 == 0) {
			Timer::stop();
			Timer::start("Rendering 60 frames... ");
		}
		//floor->transform(CTransform().rotate(normalize(Vec3f(1, 0, 1)), 0.01f).get());
	}

	// render three images with different camera settings
//	Timer::start("Rendering... ");
//	Mat img1 = scene.render();
//	Timer::stop();
//	imshow("Image1", img1);
//	imwrite("perspective1.jpg", img1);
	//
	//scene.setActiveCamera(1);
	//Mat img2 = RenderFrame(scene);
	//imshow("Image2", img2);
	//imwrite("perspective2.jpg", img2);
	//
	//scene.setActiveCamera(2);
	//Mat img3 = RenderFrame(scene);
	//imshow("Image3", img3);
	//imwrite("perspective3.jpg", img3);

	return 0;
}
