#include "openrt.h"
#include "core/timer.h"
#include "core/random.h"

using namespace rt;

static std::shared_ptr<CScene> buildpSceneColorSphere(const Vec3f& bgColor, const Size resolution)
{
	auto pScene		= std::make_shared<CScene>(bgColor);
	auto pLight1	= std::make_shared<CLightOmni>(Vec3f(0, 0, 600), Vec3f(10, 10, 0), true);
	auto pLight2	= std::make_shared<CLightOmni>(Vec3f(0, 600, 0), Vec3f(-5, 10, 8.66f), true);
	auto pLight3	= std::make_shared<CLightOmni>(Vec3f(600, 0, 0), Vec3f(-5, 10, -8.66f), true);
	auto pCamera	= std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 10, 0), Vec3f(0, -1, 0), Vec3f(1, 0, 0), 30.0f);

	pScene->addPlane();
	pScene->addSphere();
	pScene->add(pLight1);
	pScene->add(pLight2);
	pScene->add(pLight3);
	pScene->add(pCamera);

	return pScene;
}

static std::shared_ptr<CScene> buildSceneMirrorSphere(const Vec3f& bgColor, const Size resolution)
{
	auto pScene			= std::make_shared<CScene>(bgColor);
	
	// Geometry
	const float R		= 150.0f;		// The size of the world
	auto floor			= pScene->addPlane(Vec3f(0, 0, 0), Vec3f(0, 1, 0), RGB(133, 153, 180));
	//auto environment	= pScene->addSphere(Vec3f(0, 0, 0), R);
	auto sphere_center	= pScene->addSphere(Vec3f( 0, 1, 0), 1.0f, RGB(230, 191, 179));
	auto sphere_left	= pScene->addSphere(Vec3f(-2.01f, 1, 0), 1.0f, RGB(230, 191, 179));
	auto sphere_right	= pScene->addSphere(Vec3f(+2.01f, 1, 0), 1.0f, RGB(230, 191, 179));

	//environment->flipNormal();

	//pScene->add(std::make_shared<CLightSky>(Vec3f::all(1.25f), 4.0f, std::make_shared<CSamplerStratified>(4)));	// light source
	auto pLight = std::make_shared<CLightArea>(Vec3f::all(1e1), Vec3f(-2, 5, -2), Vec3f(2, 5, -2), Vec3f(2, 5, 2), Vec3f(-2, 5, 2), std::make_shared<CSamplerStratified>(4));
	//pScene->add(std::make_shared<CLightOmni>(Vec3f::all(3e2), Vec3f(0, 10, 0)));	// light source
	pScene->add(pLight);
	auto camera		= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 5, 10), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 23.0f);
	auto cameraDoF	= std::make_shared<CCameraThinLens>(camera, 0.3f, 10.77f);
	pScene->add(camera);

	// Shaders
	auto pShaderGlobal			= std::make_shared<CShaderHemisphere>(*pScene, RGB(133, 153, 180), std::make_shared<CSamplerStratified>(4));
	auto pShader				= std::make_shared<CShaderDiffuse>(*pScene, std::make_shared<CTexture>());
	auto pShaderDiffuse			= std::make_shared<CShaderDiffuse>(*pScene, RGB(230, 191, 179), 1.0f);
	//auto pShaderEnvironment	= std::make_shared<CShaderFlat>(std::make_shared<CTexture>(dataPath + "earth_color_43K.tif"));
	//auto pShaderEnvironment = std::make_shared<CShaderFlat>(RGB(255, 255, 255));
	auto pShaderMirror			= std::make_shared<CShaderPrincipled>(*pScene, Vec3f::all(0), 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	auto pShaderGlass			= std::make_shared<CShaderPrincipled>(*pScene, Vec3f::all(0), 0, 0.0f, 80.0f, 0.0f, 1.0f, 1.5f);
	auto pNewShaderMirror		= std::make_shared<CShaderMirror>(*pScene);
	auto pNewShaderGlass		= std::make_shared<CShaderGlass>(*pScene, 2.5f);
	auto pShaderChrome			= std::make_shared<CShaderGlossy>(*pScene, RGB(255, 200, 200), 0.0f, std::make_shared<CSamplerStratified>(16));
	auto pShaderSSLT			= std::make_shared<CShaderSubsurfaceScattering>(*pScene, RGB(255, 200, 200), std::make_shared<CSamplerStratified>(4));
	auto pShaderVolume			= std::make_shared<CShaderVolumeScatter>(*pScene, RGB(255, 200, 200));
	auto pShaderWhite			= std::make_shared<CShaderFlat>(Vec3f::all(10));
	

	//pShaderChrome->setDiffuseColor(RGB(255, 127, 0));

	CSolidQuad lightPanel(pShaderWhite, Vec3f(0, 5.1f, 0), Vec3f(0, -1, 0), Vec3f(1, 0, 0), 2);
	pScene->add(lightPanel);

	//environment->setShader(pShaderEnvironment);
	floor->setShader(pShaderGlobal);
	sphere_center->setShader(pShaderDiffuse);
	sphere_left->setShader(pShaderGlass);
	sphere_right->setShader(pShaderDiffuse);
	
	return pScene;
}

