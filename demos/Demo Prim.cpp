#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main(int argc, char* argv[])
{
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size resolution(640, 480);

	CScene scene(bgColor);

	// textures
	auto pTextureEarth  = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureB13	= std::make_shared<CTexture>(dataPath + "b13.jpg");

	// matherials
	auto pShaderTop  	= std::make_shared<CShaderPhong>(scene, RGB(0.90f, 0.75f, 0.70f), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderSide 	= std::make_shared<CShaderPhong>(scene, RGB(0.55f, 0.65f, 0.70f), 0.7f, 0.5f, 0.0f, 40);
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderEarth 	= std::make_shared<CShaderPhong>(scene, pTextureEarth, 0.2f, 0.7f, 0.0f, 40);
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderChrome	= std::make_shared<CShaderChrome>(scene, std::make_shared<CSamplerStratified>(4, true, true));
	auto pShaderGlass	= std::make_shared<CShader>(scene, RGB(0.55f, 0.65f, 0.70f), 0, 0.1f, 2, 80, 0.2f, 0.8f, 1.5f);

	// primitives
	auto floor = std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0));
	scene.add(floor);
/*	float s = 100;
	scene.add(std::make_shared<CPrimTriangle>(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, -s)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderFloor, Vec3f(s, 0, s), Vec3f(-s, 0, s), Vec3f(s, 0, -s)))*/;


	float s = 10;
	scene.add(std::make_shared<CPrimTriangle>(pShaderWhite, Vec3f(-s, 10.1f, -s), Vec3f(-s, 10.1f, s), Vec3f(s, 10.1f, -s)));
	scene.add(std::make_shared<CPrimTriangle>(pShaderWhite, Vec3f(s, 10.1f, s), Vec3f(-s, 10.1f, s), Vec3f(s, 10.1f, -s)));

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
	
	CTransform t;

	// --- B13 ---
	auto b13 = std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(1, 0, 0), 0.2f, 0.5f, 1.0f, 80), Vec3f(-3, 1, -1), 1);
	scene.add(std::make_shared<CPrimSphere>(pShaderTop, Vec3f::all(0), 50));
	scene.add(std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(0, 1.0f, 0), 1));
	scene.add(b13);
	auto earth		= std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0, 0), 4);
	auto cylinder	= CSolidCylinder(pShaderEarth, Vec3f(0, 0, 0), 4, 4, 5, 36, true);
	auto cone		= CSolidCone(pShaderEarth, Vec3f(0, 0, 0), 4, 5, 5, 24, true);
//	auto cube		= CSolidBox(pShaderFloorTxt, Vec3f(0, 1, 0), 1);
	//cylinder.transform(CTransform().reflectY().reflectX().get());
//	scene.add(earth);
//	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(0, 0, 1),   0.2f, 0.5f, 0.5f, 40), Vec3f(2, 1.8f, -3), 2));
//	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderPhong>(scene, RGB(0, 1, 1), 0.2f, 0.5f, 0.5f, 40), Vec3f(-3, 4.7f, -1), Vec3f(0, 3, 0), Vec3f(2, 3.8f, -3)));
//	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.2f, 0.5f, 0.5f, 40), Vec3f(2, 3, 2), Vec3f(2, 3, -4), Vec3f(-4, 3, -4)));

	// lights
	scene.add(std::make_shared<CLightOmni>(Vec3f::all(30), Vec3f(-4, 6, 3), true));
	scene.add(std::make_shared<CLightOmni>(Vec3f::all(30), Vec3f(0, 10, 0), true));
//	scene.add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(4, true, true)));

	// camera	
	const float r = 10;
	auto mainCam = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 0, r), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 60);
	scene.add(mainCam);
	scene.add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-8, 3, 8), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 45));
	scene.add(std::make_shared<CCameraPerspective>(resolution, Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45));
	
	scene.setActiveCamera(1);

	scene.buildAccelStructure(0, 3);

	// One frame
	Timer::start("Rendering... ");
	Mat img = scene.render(std::make_shared<CSamplerStratified>(4));
	Timer::stop();
	imshow("Image", img);
	imwrite("D:\\renders\\tr.jpg", img);
	waitKey();

	// Animation
	//Timer::start("Rendering 1 frame... ");
	//for (int i = 0; ; i++) {
	//	float x = r * sinf(i * Pif / 180);
	//	float z = r * cosf(i * Pif / 180);
	//	Vec3f pos(x, 5, z);
	//	mainCam->setPosition(pos);
	//	float angle = mainCam->getAngle();
	//	angle -= 0.1f;
	//	mainCam->setAngle(angle);

	//	Mat img = scene.render(std::make_shared<CSamplerStratified>(1));
	//	
	//	resize(img, img, Size(img.cols * 2, img.rows * 2), 0, 0, INTER_NEAREST);
	//	imshow("Image", img);
	//	auto key = waitKey(1);
	//	if (key == 27 || key == 'q') break;
	//	if (i % 60 == 0) {
	//		Timer::stop();
	//		Timer::start("Rendering 60 frames... ");
	//	}
	//	//floor->transform(CTransform().rotate(normalize(Vec3f(1, 0, 1)), 0.01f).get());
	//}

	return 0;
}
