#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main(int argc, char* argv[]) {
	int samples = 10;
	if(argc == 2){
		std::istringstream iss(argv[1]);
		iss >> samples;
	}

	CScene scene(Vec3f::all(0.0f));
	
	// Shaders
	auto pShaderWhite = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);

	// Floor
	float s = 3;
	scene.add(CSolidQuad(pShaderWhite, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
	
	// Ball
	scene.add(std::make_shared<CPrimSphere>(pShaderWhite, Vec3f(0, 0.5, 0), 1.5f));
	
	// Camera
	scene.add(std::make_shared<CCameraPerspectiveTarget>(Vec3f(4, 4, 4), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 45.0f, Size(720, 720)));
	
	// Light 
//	scene.add(std::make_shared<CLightPoint>(RGB(10, 10, 10), Vec3f(4, 4, 0)));
	scene.add(std::make_shared<CLightSky>(RGB(1, 1, 1)));

//	auto pSkyLight = std::make_shared<CShaderAmbientOccluson>(scene, Vec3f(1, -1, 1), 0.7, samples);
//	scene.add(pSkyLight);

	#ifdef ENABLE_BSP
		scene.buildAccelStructure();
	#endif
	
	Timer::start("Rendering... ");
	PPM gi(scene);
	gi.render(std::make_shared<CSamplerStratified>(2));
	// Mat img = scene.render(std::make_shared<CSamplerStratified>(2));
	Timer::stop();

	// imshow("image", img);
	waitKey();
	//imwrite( std::to_string(samples) + "time" +std::to_string(delta.count()) +".png", img);

	return 0;
}