static std::shared_ptr<CScene> buildScenePlanets(const Vec3f& bgColor, const Size resolution)
{
	auto pScene				= std::make_shared<CScene>(bgColor);
	pScene->setAmbientColor(Vec3f::all(0.2f));

	// Geometry
	auto floor		= pScene->addPlane();
	auto mercury	= pScene->addSphere(Vec3f(-3, 0.383f, -1), 0.383f); 
	auto venus		= pScene->addSphere(Vec3f(2.5f, 0.95f, 5), 0.95f);
	auto earth		= pScene->addSphere(Vec3f(-3, 1.0f, -2.6f), 1.0f);
	auto mars		= pScene->addSphere(Vec3f(-2.5f, 0.5321f, 1.5f), 0.5321f);
	//auto jupiter	= pScene->addSphere(Vec3f(0, 3.3f, 0), 3.3f); // real r = 10.973f
	auto neptune	= pScene->addSphere(Vec3f(0, 3.8647f, 0), 3.8647f);

	pScene->add(std::make_shared<CLightSky>(Vec3f::all(1.0f), 0.0f, std::make_shared<CSamplerStratified>(4)));	// light	
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-10, 5, 0), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 40.0f));	// camera

	// Textures
	auto pTextureMercury	= std::make_shared<CTexture>(dataPath + "1_mercury_8k.jpg");
	auto pTextureVenus		= std::make_shared<CTexture>(dataPath + "1_venus_4k.jpg");
	auto pTextureEarth		= std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureMars		= std::make_shared<CTexture>(dataPath + "1_mars_8k.jpg");
	auto pTextureJupiter	= std::make_shared<CTexture>(dataPath + "1_jupiter_8k.jpg");
	auto pTextureNeptune	= std::make_shared<CTexture>(dataPath + "1_neptune_2k.jpg");

	// Shaders
	auto pShaderFloor = std::make_shared<CShaderDiffuse>(*pScene, std::make_shared<CTexture>()/*RGB(0.522f, 0.6f, 0.7f)*/);
	auto pShaderMercury = std::make_shared<CShaderDiffuse>(*pScene, pTextureMercury);
	auto pShaderVenus = std::make_shared<CShaderDiffuse>(*pScene, pTextureVenus);
	auto pShaderEarth = std::make_shared<CShaderDiffuse>(*pScene, pTextureEarth);
	auto pShaderMars = std::make_shared<CShaderDiffuse>(*pScene, pTextureMars);
	auto pShaderJupiter = std::make_shared<CShaderDiffuse>(*pScene, pTextureJupiter);
	auto pShaderNeptune = std::make_shared<CShaderDiffuse>(*pScene, pTextureNeptune);
	
	floor->setShader(pShaderFloor);
	mercury->setShader(pShaderMercury);
	venus->setShader(pShaderVenus);
	earth->setShader(pShaderEarth);
	mars->setShader(pShaderMars);
	//jupiter->setShader(pShaderJupiter);
	neptune->setShader(pShaderNeptune);

	return pScene;
}

