#include "openrt.h"
#include "core/timer.h"

using namespace rt;

Mat RenderFrame(CScene& scene)
{
	Mat img(scene.getActiveCamera()->getResolution(), CV_32FC3); 	// image array
	
#ifdef ENABLE_PPL
	concurrency::parallel_for(0, img.rows, [&](int y) {
		Ray ray;
#else
	Ray ray;
	for (int y = 0; y < img.rows; y++) {
#endif
		for (int x = 0; x < img.cols; x++) {
			scene.getActiveCamera()->InitRay(x, y, ray);
			img.at<Vec3f>(y, x) = scene.rayTrace(ray);
		}
	}
#ifdef ENABLE_PPL
	);
#endif
	
	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[])
{
	const Size resolution(800, 600);

	CScene scene(Vec3f::all(0.4f));

	// primitives
	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(1, 0, 0),   0.2f, 0.5f, 0.5f, 40), Vec3f(-3, 2.7f, -1), 2));
	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(0, 1, 0),   0.2f, 0.5f, 0.5f, 40), Vec3f(0, 0, 0), 2));
	scene.add(std::make_shared<CPrimSphere>(std::make_shared<CShaderPhong>(scene, RGB(0, 0, 1),   0.2f, 0.5f, 0.5f, 40), Vec3f(2, 1.8f, -3), 2));
	scene.add(std::make_shared<CPrimPlane>(std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1),    0.2f, 0.5f, 0.5f, 40), Vec3f(0, 0, 0), Vec3f(0, 1, 0)));
	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderPhong>(scene, RGB(0, 1, 1), 0.2f, 0.5f, 0.5f, 40), Vec3f(-3, 4.7f, -1), Vec3f(0, 3, 0), Vec3f(2, 3.8f, -3)));
	scene.add(std::make_shared<CPrimTriangle>(std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.2f, 0.5f, 0.5f, 40), Vec3f(2, 3, 2), Vec3f(2, 3, -4), Vec3f(-4, 3, -4)));

	// lights
//	scene.add(std::make_shared<CLightPoint>(Vec3f::all(3000), Vec3f(0, 50, 0)));
//	scene.add(std::make_shared<CLightPoint>(Vec3f(50, 50, 50), Vec3f(-4, 6, 3)));
	scene.add(std::make_shared<CLightArea>(Vec3f(25, 25, 25), Vec3f(-5, 10, -5), Vec3f(5, 10, 5), Vec3f(5, 10, -5), Vec3f(-5, 10, 5)));

	// camera	
	const float r = 10.0f;
	auto mainCam = std::make_shared<CCameraPerspective>(Vec3f(0, 1, r), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60, resolution);
	scene.add(mainCam);
	scene.add(std::make_shared<CCameraPerspective>(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45, resolution));
	scene.add(std::make_shared<CCameraPerspective>(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(1, 1, 0), 45, resolution));
	
	scene.setActiveCamera(0);

	Timer::start("Rendering 1 frame... ");
	for (int i = 0; ; i++) {
		float x = r * sinf(i * Pif / 180);
		float z = r * cosf(i * Pif / 180);
		Vec3f pos(x, 1, z);
		Vec3f dir = normalize(Vec3f::all(0) - pos);
		mainCam->setPosition(pos);
		mainCam->setDirection(dir);
		Mat img = RenderFrame(scene);
		imshow("Image", img);
		auto key = waitKey(5);
		if (key > 0) break;
		if (i % 60 == 0) {
			Timer::stop();
			Timer::start("Rendering 60 frames... ");
		}
	}





	//// render three images with different camera settings
	//Timer::start("Rendering... ");
	//Mat img1 = RenderFrame(scene);
	//Timer::stop();
	//imshow("Image1", img1);
	//imwrite("perspective1.jpg", img1);
	//
	//scene.setActiveCamera(1);
	//Mat img2 = RenderFrame(scene);
	//imshow("Image2", img2);
	//imwrite("perspective2.jpg", img2);
	//
	//scene.setActiveCamera(2);
	//Mat img3 = RenderFrame(scene);
	//imshow("Image3", img3);
	//imwrite("perspective3.jpg", img3);

	//waitKey();
	return 0;
}
