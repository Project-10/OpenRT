#include "openrt.h"
#include "core/timer.h"

using namespace rt;


std::shared_ptr<CScene> buildpSceneColorSphere(const Vec3f& bgColor, const Size resolution)
{
	auto pScene		= std::make_shared<CScene>(bgColor);
	auto pShader	= std::make_shared<CShaderBlinn>(*pScene, Vec3f::all(1), 0.1f, 0.9f, 0.0f, 0.0f);
	auto pPlane		= std::make_shared<CPrimPlane>(pShader, Vec3f::all(0), Vec3f(0, 1, 0));
	auto pSphere	= std::make_shared<CPrimSphere>(pShader, Vec3f::all(0), 1);
	auto pLight1	= std::make_shared<CLightOmni>(Vec3f(0, 0, 200), Vec3f(10, 10, 0), true);
	auto pLight2	= std::make_shared<CLightOmni>(Vec3f(0, 200, 0), Vec3f(-5, 10, 8.66f), true);
	auto pLight3	= std::make_shared<CLightOmni>(Vec3f(200, 0, 0), Vec3f(-5, 10, -8.66f), true);
	auto pCamera	= std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 10, 0), Vec3f(0, -1, 0), Vec3f(1, 0, 0), 30);

	pScene->add(pPlane);
	pScene->add(pSphere);
	pScene->add(pLight1);
	pScene->add(pLight2);
	pScene->add(pLight3);
	pScene->add(pCamera);

	return pScene;
}

std::shared_ptr<CScene> buildSceneMirrorSphere(const Vec3f& bgColor, const Size resolution)
{
	auto pScene			= std::make_shared<CScene>(bgColor);
	
	// texture
	auto pTextureRoom	= std::make_shared<CTexture>(dataPath + "room.jpg");

	// shaders
	auto pShaderFloor	= std::make_shared<CShaderBlinn>(*pScene, RGB(0.522f, 0.6f, 0.706f), 0.1f, 0.9f, 0.0f, 0.0f);
	auto pShaderMirror	= std::make_shared<CShader>(*pScene, Vec3f::all(0), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	auto pShaderTop		= std::make_shared<CShaderBlinn>(*pScene, RGB(0.90f, 0.75f, 0.70f), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderChrome	= std::make_shared<CShaderChrome>(*pScene, std::make_shared<CSamplerStratified>(4, true, true));
	auto pShaderRoom	= std::make_shared<CShaderFlat>(pTextureRoom);

	// geometry
	auto pFloor			= std::make_shared<CPrimDisc>(pShaderFloor, Vec3f::all(0), Vec3f(0, 1, 0), 100);
	auto pSphere1		= std::make_shared<CPrimSphere>(pShaderMirror, Vec3f(-2, 1, 0), 1);
	auto pSphere2		= std::make_shared<CPrimSphere>(pShaderTop, Vec3f(0, 1, 0), 1);
	auto pSphere3		= std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(2, 1, 0), 1);
	auto pSphereRoom	= std::make_shared<CPrimSphere>(pShaderRoom, Vec3f(2, 1, 0), 100);

	auto pLight			= std::make_shared<CLightSky>(Vec3f::all(1));
	auto pCamera		= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 5, 10), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 23);

	pScene->add(pFloor);
	pScene->add(pSphere1);
	pScene->add(pSphere2);
	pScene->add(pSphere3);
//	pScene->add(pSphereRoom);
	pScene->add(pLight);
	pScene->add(pCamera);

	return pScene;
}



