#include "openrt.h"
#include "core/timer.h"

#include <map>

using namespace rt;

int main(int argc, char* argv[])
{
    
	const std::map<int, Vec3f> Kelvin2RGB {
		{ 1000, RGB(255, 56, 0) },
		{ 1100, RGB(255, 71, 0) },
		{ 1200, RGB(255, 83, 0) },
		{ 1300, RGB(255, 93, 0) },
		{ 1400, RGB(255, 101, 0) },
		{ 1500, RGB(255, 109, 0) },
		{ 1600, RGB(255, 115, 0) },
		{ 1700, RGB(255, 121, 0) },
		{ 1800, RGB(255, 126, 0) },
		{ 1900, RGB(255, 131, 0) },
		{ 2000, RGB(255, 138, 18) },
		{ 2100, RGB(255, 142, 33) },
		{ 2200, RGB(255, 147, 44) },
		{ 2300, RGB(255, 152, 54) },
		{ 2400, RGB(255, 157, 63) },
		{ 2500, RGB(255, 161, 72) },
		{ 2600, RGB(255, 165, 79) },
		{ 2700, RGB(255, 169, 87) },
		{ 2800, RGB(255, 173, 94) },
		{ 2900, RGB(255, 177, 101) },
		{ 3000, RGB(255, 180, 107) },
		{ 3100, RGB(255, 184, 114) },
		{ 3200, RGB(255, 187, 120) },
		{ 3300, RGB(255, 190, 126) },
		{ 3400, RGB(255, 193, 132) },
		{ 3500, RGB(255, 196, 137) },
		{ 3600, RGB(255, 199, 143) },
		{ 3700, RGB(255, 201, 148) },
		{ 3800, RGB(255, 204, 153) },
		{ 3900, RGB(255, 206, 159) },
		{ 4000, RGB(255, 209, 163) },
		{ 4100, RGB(255, 211, 168) },
		{ 4200, RGB(255, 213, 173) },
		{ 4300, RGB(255, 215, 177) },
		{ 4400, RGB(255, 217, 182) },
		{ 4500, RGB(255, 219, 186) },
		{ 4600, RGB(255, 221, 190) },
		{ 4700, RGB(255, 223, 194) },
		{ 4800, RGB(255, 225, 198) },
		{ 4900, RGB(255, 227, 202) },
		{ 5000, RGB(255, 228, 206) },
		{ 5100, RGB(255, 230, 210) },
		{ 5200, RGB(255, 232, 213) },
		{ 5300, RGB(255, 233, 217) },
		{ 5400, RGB(255, 235, 220) },
		{ 5500, RGB(255, 236, 224) },
		{ 5600, RGB(255, 238, 227) },
		{ 5700, RGB(255, 239, 230) },
		{ 5800, RGB(255, 240, 233) },
		{ 5900, RGB(255, 242, 236) },
		{ 6000, RGB(255, 243, 239) },
		{ 6100, RGB(255, 244, 242) },
		{ 6200, RGB(255, 245, 245) },
		{ 6300, RGB(255, 246, 247) },
		{ 6400, RGB(255, 248, 251) },
		{ 6500, RGB(255, 249, 253) },
		{ 6600, RGB(254, 249, 255) },
		{ 6700, RGB(252, 247, 255) },
		{ 6800, RGB(249, 246, 255) },
		{ 6900, RGB(247, 245, 255) },
		{ 7000, RGB(245, 243, 255) },
		{ 7100, RGB(243, 242, 255) },
		{ 7200, RGB(240, 241, 255) },
		{ 7300, RGB(239, 240, 255) },
		{ 7400, RGB(237, 239, 255) },
		{ 7500, RGB(235, 238, 255) },
		{ 7600, RGB(233, 237, 255) },
		{ 7700, RGB(231, 236, 255) },
		{ 7800, RGB(230, 235, 255) },
		{ 7900, RGB(228, 234, 255) },
		{ 8000, RGB(227, 233, 255) },
		{ 8100, RGB(225, 232, 255) },
		{ 8200, RGB(224, 231, 255) },
		{ 8300, RGB(222, 230, 255) },
		{ 8400, RGB(221, 230, 255) },
		{ 8500, RGB(220, 229, 255) },
		{ 8600, RGB(218, 229, 255) },
		{ 8700, RGB(217, 227, 255) },
		{ 8800, RGB(216, 227, 255) },
		{ 8900, RGB(215, 226, 255) },
		{ 9000, RGB(214, 225, 255) },
		{ 9100, RGB(212, 225, 255) },
		{ 9200, RGB(211, 224, 255) },
		{ 9300, RGB(210, 223, 255) },
		{ 9400, RGB(209, 223, 255) },
		{ 9500, RGB(208, 222, 255) },
		{ 9600, RGB(207, 221, 255) },
		{ 9700, RGB(207, 221, 255) },
		{ 9800, RGB(206, 220, 255) },
		{ 9900, RGB(205, 220, 255) },
		{ 10000,  RGB(207, 218, 255) },
		{ 10100,  RGB(207, 218, 255) },
		{ 10200,  RGB(206, 217, 255) },
		{ 10300,  RGB(205, 217, 255) },
		{ 10400,  RGB(204, 216, 255) },
		{ 10500,  RGB(204, 216, 255) },
		{ 10600,  RGB(203, 215, 255) },
		{ 10700,  RGB(202, 215, 255) },
		{ 10800,  RGB(202, 214, 255) },
		{ 10900,  RGB(201, 214, 255) },
		{ 11000,  RGB(200, 213, 255) },
		{ 11100,  RGB(200, 213, 255) },
		{ 11200,  RGB(199, 212, 255) },
		{ 11300,  RGB(198, 212, 255) },
		{ 11400,  RGB(198, 212, 255) },
		{ 11500,  RGB(197, 211, 255) },
		{ 11600,  RGB(197, 211, 255) },
		{ 11700,  RGB(197, 210, 255) },
		{ 11800,  RGB(196, 210, 255) },
		{ 11900,  RGB(195, 210, 255) },
		{ 12000,  RGB(195, 209, 255) } 
	};
	
	
	const Vec3f    bgColor = RGB(204, 230, 255);
    const Size resolution(600, 600);
    CScene scene(bgColor);
    
    // matherials
    auto pShaderFloor    = std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderRed		= std::make_shared<CShaderPhong>(scene, RGB(255, 0, 0), 0.5f, 0.5f, 0.0f, 40.0f);

    CTransform t;
    CSolid room(pShaderFloor, dataPath + "room.obj");

    scene.add(room);

	
	scene.add(std::make_shared<CPrimSphere>(pShaderRed, Vec3f(37.00f, 107.0f, -55.50f), 0.5f));
	scene.add(std::make_shared<CPrimSphere>(pShaderRed, Vec3f(37.00f, 107.0f, -67.50f), 0.5f));
	scene.add(std::make_shared<CPrimSphere>(pShaderRed, Vec3f(37.00f, 107.0f, -79.50f), 0.5f));

    // lights
	scene.add(std::make_shared<CLightOmni>(2e2 * Kelvin2RGB.at(5500), Vec3f(-99.0f, 48.5f, -77.25f), true));
	//scene.add(std::make_shared<CLightOmni>(2e2 * Kelvin2RGB.at(5500), Vec3f(35.75f, 104.0f, -67.43f), true));


	scene.add(std::make_shared<CLightOmni>(Vec3f::all(1e3), Vec3f(-50, 100, 0), true));
	scene.add(std::make_shared<CLightOmni>(5e5 * Kelvin2RGB.at(4500), Vec3f(1000, 50, -500), true));
    scene.add(std::make_shared<CLightSky>(Vec3f::all(0.25f)));
    
    // cameras
    scene.add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(35, 65, -70), Vec3f(35.57f, 107.0f, -67.43f), Vec3f(1, 0, 0), 60.0f));
	scene.add(std::make_shared<CCameraEnvironment>(resolution, Vec3f(0, 60, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0)));
	scene.add(std::make_shared<CCameraStereoscopic>(resolution, Vec3f(0, 60, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0), 1, 1));
	scene.add(std::make_shared<CCameraStereoscopic>(resolution, Vec3f(0, 60, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0), 2, 1));

    scene.buildAccelStructure(20, 3);
      
    scene.setActiveCamera(0);

	Timer::start("Rendering Main... ");
	Mat img_main = scene.render(nullptr);
	Timer::stop();
	
	imshow("Main", img_main);

	//scene.setActiveCamera(2);
 //   
 //   Timer::start("Rendering Left... ");
 //   Mat img_left = scene.render(std::make_shared<CSamplerStratified>(4));
 //   Timer::stop();
 //   
 //   imshow("Left", img_left);

 //   scene.setActiveCamera(3);
 //   
 //   Timer::start("Rendering Right... ");
 //   Mat img_right = scene.render(std::make_shared<CSamplerStratified>(4));
 //   Timer::stop();
 //   
 //   imshow("Right", img_right);
 //   
    imwrite("D:\\renders\\img_main.jpg", img_main);
 //   imwrite("D:\\renders\\img_left.jpg", img_left);
 //   imwrite("D:\\renders\\img_right.jpg", img_right);

    waitKey();
    
    return 0;
}