static std::shared_ptr<CScene> buildSceneBox(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);
	//pScene->setAmbientColor(Vec3f::all(0.2f));

	// primitives
	auto s1		= pScene->addSphere(Vec3f(3, 1, 0));
	auto s2		= pScene->addSphere(Vec3f(-3, 1, 0));
	auto sc		= pScene->addSphere(Vec3f(0, 1, 0));


	// shaders
	auto pShaderTop = std::make_shared<CShaderDiffuse>(*pScene, RGB(230, 191, 179));
	auto pShaderSide = std::make_shared<CShaderDiffuse>(*pScene, RGB(140, 166, 179));
	auto pShaderFloor = std::make_shared<CShaderDiffuse>(*pScene, RGB(133, 153, 180));
	auto pShaderWhite = std::make_shared<CShaderFlat>(Vec3f::all(1));
	//auto pShaderChrome = std::make_shared<CShaderChrome>(*pScene, std::make_shared<CSamplerStratified>(4));
	auto pShaderGlass = std::make_shared<CShaderPrincipled>(*pScene, InvPif * RGB(140, 166, 179), 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderGlassP = std::make_shared<CShaderPrincipled>(*pScene, RGB(140, 166, 179), 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pShaderNewGlass	= std::make_shared<CShaderGlass>(*pScene, 1.5f);
	//auto pShaderMirror = std::make_shared<CShaderPrincipled>(*pScene, InvPif * RGB(140, 166, 179), 0.1f, 2.0f, 80.0f, 1.0f, 0.0f, 1.5f);
	auto pShaderMirror	= std::make_shared<CShaderPrincipled>(*pScene, InvPif * RGB(140, 166, 179),  0.9f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	auto pShaderMirrorP = std::make_shared<CShaderPrincipled>(*pScene, RGB(140, 166, 179),		  0.9f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	
	// floor
	pScene->add(CSolidQuad(pShaderFloor, Vec3f(0, 0, 0), Vec3f(0, 1, 0), Vec3f(100, 0, 0)));

	// --- light panel ---
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(0, 10.01f, 0), Vec3f(0, -1, 0), Vec3f(10, 0, 0)));

	// --- cube ---
	//pScene->add(CSolidQuad(pShaderTop,  Vec3f(0, 2, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0)));
	//pScene->add(CSolidQuad(pShaderSide, Vec3f(1, 1, 0), Vec3f(1, 0, 0), Vec3f(0, 0, 1)));
	//pScene->add(CSolidQuad(pShaderSide, Vec3f(-1, 1, 0), Vec3f(-1, 0, 0), Vec3f(0, 0, 1)));
	//pScene->add(CSolidQuad(pShaderSide, Vec3f(0, 1, 1), Vec3f(0, 0, 1), Vec3f(1, 0, 0)));
	//pScene->add(CSolidQuad(pShaderSide, Vec3f(0, 1, -1), Vec3f(0, 0, -1), Vec3f(-1, 0, 0)));
	// --- ---- ---

	s1->setShader(pShaderMirror);
	sc->setShader(pShaderMirror);
	s2->setShader(pShaderMirrorP);

	// lights
	//pScene->add(std::make_shared<CLightOmni>(Vec3f::all(5e1), Vec3f(-4, 6, 3), true));
	//pScene->add(std::make_shared<CLightOmni>(Vec3f::all(5e1), Vec3f(0, 10, 0), true));
	pScene->add(std::make_shared<CLightArea>(Vec3f::all(2.0f), Vec3f(-10, 10, -10), Vec3f(10, 10, -10), Vec3f(10, 10, 10), Vec3f(-10, 10, 10), std::make_shared<CSamplerStratified>(4)));
	pScene->add(std::make_shared<CLightSky>(Vec3f::all(1.0f), 0, std::make_shared<CSamplerStratified>(4)));

	// camera
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-5, 5, 5), Vec3f(0, 1, 0), Vec3f(0, 1, 0), 45.0f));

	return pScene;
}

