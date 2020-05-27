#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	CScene scene(Vec3f::all(0.0f));
	
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.5f, 0.5f, 0.0f, 40);
	auto pShaderSSLT 	= std::make_shared<CShaderFlat>(Vec3f::all(1));	// Your new shader
	
	float s = 50;
	//Floor
	//scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
	
	//Ball
	//scene.add(std::make_shared<CPrimSphere>(pShaderSSLT, Vec3f(0, 1, 0), 0.5f));
	
	// Tenerife House
	CSolid dragon(pShaderSSLT, "../../../data/stanford-dragon.obj");
	CTransform t;
	dragon.transform(t.scale(0.1f).get());
	scene.add(dragon);
	
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(Vec3f(4, 4, 4), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 45.0f, Size(640, 480));
	auto pLightPoint = std::make_shared<CLightPoint>(RGB(10, 10, 10), Vec3f(4, 4, 0));
	auto pLightSpot = std::make_shared<CLightSpotDirected>(RGB(10, 10, 10), Vec3f(4, 4, 0), Vec3f(0, 0, 0), 20.0f, 10.0f);
	scene.add(pCamera);
	if (false) scene.add(pLightPoint);
	else scene.add(pLightSpot);



#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif

	Mat img = scene.render(std::make_shared<CSamplerStratified>(1));
	imshow("image", img);
	waitKey();
	//imwrite("out1.jpg", img);
	return 0;
}
