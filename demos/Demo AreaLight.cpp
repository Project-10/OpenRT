#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main(int argc, char* argv[])
{
	const Size resolution(800, 600);

	CScene scene(RGB(0.4f, 0.4f, 0.4f));

	auto txt_cb = std::make_shared<CTexture>();//"/Users/creator/Projects/OpenRT/data/tnf.jpg");
	
	
	auto pShaderTop  	= std::make_shared<CShaderPhong>(scene, RGB(0.90f, 0.75f, 0.70f), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderSide 	= std::make_shared<CShaderPhong>(scene, RGB(0.55f, 0.65f, 0.70f), 0.7f, 0.5f, 0.5f, 40);
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderFloor	= std::make_shared<CShaderFlat>(txt_cb);
	auto pShaderFloos	= std::make_shared<CShaderPhong>(scene, RGB(1, 0, 0), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderGlass	= std::make_shared<CShader>(scene, RGB(0.55f, 0.65f, 0.70f), 0, 0.1f, 2, 80, 0.2f, 0.8f, 1.5f);

	CSolid torus(pShaderFloor, "../../../data/Torus Knot.obj"); // "D:\\Projects\\OpenRT\\data\\Torus Knot.obj");

	// primitives
	const float s = 50;
	const float h = 0;
	auto			floor = std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, h, 0), normalize(Vec3f(0, 1.0f, 0)));
//	CSolidQuad 		floor(pShaderFloor, Vec3f(-s, h, -s), Vec3f(-s, h, s), Vec3f(s, h, s), Vec3f(s, h, -s));
//	CSolidQuad 		floos(pShaderFloos, Vec3f(0, h + 0.005f, -s), Vec3f(0, h + 0.005f, s), Vec3f(s, h + 0.005f, s), Vec3f(s, h + 0.005f, -s));
	
	auto			sphere = std::make_shared<CPrimSphere>(std::make_shared<CShaderMirror>(scene), Vec3f(0, 1, 0), 1);
	CSolidQuad 		areaLamp(pShaderWhite, Vec3f(-10, 10.01f, -10), Vec3f(10, 10.01f, -10), Vec3f(10, 10.01f, 10), Vec3f(-10, 10.01f, 10));
	CSolidBox  		glassbox(pShaderGlass, Vec3f(0, 1, 0), 0, 2, 6);
	CSolidBox  		cube1(pShaderTop, Vec3f(-2, 0, 2), 0.01f);
	CSolidBox  		cube2(pShaderSide, Vec3f(-2, 1, 2), 1);
	CSolidCone 		cone1(pShaderSide, Vec3f(0, 0, 0), 1, 2, 24, true);
	CSolidCone 		cone2(pShaderSide, Vec3f(0, 2, 0), 1, 2, 24, true);
	CSolidCylinder	cylinder(std::make_shared<CShaderMirror>(scene), Vec3f(0, 0.01f, 0), 0.01f, 2, 36, true);
	
	//floor->transform(CTransform().rotate(Vec3f(0, 1, 0), -Pif / 6).translate(0, -0.1f, 0).scale(1, -1, 1).get());
	sphere->transform(CTransform().rotate(Vec3f(0, 1, 0), -Pif / 6).translate(0, 0, 0).scale(2).get());
	torus.transform(CTransform().scale(2.0f).get());
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
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShader>(scene, RGB(0, 0.5f, 1), 0, 0, 1, 80, 0.2f, 0.8f, 2.4f, std::make_shared<CSamplerRandom>(3, true, 0.1f)), Vec3f(-2, 1, 2), 1));
	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShader>(scene, 0.35f, 0.65f, 1.517), Vec3f(2, 1, -2), 1));
	
	//scene.add(std::make_shared<CPrimSphere>(pShaderSide, Vec3f(2, 1, -2), 1));


	// lights
	//scene.add(std::make_shared<CLightPoint>(Vec3f(50, 50, 50), Vec3f(-10, 10, -10), true));
	//scene.add(std::make_shared<CLightPoint>(Vec3f(50, 50, 50), Vec3f(-10, 10, 10), true));
	//scene.add(std::make_shared<CLightPoint>(Vec3f(50, 50, 50), Vec3f(10, 10, 10), true));
	//scene.add(std::make_shared<CLightPoint>(Vec3f(50, 50, 50), Vec3f(10, 10, -10), true));
	scene.add(std::make_shared<CLightPoint>(Vec3f::all(50), Vec3f(0, 4, 10), false));
	//scene.add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(4, true, true)));


	// camera
	const float r = 17.5f;
	Vec3f camPos(sqrt(r), sqrt(r), sqrt(r));
	scene.add(std::make_shared<CCameraPerspective>(camPos, normalize(Vec3f(0, 0.5f, 0) - camPos), Vec3f(0, 1, 0), 45, resolution));
	scene.add(std::make_shared<CCameraPerspective>(Vec3f(0, 9.99f, 0), Vec3f(0, -1, 0), Vec3f(1, 0, 0), 45, resolution));
	scene.setActiveCamera(0);
	
#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif

	// render three images with different camera settings
	Timer::start("Rendering... ");
	Mat img = scene.render(); //std::make_shared<CSamplerStratified>(4, true, true));
	Mat depth = scene.renderDepth();
	Timer::stop();
	
	imshow("Image", img);
	imwrite("cube.jpg", img);
	
	depth.convertTo(depth, CV_8UC1, 10);
	//imshow("Depth", depth);
	imwrite("cube_depth.jpg", depth);
	
	waitKey();
	return 0;
}