static std::shared_ptr<CScene> buildSceneTorusKnot(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);
	
	// Geometry
	auto floor	= pScene->addDisc(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 10.0f, 0.0f, RGB(133, 153, 180));
	//auto sphere	= pScene->addSphere(Vec3f(0, 0.5f, 0), 0.5f);
	
	
	// Shaders
	auto pShaderWhite	= std::make_shared<CShaderFlat>(Vec3f::all(2.2f));
	auto pShaderDiffuse = std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 255, 255));
	auto pShaderGlass	= std::make_shared<CShaderPrincipled>(*pScene, InvPif * RGB(140, 166, 179), 0.1f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);
	auto pNewShaderGlass= std::make_shared<CShaderGlass>(*pScene, 1.5f);
	auto pShaderGlobal  = std::make_shared<CShaderHemisphere>(*pScene, RGB(133, 153, 180), std::make_shared<CSamplerStratified>(4));

	//floor->setShader(pShaderDiffuse);
	//sphere->setShader(pShaderDiffuse);
	
	// geometry
	CSolidQuad lightPanel(pShaderWhite, Vec3f(0, 2.1f, 0), Vec3f(0, -1, 0), Vec3f(1, 0, 0), 1);
	CSolid torusKnot(pNewShaderGlass, dataPath + "Torus Knot.obj");
	//auto sphere = CSolidSphere(pShaderGlass, Vec3f(0, 0.5f, 0), 0.5f, 24);
	//auto sphere = std::make_shared<CPrimSphere>(pNewShaderGlass, Vec3f(0, 0.5f, 0), 0.5f);

	// light
	//auto pLight = std::make_shared<CLightOmni>(Vec3f::all(1e3), Vec3f(0, 20, 0));
	//auto pLight				= std::make_shared<CLightArea>(Vec3f::all(Pif), Vec3f(-1, 2, -1), Vec3f(1, 2, -1), Vec3f(1, 2, 1), Vec3f(-1, 2, 1), std::make_shared<CSamplerStratified>(4));
	auto pLight		= std::make_shared<CLightSky>(Vec3f::all(1), 2.0f, std::make_shared<CSamplerStratified>(4));

	// camera
	auto pCamera			= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-5, 4, 10), Vec3f(0, 0.5f, 0), Vec3f(0, 1, 0), 10.0f);
	
	pScene->add(floor);
	//pScene->add(sphere);
	pScene->add(lightPanel);
	pScene->add(torusKnot);
	
	pScene->add(pLight);
	pScene->add(pCamera);
		
	return pScene;
}

static std::shared_ptr<CScene> buidSceneOcclusions(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);

	// Geometry
	//auto plane	= pScene->addPlane();
	//auto sphere	= pScene->addSphere();

	for (int i = 0; i < 1000; i++) {
		auto pShader = std::make_shared<CShaderDiffuse>(*pScene, RGB(random::u(0, 255), random::u(0, 255), random::u(0, 255)));
		pShader->setOpacity(static_cast<float>(random::u(100, 500)) / 1000);
		auto solid = CSolidQuad(pShader, Vec3f(random::u(-40, 40), static_cast<float>(random::u(1000, 60000)) / 1000, random::u(-40, 40)), Vec3f(0, 1, 0), Vec3f(1, 0, 0), static_cast<float>(random::u(1000, 5000)) / 1000);
		pScene->add(solid);
	}

	auto s2 = std::make_shared<CShaderDiffuse>(*pScene, RGB(20, 155, 20));
	s2->setOpacity(0.5f);
	auto s3 = std::make_shared<CShaderDiffuse>(*pScene, RGB(155, 20, 20));
	s3->setOpacity(0.4f);

	
	auto q2 = CSolidQuad(s2, Vec3f(-2, 30, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0), 4);
	auto q3 = CSolidQuad(s3, Vec3f(-2, 40, 0), Vec3f(0, 1, 0), Vec3f(1, 0, 0), 1);

	//pScene->add(q2);
	//pScene->add(q3);
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(1e4), Vec3f(0, 100, 0)));
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(20, 100, 20), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 35.0f));

	return pScene;
}

//#include <random>
//
//Matx33f World2LocalMatix(const Vec3d& n, const Vec3d& aux = Vec3d(1.0f, .0f, .0f)) {
//	Vec3f t = normalize(tangent(n, aux));
//	Vec3f s = t.cross(n);
//
//	return Matx33d(
//		s[0], s[1], s[2],
//		t[0], t[1], t[2],
//		n[0], n[1], n[2]
//	);
//}

