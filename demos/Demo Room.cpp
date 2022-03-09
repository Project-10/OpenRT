#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main(int argc, char* argv[])
{
    const Vec3f    bgColor = RGB(0.8f, 0.9f, 1.0f);
    const Size resolution(2048, 1024);
    CScene scene(bgColor);
    
    // matherials
    auto pShaderFloor    = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);

    CTransform t;
    CSolid room(pShaderFloor, dataPath + "room.obj");

    scene.add(room);

    scene.add(std::make_shared<CLightOmni>(Vec3f::all(1e3), Vec3f(-50, 100, 0), true));
    scene.add(std::make_shared<CLightOmni>(Vec3f::all(5e5), Vec3f(1000, 100, 250), true));
    scene.add(std::make_shared<CLightSky>(Vec3f::all(0.25f)));
    
    // cameras
    auto mainCam = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 60, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0), 90.0f);
    scene.add(mainCam);

	scene.add(std::make_shared<CCameraEnvironment>(resolution, Vec3f(0, 60, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0)));
	scene.add(std::make_shared<CCameraStereoscopic>(resolution, Vec3f(0, 60, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0), 1, 1));
	scene.add(std::make_shared<CCameraStereoscopic>(resolution, Vec3f(0, 60, 0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0), 2, 1));

    scene.buildAccelStructure(20, 3);
    
 //   scene.setActiveCamera(0);

	//Timer::start("Rendering Main... ");
	//Mat img_main = scene.render(std::make_shared<CSamplerStratified>(1));
	//Timer::stop();
	//
	//imshow("Main", img_main);

	scene.setActiveCamera(2);
    
    Timer::start("Rendering Left... ");
    Mat img_left = scene.render(std::make_shared<CSamplerStratified>(4));
    Timer::stop();
    
    imshow("Left", img_left);

    scene.setActiveCamera(3);
    
    Timer::start("Rendering Right... ");
    Mat img_right = scene.render(std::make_shared<CSamplerStratified>(4));
    Timer::stop();
    
    imshow("Right", img_right);
    
    imwrite("D:\\renders\\img_left.jpg", img_left);
    imwrite("D:\\renders\\img_right.jpg", img_right);

    waitKey();
    
    return 0;
}
