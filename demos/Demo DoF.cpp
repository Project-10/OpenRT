#include "openrt.h"
#include "core/timer.h"
#include "core/random.h"

using namespace rt;

int main()
{
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size	resolution = Size(500, 500);
	const float intensity = 20;

	// Scene
	CScene scene(bgColor);

	// Shaders
	auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderBall = std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.9f, 40.0f);
	auto pShaderGlass = std::make_shared<CShaderGeneral>(scene, RGB(140, 166, 179), 0.0f, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderRed = std::make_shared<CShaderFlat>(RGB(255, 0, 0));
	auto pShaderGreen = std::make_shared<CShaderFlat>(RGB(0, 255, 0));
	auto pShaderBlue = std::make_shared<CShaderFlat>(RGB(0, 0, 255));

	//Floor
	float s = 50;
	scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
	//Ball
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0.75f, -4), 0.75f));
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0.75f, -2), 0.75f));
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0.75f, 0), 0.75f));
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0.75f, 2), 0.75f));
	scene.add(std::make_shared<CPrimSphere>(pShaderBall, Vec3f(0, 0.75f, 4), 0.75f));


	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(1, 0, 0)), Vec3f(1, 1.f, 1), 0.4f));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(0, 1, 0)), Vec3f(0, 0.f, -2), 0.4f));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(0, 1, 0)), Vec3f(-1, -1.5f, 1), 0.4f));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(0, 0, 1)), Vec3f(1, 1.f, -1), 0.4f));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(0, 0, 1)), Vec3f(1, 2.f, 2), 0.4f));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(0, 0, 1)), Vec3f(1, -2.f, 3), 0.4f));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(1, 1, 0)), Vec3f(0, -0.75f, 0), 0.4f));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(0, 1, 1)), Vec3f(-1, 2.f, 1), 0.4f)); 
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(1, 1, 0)), Vec3f(-1, 1.f, -3), 0.4f)); 
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderFlat>(RGB(1, 0, 0)), Vec3f(0, -4.f, -1), 0.4f));
	//std::cout << "dist: " << (norm(Vec3f(0, 0.75f, 0), Vec3f(-4, 4, -4))) << std::endl;


	// camera
	const float r = 4;
	auto pCamera = std::make_shared<CCameraThinLens>(resolution, Vec3f(-4, 4, -4), Vec3f(0.601317, -0.526152, 0.601317), Vec3f(0, 1, 0), 45.0f, 0.2f, 6, 4);
	//auto pCamera = std::make_shared<CCameraThinLens>(resolution, Vec3f(-4, 4, -4), Vec3f(0.601317, -0.526152, 0.601317), Vec3f(0, 1, 0), 45.0f, 1.0f, 20, 5);
	//auto pCamera = std::make_shared<CCameraThinLens>(resolution, Vec3f(-4, 2, 0), Vec3f(1, 0, 0), Vec3f(0, 1, 0), 45.0f, 0, 4, 4);
	//auto pCamera = std::make_shared<CCameraThinLens>(resolution, Vec3f(-4, 2, 0), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 45.0f, 0.3f, 4, 4);
	auto pLight = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(-10, 10, 0));
	auto pLightRed = std::make_shared<CLightOmni>(Vec3f(0, 0, intensity), Vec3f(0, 5, 3), true);
	auto pLightGreen = std::make_shared<CLightOmni>(Vec3f(0, intensity, 0), Vec3f(2.12f, 5, 2.12f), true);
	auto pLightBlue = std::make_shared<CLightOmni>(Vec3f(intensity, 0, 0), Vec3f(3, 5, 0), true);
	//auto pLightRed	= std::make_shared<CLightArea>(RGB(intensity, 0, 0 ), Vec3f(0.5f, 0, 3), Vec3f(-0.5f, 0, 3), Vec3f(-0.5f, 10, 3), Vec3f(0.5f, 10, 3), std::make_shared<CSamplerStratified>(1, false, false), false);
	//auto pLightGreen	= std::make_shared<CLightArea>(RGB(0, intensity, 0), Vec3f(2.47f, 0, 1.77f), Vec3f(1.77f, 0, 2.47f), Vec3f(1.77f, 10, 2.47f), Vec3f(2.47f, 10, 1.77f), std::make_shared<CSamplerStratified>(1, false, false));
	//auto pLightBlue	= std::make_shared<CLightArea>(RGB(0, 0, intensity), Vec3f(3, 0, -0.5f), Vec3f(3, 0, 0.5f), Vec3f(3, 10, 0.5f), Vec3f(3, 10, -0.5f), std::make_shared<CSamplerStratified>(1, false, false));

	scene.add(pCamera);
	scene.add(pLight);
	scene.add(pLightRed);
	scene.add(pLightGreen);
	scene.add(pLightBlue);


	scene.buildAccelStructure(30, 3);

	Timer::start("Rendering... ");
	//std::make_shared<CSamplerStratified>(1)
	Mat img = scene.render(nullptr, 0.001f, 16);
	//Mat img = scene.render(std::make_shared<CSamplerRandom>(4));
	Timer::stop();

	imshow("image", img);
	imwrite("D:\\arealight_1.png", img);
	waitKey();
	return 0;
}