int main(int argc, char* argv[])
{
	//std::random_device rd; 
	//std::mt19937 generator(rd()); 
	//std::uniform_real_distribution<double> distribution(-1.0f, 1.0f);
	//Vec3d n = normalize(Vec3d(distribution(generator), distribution(generator), distribution(generator)));
	//auto M = World2LocalMatix(n);
	//auto I = M.t() * M;
	//std::cout << I << std::endl;
	//return 0;
	
	
	
	const Vec3f	bgColor = RGB(196, 209, 227);
	//const Vec3f	bgColor = RGB(200, 200, 200);
	const Size resolution(960, 600);
	//const Size resolution(3072, 1920);

	//auto pScene = buildpSceneColorSphere(bgColor, resolution);
	auto pScene = buildSceneMirrorSphere(bgColor, resolution);
	//auto pScene = buildScenePlanets(bgColor, resolution);
	//auto pScene = buildSceneBox(bgColor, resolution);
	//auto pScene = buildSceneTorusKnot(bgColor, resolution);
	//auto pScene = buidSceneOcclusions(bgColor, resolution);
	

	// ------------------------- TEST -------------------------
	//auto pScene = std::make_shared<CScene>(bgColor);
	//pScene->setAmbientColor(Vec3f::all(0.2f));
	//auto floor = pScene->addPlane(Vec3f(0, -1, 0), Vec3f(0, 1, 0));
	//
	////pScene->setAmbientColor(Vec3f::all(0.5f));

	//auto s1 = pScene->addSphere(Vec3f(4.4f, 0, 0));
	//auto s2 = pScene->addSphere(Vec3f(2.2f, 0, 0));
	//auto s3 = pScene->addSphere(Vec3f(0, 0, 0));
	//auto s4 = pScene->addSphere(Vec3f(-2.2f, 0, 0));
	//auto s5 = pScene->addSphere(Vec3f(-4.4f, 0, 0));
	//
	//auto texture		= std::make_shared<CTexture>(dataPath + "b13.jpg");
	//auto test			= std::make_shared<CShaderHemisphere>(*pScene, RGB(255, 200, 200));
	//auto lambertian		= std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 200, 200));
	//auto diffuse		= std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 200, 200));
	//auto oren_nayar00	= std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 200, 200), 0.0f);
	//auto oren_nayar02	= std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 200, 200), 11.46f);
	//auto oren_nayar035	= std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 200, 200), 20.0f);
	//auto oren_nayar05	= std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 200, 200), 60.0f);
	//auto oren_nayar10	= std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 200, 200), 90.0f);
	//auto phong			= std::make_shared<CShaderPhong>(*pScene, RGB(255, 200, 200), 1.0f, 0.5f, 250.0f);
	//auto blinn			= std::make_shared<CShaderBlinn>(*pScene, RGB(255, 200, 200), 1.0f, 0.5f, 250.0f);
	//auto mirror			= std::make_shared<CShaderMirror>(*pScene);
	//
	////floor->setShader(lambertian);
	//s1->setShader(mirror);
	//s2->setShader(blinn);
	//s3->setShader(blinn);
	//s4->setShader(blinn);
	//s5->setShader(blinn);

	//auto shader = std::make_shared<CShaderDiffuse>(*pScene, texture);

	////auto pdisc = pScene->addDisc(Vec3f(-2, 0, 0), normalize(Vec3f(0, 0, -1)), 1.2f, 0.2f);
	////auto cdisk = CSolidDisc(shader, Vec3f(2, 0, 0), normalize(Vec3f(0, 0, -1)), 1.2f, 0.2f, 32);

	////pdisc->setShader(shader);
	////pScene->add(cdisk);
	//auto pLight = std::make_shared<CLightOmni>(2e2 * RGB(255, 255, 255), Vec3f(0, 10, 0), true);
	//pScene->add(pLight);
	////pScene->add(std::make_shared<CLightOmni>(Vec3f::all(3e2), Vec3f(0, 10,  -2)));
	//pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 10, -10), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 35.0f));
	
	// --------------------------------------------------------


	pScene->buildAccelStructure(0, 3);

	if (false) {
		Timer::start("Rendering 100 frames...");
		for (size_t x = 0;; x++) {
			Mat render = pScene->render(std::make_shared<CSamplerStratified>(1, false));
			imshow("Render", render);
			
			float X = static_cast<float>(x % 200) / 10.0f - 5.0f; // [-5; 15)
			if (X >= 5) X = 10.0f - X;
			//pLight->setOrigin(Vec3f(X, 10, 0));

			if (x && x % 100 == 0) {
				Timer::stop();
				Timer::start("Rendering 100 frames...");
			}

			if (waitKey(1) == 'q') break;
		}
	}
	else {
		Timer::start("Rendering...");
		Mat render = pScene->render(std::make_shared<CSamplerStratified>(4), 48);
		Timer::stop();
		imshow("pScene", render);
		imwrite("D:\\renders\\res__6.png", render);
		waitKey();
	}
	return 0;
}
