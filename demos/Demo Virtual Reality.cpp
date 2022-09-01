#include "openrt.h"
#include "core/timer.h"
#include "core/tools.h"

using namespace rt;

int main(int argc, char* argv[])
{
	const Vec3f		bgColor = Tools::Kelvin2RGB.at(5500);
    const Size		resolution(1 * 1024, 1 * 512);
    CScene scene(bgColor);
    
    // matherials
    auto pShader = std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.1f, 0.9f, 0.0f, 40.0f);

	// For the room.obj - 118 world units correspond to 3 meters in real life.
	// The average inter-pupilary distance for an adult man is 64mm
	// Thus, monocular pupilary distance is 32mm = 1.258(6) world units
    CSolid room(pShader, dataPath + "room.obj");
    const float PD = 1.2587f;
	
	scene.add(room);
	

    // lights
	scene.add(std::make_shared<CLightOmni>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(-99.0f, 48.5f, -77.25f), true));
	
	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.8784f, 106.8566f, -79.4961f), Vec3f(0.8008f, -0.5920f, -0.0901f), 45.0f, 30.0f, true));
	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.4436f, 106.6100f, -67.3086f), Vec3f(0.7317f, -0.6783f, 0.0677f), 45.0f, 30.0f, true));
	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.2625f, 106.6325f, -55.6289f), Vec3f(0.6986f, -0.7030f, 0.1335f), 45.0f, 30.0f, true));

	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.8784f, 106.8566f, -16.4629f), Vec3f(0.8008f, -0.5920f, -0.0901f), 45.0f, 30.0f, true));
	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.4436f, 106.6100f, -4.2754f), Vec3f(0.7317f, -0.6783f, 0.0677f), 45.0f, 30.0f, true));
	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.2625f, 106.6325f, 7.4043f), Vec3f(0.6986f, -0.7030f, 0.1335f), 45.0f, 30.0f, true));

	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.8784f, 106.8566f, 46.5703f), Vec3f(0.8008f, -0.5920f, -0.0901f), 45.0f, 30.0f, true));
	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.4436f, 106.6100f, 58.7578f), Vec3f(0.7317f, -0.6783f, 0.0677f), 45.0f, 30.0f, true));
	scene.add(std::make_shared<CLightSpot>(2e2 * Tools::Kelvin2RGB.at(5500), Vec3f(36.2625f, 106.6325f, 70.4375f), Vec3f(0.6986f, -0.7030f, 0.1335f), 45.0f, 30.0f, true));

	scene.add(std::make_shared<CLightOmni>(5e2 * Tools::Kelvin2RGB.at(5500), Vec3f(-50, 100, 0), true));
	scene.add(std::make_shared<CLightOmni>(5e5 * Tools::Kelvin2RGB.at(4500), Vec3f(1000, 50, -500), true));
    scene.add(std::make_shared<CLightSky>(Vec3f::all(0.2f)));
    
    // cameras
	scene.add(std::make_shared<CCameraEnvironment>(resolution, Vec3f(0, 67, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0), -PD));	// left eye camera
	scene.add(std::make_shared<CCameraEnvironment>(resolution, Vec3f(0, 67, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0), PD));	// right eye camera

    scene.buildAccelStructure(20, 3);
      
	// Render left view first
	scene.setActiveCamera(0);
    
    Timer::start("Rendering Left... ");
    Mat img_left = scene.render(std::make_shared<CSamplerStratified>(1));
    Timer::stop();
    
	imshow("Left", img_left);
	waitKey(20);

	// Render right view next
    scene.setActiveCamera(1);
    
    Timer::start("Rendering Right... ");
    Mat img_right = scene.render(std::make_shared<CSamplerStratified>(1));
    Timer::stop();
    
    imshow("Right", img_right);
	waitKey(20);

	// Save combined stereo pair
	Mat img;
	vconcat(img_left, img_right, img);
	imshow("VR", img);
	imwrite("D:\\renders\\img_vr.jpg", img);

    waitKey();
    
    return 0;
}