int main(int argc, char* argv[])
{
	const Vec3f	bgColor = RGB(0.77f, 0.82f, 0.89f);
	const Size resolution(2 * 960, 2 * 600);

	//auto pScene = buildpSceneColorSphere(bgColor, resolution);
	auto pScene = buildSceneMirrorSphere(bgColor, resolution);
	
	pScene->buildAccelStructure(0, 3);
	
	Timer::start("Rendering...");
	Mat render = pScene->render(std::make_shared<CSamplerStratified>(4, true, true));
	Timer::stop();
	imshow("pScene", render);
	imwrite("D:\\renders\\3 spheres.png", render);
	waitKey();
	return 0;


	
	
	
	


	CScene scene(bgColor);

	// textures
	auto pTextureEarth  = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureB13	= std::make_shared<CTexture>(dataPath + "b13.jpg");

	// matherials
	auto pShaderTop  	= std::make_shared<CShaderBlinn>(scene, RGB(0.90f, 0.75f, 0.70f), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderSide 	= std::make_shared<CShaderBlinn>(scene, RGB(0.55f, 0.65f, 0.70f), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderFloor	= std::make_shared<CShaderBlinn>(scene, RGB(0.522f, 0.6f, 0.706f), 0.2f, 0.8f, 0.0f, 40.0f);
	auto pShaderEarth 	= std::make_shared<CShaderBlinn>(scene, pTextureEarth, 0.2f, 0.7f, 0.0f, 40.0f);
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderChrome	= std::make_shared<CShaderChrome>(scene, std::make_shared<CSamplerStratified>(4, true, true));
	auto pShaderGlass	= std::make_shared<CShader>(scene, RGB(0.55f, 0.65f, 0.70f), 0.0f, 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderMirror	= std::make_shared<CShader>(scene, RGB(0.55f, 0.65f, 0.70f), 0.0f, 0.1f, 2.0f, 80.0f, 1.0f, 0.0f, 1.5f);

	// primitives

	//scene.add(std::make_shared<CPrimPlane>(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0)););
	scene.add(CSolidQuad(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0), Vec3f(100, 0, 0)));


	// --- light panel ---
	scene.add(CSolidQuad(pShaderWhite, Vec3f(0, 10.01f, 0), Vec3f(0, -1, 0), Vec3f(10, 0, 0)));

	// --- cube ---
	scene.add(CSolidQuad(pShaderTop, Vec3f(0, 2, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0)));
	scene.add(CSolidQuad(pShaderSide, Vec3f(1 , 1, 0), Vec3f(1, 0, 0), Vec3f(0, 0, 1)));
	scene.add(CSolidQuad(pShaderSide, Vec3f(-1, 1, 0), Vec3f(1, 0, 0), Vec3f(0, 0, -1)));
	scene.add(CSolidQuad(pShaderSide, Vec3f(0, 1, 1), Vec3f(0, 0, 1), Vec3f(1, 0, 0)));
	scene.add(CSolidQuad(pShaderSide, Vec3f(0, 1, -1), Vec3f(0, 0, -1), Vec3f(-1, 0, 0)));
	// --- ---- ---
	
//	scene.parseOBJ("/Users/creator/Projects/CG/eyden-tracer-03/data/cow.obj");
	
	CTransform t;
	
	scene.add(std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(3, 1.0f, 0), 1));
	scene.add(std::make_shared<CPrimSphere>(pShaderChrome, Vec3f(-3, 1.0f, 0), 1));

	//scene.add(CSolidSphere(pShaderChrome, Vec3f(3, 1.0f, 0), 1, 24));
	//scene.add(CSolidSphere(pShaderChrome, Vec3f(-3, 1.0f, 0), 1, 24));	

	//scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderEyelight>(Vec3f::all(1)), Vec3f::all(0), 3.0f));
	auto earth		= std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0, 0), 4.0f);
	auto cylinder	= CSolidCylinder(pShaderEarth, Vec3f(0, 0, 0), 4, 4, 5, 36, true);
	auto cone		= CSolidCone(pShaderEarth, Vec3f(0, 0, 0), 4, 5, 5, 24, true);
//	auto cube		= CSolidBox(pShaderFloorTxt, Vec3f(0, 1, 0), 1);
	//cylinder.transform(CTransform().reflectY().reflectX().get());
//	scene.add(earth);
//	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderBlinn>(scene, RGB(0, 0, 1),   0.2f, 0.5f, 0.5f, 40.0f), Vec3f(2, 1.8f, -3), 2));
//	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderBlinn>(scene, RGB(0, 1, 1), 0.2f, 0.5f, 0.5f, 40.0f), Vec3f(-3, 4.7f, -1), Vec3f(0, 3, 0), Vec3f(2, 3.8f, -3)));
//	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderBlinn>(scene, RGB(1, 1, 1), 0.2f, 0.5f, 0.5f, 40.0f), Vec3f(2, 3, 2), Vec3f(2, 3, -4), Vec3f(-4, 3, -4)));

	// lights
	//scene.add(std::make_shared<CLightOmni>(Vec3f::all(30), Vec3f(-4, 6, 3), true));
	//scene.add(std::make_shared<CLightOmni>(Vec3f::all(30), Vec3f(0, 10, 0), true));
	scene.add(std::make_shared<CLightArea>(Vec3f::all(6), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(4, true, true)));

	// camera	
	const float r = 10;
	auto mainCam = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 0, r), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 60.0f);
	scene.add(mainCam);
	scene.add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-8, 8, 8), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 45.0f));
	scene.add(std::make_shared<CCameraOrthographicTarget>(resolution, Vec3f(-5, 5, 5), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 5.0f));
	scene.add(std::make_shared<CCameraPerspective>(resolution, Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45.0f));

	scene.buildAccelStructure(20, 3);

	// One frame
	Timer::start("Rendering camera 0... ");
	scene.setActiveCamera(0);
	Mat img_cam0 = scene.render(std::make_shared<CSamplerStratified>(4, true, true));
	Timer::stop();

	imshow("Camera 0", img_cam0);
	imwrite("D:\\renders\\cam 0 e5.png", img_cam0);
	waitKey(5);

	// -------
	Timer::start("Rendering camera 1... ");
	scene.setActiveCamera(1);
	Mat img_cam1 = scene.render(std::make_shared<CSamplerStratified>(4, true, true));
	Timer::stop();

	imshow("Camera 1", img_cam1);
	imwrite("D:\\renders\\cam 1 e5.png", img_cam1);
	waitKey(5);


	// -------
	Timer::start("Rendering camera 3... ");
	scene.setActiveCamera(3);
	Mat img_cam3 = scene.render(std::make_shared<CSamplerStratified>(4, true, true));
	Timer::stop();

	imshow("Camera 3", img_cam3);
	imwrite("D:\\renders\\cam 3 e5.png", img_cam3);
	waitKey(5);



	//scene.setActiveCamera(2);
	//Timer::start("Rendering... ");
	//Mat img_orth = scene.render(std::make_shared<CSamplerStratified>(4));
	//Timer::stop();
	//imshow("Orthographic", img_orth);
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
