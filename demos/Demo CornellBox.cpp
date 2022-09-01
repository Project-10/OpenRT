#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main()
{
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size	resolution = Size(1024, 1024);
	const float intensity = 5000;

	// Scene
	CScene scene(bgColor);
	
	// Camera
	auto pCamera = std::make_shared<CCameraPerspective>(resolution, Vec3f(278, 273, -800), Vec3f(0, 0, 1), Vec3f(0, 1, 0), 39.3f);
	
	// Shaders
	auto pShaderLight	= std::make_shared<CShaderFlat>(RGB(255, 255, 255));
	auto pShaderWhite	= std::make_shared<CShaderPhong>(scene, RGB(255, 255, 255), 0.2f, 0.8f, 0.0f, 0.0f);
	auto pShaderRed		= std::make_shared<CShaderPhong>(scene, RGB(255, 0, 0), 0.2f, 0.8f, 0.0f, 0.0f);
	auto pShaderGreen	= std::make_shared<CShaderPhong>(scene, RGB(0, 255, 0), 0.2f, 0.8f, 0.0f, 0.0f);
	auto pShader		= std::make_shared<CShaderGeneral>(scene, RGB(255, 255, 255), 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, std::make_shared<CSamplerStratified>(4, true, true));
	
	// Lights
	auto pLight			= std::make_shared<CLightArea>(intensity * RGB(255, 214, 126), Vec3f(343, 548.78f, 227), Vec3f(343, 548.78f, 332), Vec3f(213, 548.78f, 332), Vec3f(213, 548.78f, 227), std::make_shared<CSamplerStratified>(6, true, true));
	auto pLightGreen	= std::make_shared<CLightOmni>(20 * intensity * RGB(0, 255, 0), Vec3f(-1000, 400, 280), false);
	auto pLightRed		= std::make_shared<CLightOmni>(20 * intensity * RGB(255, 0, 0), Vec3f(1553.7f, 400, 280), false);
	
	// Blocks
	CSolidBox shortBlock(pShaderWhite, Vec3f(185.5f, 82.5f, 169), 165, 165, 168);
	CSolidBox tallBlock(pShaderWhite, Vec3f(368.5f, 165, 351.25f), 165, 330, 167);
	
	shortBlock.transform(CTransform().rotate(Vec3f(0, 1, 0), -16.7f).get());
	tallBlock.transform(CTransform().rotate(Vec3f(0, 1, 0), 17.1f).get());
	
	
	scene.add(pCamera);
	scene.add(pLight);
	scene.add(pLightGreen);
	scene.add(pLightRed);
	
	scene.add(CSolidQuad(pShaderWhite, Vec3f(552.8f, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 0, 559.2f), Vec3f(549.6f, 0, 559.2f)));					// floor
	scene.add(CSolidQuad(pShaderWhite, Vec3f(556, 548.8f, 0), Vec3f(556, 548.8f, 559.2f), Vec3f(0, 548.8f, 559.2f), Vec3f(0, 548.8f, 0)));		// ceiling
	scene.add(CSolidQuad(pShaderWhite, Vec3f(549.6f, 0, 559.2f), Vec3f(0, 0, 559.2f), Vec3f(0, 548.8f, 559.2f), Vec3f(556, 548.8f, 559.2f)));	// back wall
	scene.add(CSolidQuad(pShaderGreen, Vec3f(0, 0, 559.2f), Vec3f(0, 0, 0), Vec3f(0, 548.8f, 0), Vec3f(0, 548.8f, 559.2f)));					// right wall
	scene.add(CSolidQuad(pShaderRed, Vec3f(552.8f, 0, 0), Vec3f(549.6f, 0, 559.2f), Vec3f(556, 548.8f, 559.2f), Vec3f(556, 548.8f, 0)));		// left wall
	scene.add(CSolidQuad(pShaderLight, Vec3f(343, 548.79f, 227), Vec3f(343, 548.79f, 332), Vec3f(213, 548.79f, 332), Vec3f(213, 548.79f, 227)));// light
	
	scene.add(shortBlock);
	scene.add(tallBlock);
	
	scene.buildAccelStructure(0, 3);
	
	Timer::start("Rendering... ");
	Mat img = scene.render(std::make_shared<CSamplerStratified>(4, true, true));
	Timer::stop();
	imshow("image", img);
	imwrite("D:\\renders\\res.jpg", img);
	waitKey();
	return 0;
}