/*
void foo() {
	auto txt_cb = std::make_shared<CTexture>("../../data/tnf.jpg");
	auto pShaderTop  	= std::make_shared<CShaderPhong>(scene, RGB(0.90f, 0.75f, 0.70f), 0.5f, 0.5f, 0.0f, 40.0f);
	auto pShaderSide 	= std::make_shared<CShaderPhong>(scene, RGB(0.55f, 0.65f, 0.70f), 0.7f, 0.5f, 0.5f, 40.0f);
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderFloos	= std::make_shared<CShaderPhong>(scene, RGB(1, 0, 0), 0.5f, 0.5f, 0.0f, 40.0f);
	auto pShaderGlass	= std::make_shared<CShaderGeneral>(scene, RGB(0.55f, 0.65f, 0.70f), 0, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderTxt		= std::make_shared<CShaderFlat>(txt_cb);
	//CSolid torus(pShaderFloor, "../../data/Torus Knot.obj"); // "D:\\Projects\\OpenRT\\data\\Torus Knot.obj");
	auto			sphere = std::make_shared<CPrimSphere>(pShaderTxt, Vec3f(0, 1, 0), 1);
	CSolidQuad 		areaLamp(pShaderWhite, Vec3f(-10, 10.01f, -10), Vec3f(10, 10.01f, -10), Vec3f(10, 10.01f, 10), Vec3f(-10, 10.01f, 10));
	CSolidBox  		glassbox(pShaderGlass, Vec3f(0, 1, 0), 0, 2, 6);
	CSolidBox  		cube1(pShaderTop, Vec3f(-2, 0, 2), 0.01f);
	CSolidBox  		cube2(pShaderSide, Vec3f(-2, 1, 2), 1);
	CSolidCone 		cone1(pShaderSide, Vec3f(0, 0, 0), 1, 2, 24, true);
	CSolidCone 		cone2(pShaderSide, Vec3f(0, 2, 0), 1, 2, 24, true);
	CSolidCylinder	cylinder(std::make_shared<CShaderMirror>(scene), Vec3f(0, 0.01f, 0), 0.01f, 2, 36, true);
	//floor->transform(CTransform().rotate(Vec3f(0, 1, 0), -Pif / 6).translate(0, -0.1f, 0).scale(1, -1, 1).get());
	//sphere->transform(CTransform().rotate(Vec3f(0, 1, 0), -Pif / 6).translate(0, 0, 0).scale(2).get());
	//torus.transform(CTransform().scale(2.0f).get());
	//cone1.transform(CTransform().rotate(Vec3f(0, 1, 0), Pif / 2).scale(2, -2.5f, 4).get());
	//cone2.transform(CTransform().scale(1, -1, 1).get());
	//cylinder.transform(CTransform().rotate(Vec3f(1, 0, 0), Pif/2).translate(0, 1, 0).get());
	//Mat t = CTransform().scale(100).rotate(normalize(Vec3f(1, 0, 1)), Pif / 3.289f).translate(Vec3f(0, sqrtf(3), 0)).get();
	// std::cout << "transform matrix:" << std::endl << t << std::endl;
	//cube1.transform(t);
	//cube1.transform(t.rotate(normalize(Vec3f(1, 0, 1)), Pif / 3.289f).translate(Vec3f(2, 0.75f * sqrtf(3) - 1, -2)).scale(0.75f).get());
	//cone.transform(CTransform().scale(Vec3f(2, 0.5f, 1)).reflectY().translate(0, -2, 0).get());
	scene.add(floor);
	//scene.add(floos);
	//scene.add(glassbox);
	//scene.add(cube1);
	//scene.add(cube2);
	//scene.add(torus);
	//scene.add(cone1);
	//scene.add(cone2);
	//scene.add(cylinder);
	scene.add(sphere);
	scene.add(areaLamp);
	//scene.add(std::make_shared<CPrimSphere>(pShaderTop, Vec3f(-2, 1, 2), 1));
	//scene.add(CSolidBox(pShaderTop, Vec3f(-2, 0.9f, 2), 0.9f));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderGeneral>(scene, RGB(0, 0.5f, 1), 0.0f, 0.0f, 1.0f, 80.0f, 0.2f, 0.8f, 2.4f, std::make_shared<CSamplerRandom>(3, true, 0.1f)), Vec3f(-2, 1, 2), 1));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderGeneral>(scene, 0.35f, 0.65f, 1.517), Vec3f(2, 1, -2), 1));

	//scene.add(std::make_shared<CPrimSphere>(pShaderSide, Vec3f(2, 1, -2), 1));
	// lights
	//scene.add(std::make_shared<CLightOmni>(Vec3f(50, 50, 50), Vec3f(-10, 10, -10), true));
	//scene.add(std::make_shared<CLightOmni>(Vec3f(50, 50, 50), Vec3f(-10, 10, 10), true));
	//scene.add(std::make_shared<CLightOmni>(Vec3f(50, 50, 50), Vec3f(10, 10, 10), true));
	//scene.add(std::make_shared<CLightOmni>(Vec3f(50, 50, 50), Vec3f(10, 10, -10), true));
	//scene.add(std::make_shared<CLightOmni>(Vec3f::all(50), Vec3f(0, 4, 10), false));
	scene.add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(4, true, true)));
}*/

/*
	for (int i = 0; i < 200; i++) {

		float r1 = random::U(-10.0, 10.0);
		float r2 = random::U(-10., 10.);
		auto a = Vec3f(1.771f, 0, 1.);
		auto b = Vec3f(1.771f, 0, 1.5);
		auto c = Vec3f(1.771f, 1, 2);
		auto d = Vec3f(1.771f, 1, 1.5);
		a[1] += r1;
		a[2] += r2;
		b[1] += r1;
		b[2] += r2;
		c[1] += r1;
		c[2] += r2;
		d[1] += r1;
		d[2] += r2;
		scene.add(CSolidQuad(std::make_shared<CShaderFlat>(RGB(r2, r1, 0)), a, b, c, d));
	}
 */