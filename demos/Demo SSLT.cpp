#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	CScene scene(Vec3f::all(0.1f));
	
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(1));
	auto pShaderFloor	= std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40);
	auto pShaderSSLT 	= std::make_shared<CShaderPhong>(scene, RGB(0.153f, 0.682f, 0.376f), 0.1f, 0.9f, 0.5f, 40);	// Your new shader
	
	float s = 500;
	//Floor
	scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
	
	// Stanford Dragon
	CSolid dragon(pShaderSSLT, "..\\..\\data\\Stanford Dragon.obj");
	CTransform t;
	dragon.transform(t.scale(2.01f).get());
	scene.add(dragon);
	
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(Size(640, 480), Vec3f(0, 20, 40), Vec3f(0, 10, 0), Vec3f(0, 1, 0), 45.0f);
	auto pLightPoint = std::make_shared<CLightPoint>(RGB(1000, 1000, 1000), Vec3f(40, 40, 0));
	auto pLightSpot = std::make_shared<CLightSpotDirected>(RGB(5000, 5000, 5000), Vec3f(0, 100, 0), Vec3f(0, 0, 0), 15.0f, 30.0f);
	scene.add(pCamera);
	if (false) scene.add(pLightPoint);
	else scene.add(pLightSpot);



#ifdef ENABLE_BSP
	scene.buildAccelStructure();
#endif

	Mat img = scene.render(std::make_shared<CSamplerStratified>(2));
	imshow("image", img);
	waitKey();
	//imwrite("out1.jpg", img);
	return 0;
}
