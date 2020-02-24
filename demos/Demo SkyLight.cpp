#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() {
	CScene scene(Vec3f::all(0.0f));

	auto pShader = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.0f, 0.9f, 0.0f, 0.0f);

	CSolid object(pShader, "C:\\Users\\GoraT\\Documents\\models\\haus_by_tk.obj");
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(Vec3f(-2, 3, 10), Vec3f(5, 5.5f, 0), Vec3f(0, 1, 0), 50.0f, Size(640, 480));
	auto pSkyLight = std::make_shared<CShaderAmbientOccluson>(scene,Vec3f(0, 0, 1));
	auto pLightPoint = std::make_shared<CLightPoint>(RGB(10, 10, 10), Vec3f(5, 3, 1));

	scene.add(object);
	scene.add(pSkyLight);
	//scene.add(pSkyLight);
	scene.add(pCamera);
	#ifdef ENABLE_BSP
		scene.buildAccelStructure();
	#endif

	Mat img = scene.render(std::make_shared<CSamplerStratified>(2));
	imshow("image", img);
	waitKey();
	imwrite("out1.jpg", img);

	return 0;
}