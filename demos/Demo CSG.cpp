#include "openrt.h"
#include "core/timer.h"

using namespace rt;

ptr_prim_t createCompositeDice(const ptr_shader_t& shader) {
	auto solidSphere2 = CSolidSphere(shader, Vec3f(0, -3.0f, -7), 0.2f, 24, true);
	auto solidSphere3 = CSolidSphere(shader, Vec3f(0.5f, -3.0f, -7), 0.2f, 24, true);
	auto solidSphere4 = CSolidSphere(shader, Vec3f(-0.5f, -3.0f, -7), 0.2f, 24, true);
	auto solidSphere5 = CSolidSphere(shader, Vec3f(0, -2.5f, -7), 0.2f, 24, true);
	auto solidSphere6 = CSolidSphere(shader, Vec3f(0.5f, -2.5f, -7), 0.2f, 24, true);
	auto solidSphere7 = CSolidSphere(shader, Vec3f(-0.5f, -2.5f, -7), 0.2f, 24, true);
	auto solidSphere8 = CSolidSphere(shader, Vec3f(0, -3.5f, -7), 0.2f, 24, true);
	auto solidSphere9 = CSolidSphere(shader, Vec3f(0.5f, -3.5f, -7), 0.2f, 24, true);
	auto solidSphere10 = CSolidSphere(shader, Vec3f(-0.5f, -3.5f, -7), 0.2f, 24, true);
	ptr_prim_t temp = std::make_shared<CPrimBoolean>(solidSphere2, solidSphere3, BoolOp::Union);
	ptr_prim_t row1 = std::make_shared<CPrimBoolean>(temp, solidSphere4, BoolOp::Union);
	ptr_prim_t temp2 = std::make_shared<CPrimBoolean>(solidSphere5, solidSphere6, BoolOp::Union);
	ptr_prim_t row2 = std::make_shared<CPrimBoolean>(temp2, solidSphere7, BoolOp::Union);
	ptr_prim_t temp3 = std::make_shared<CPrimBoolean>(solidSphere8, solidSphere9, BoolOp::Union);
	ptr_prim_t row3 = std::make_shared<CPrimBoolean>(temp3, solidSphere10, BoolOp::Union);
	ptr_prim_t temp4 = std::make_shared<CPrimBoolean>(row1, row2, BoolOp::Union);
	return std::make_shared<CPrimBoolean>(row3, temp4, BoolOp::Union);
}

std::shared_ptr<CScene> buildSceneEarth(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);

	// textures
	auto pTextureEarthDiffuse = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureEarthSpecular = std::make_shared<CTexture>(dataPath + "1_earth_specular_map_8k.tif");
	auto pTextureEarthAmbient = std::make_shared<CTexture>(dataPath + "1_earth_night_map_8k.jpg");

	// Shaders
	auto pShaderEarth = std::make_shared<CShaderPhong>(*pScene, Vec3f::all(1), 0.5f, 1.0f, 0.5f, 5.0f);
	pShaderEarth->setAmbientColor(pTextureEarthAmbient);
	pShaderEarth->setDiffuseColor(pTextureEarthDiffuse);
	pShaderEarth->setSpecularLevel(pTextureEarthSpecular);
	auto pShaderCore = std::make_shared<CShaderPhong>(*pScene, RGB(255, 255, 0), 0.8f, 0.2f, 0.0f, 40.0f);
	auto pShaderCut = std::make_shared<CShaderPhong>(*pScene, RGB(204, 51, 0), 0.3f, 0.7f, 0.0f, 40.0f);
	auto pShaderAtmosphere = std::make_shared<CShaderSSLT>(*pScene, RGB(0, 127, 255), 0.0f);

	// Geometries
	auto earth          = CSolidSphere(pShaderEarth, Vec3f(0, 0, 0), 1, 64);
	auto core           = CSolidSphere(pShaderCore, Vec3f(0, 0, 0), 0.55f, 64);
	auto atmosphere		= CSolidSphere(pShaderAtmosphere, Vec3f(0, 0, 0), 1.05f, 64);
	//ptr_prim_t earth = std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0, 0), 1);
	//ptr_prim_t core = std::make_shared<CPrimSphere>(pShaderCore, Vec3f(0, 0, 0), 0.55f);

	// Transform
	CTransform T;
	earth.transform(T.rotate(Vec3f(0, 1, 0), 45).get());

	auto box = CSolidBox(pShaderCut, Vec3f(0.5f, 0.5f, 0.5f), 0.5f);
	ptr_prim_t composite1 = std::make_shared<CPrimBoolean>(earth, box, BoolOp::Substraction);
	ptr_prim_t composite2 = std::make_shared<CPrimBoolean>(composite1, core, BoolOp::Union);

	pScene->add(composite2);
	//pScene->add(box);
	//pScene->add(atmosphere);

	// Light
	auto sun = std::make_shared<CLightOmni>(Vec3f::all(1e9), Vec3f(23500, 0, 0), false);
	pScene->add(sun);

	// cameras
	auto camera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(1, 2, 3), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 35.0f);
	pScene->add(camera);

	return pScene;
}

ptr_prim_t biconvex(const ptr_shader_t pShader, const Vec3f& origin, float R, float r)
{
	float x = sqrtf(R * R - r * r);
	ptr_prim_t pSphere1 = std::make_shared<CPrimSphere>(pShader, origin - Vec3f(0, 0, x), R);
	ptr_prim_t pSphere2 = std::make_shared<CPrimSphere>(pShader, origin + Vec3f(0, 0, x), R);
	ptr_prim_t res = std::make_shared<CPrimBoolean>(pSphere1, pSphere2, BoolOp::Intersection);

	return res;
}
// plano-convex
// positive meniscus
// 
ptr_prim_t biconcave(const ptr_shader_t pShader, const Vec3f& origin, float R, float r)
{
	float x = R + 0.1f;
	const float h = 3;

	ptr_prim_t pSphere1 = std::make_shared<CPrimSphere>(pShader, origin - Vec3f(0, 0, x), R);
	ptr_prim_t pSphere2 = std::make_shared<CPrimSphere>(pShader, origin + Vec3f(0, 0, x), R);
	ptr_prim_t pSpheres = std::make_shared<CPrimBoolean>(pSphere1, pSphere2, BoolOp::Union);

	CTransform t;
	CSolidCylinder base(pShader, origin, r, h, 1, 32, true);
	base.transform(t.rotate(Vec3f(1, 0, 0), 90).translate(0, 0, -h / 2).get());
	ptr_prim_t pLens = std::make_shared<CPrimBoolean>(base, pSpheres, BoolOp::Substraction);

	return pLens;
}

// plano-concave
// negative meniscus


std::shared_ptr<CScene> buildSceneLens(const Vec3f& bgColor, const Size resolution, float pos)
{
	auto pScene = std::make_shared<CScene>(bgColor);

	// textures
	auto pTextureEarth = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");

	// shaders
	auto pShaderPage = std::make_shared<CShaderBlinn>(*pScene, pTextureEarth, 0.0f, 1.0f, 0.0f, 0.0f);
	auto pShaderTest = std::make_shared<CShaderFlat>(RGB(127, 127, 127));
	auto pShaderGlass = std::make_shared<CShaderGeneral>(*pScene, Vec3f::all(0), 0.0f, 0.0f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);

	// geometry
	CSolidQuad book(pShaderTest, Vec3f(0, 0, 0), Vec3f(0, 0, -1), Vec3f(1, 0, 0), 10);

	CSolidCone cone(pShaderPage, Vec3f(0, 0, -15), 3, 5, 5, 24, false);

	//ptr_prim_t pLens = biconvex(pShaderTest, Vec3f(0, 0, -15), 15, 3);
	//ptr_prim_t pLens = biconcave(pShaderGlass, Vec3f(0, 0, pos), 15, 5);

	//CSolidCylinder base(pShaderTest, Vec3f(0, 0, 0), 3, 6, 1, 24, true);


	CTransform t;


	// light
	auto pLight = std::make_shared<CLightOmni>(Vec3f::all(1e2), Vec3f(-15, 5, -15), false);

	// camera
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-15, 5, -15), Vec3f(0, 0, -15), Vec3f(0, 1, 0), 45.0f);


	book.transform(t.scale(-2, 1, 1).get());

	//pScene->add(book);
	pScene->add(cone);
	pScene->add(pLight);
	pScene->add(pCamera);

	return pScene;
}

std::shared_ptr<CScene> buildClassicExample(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);

	// shaders
	auto pShaderRed		= std::make_shared<CShaderBlinn>(*pScene, RGB(255, 0, 0), 0.4f, 0.6f, 1.0f, 2.0f);
	auto pShaderGreen	= std::make_shared<CShaderBlinn>(*pScene, RGB(0, 255, 0), 0.4f, 0.6f, 1.0f, 2.0f);
	auto pShaderBlue	= std::make_shared<CShaderBlinn>(*pScene, RGB(0, 0, 255), 0.4f, 0.6f, 1.0f, 2.0f);

	CTransform T;

	// geometry
	CSolidCylinder c1(pShaderGreen, Vec3f(0, 0, 0), 1.3f, 6, 1, 64);
	CSolidCylinder c2(pShaderGreen, Vec3f(0, 0, 0), 1.3f, 6, 1, 64);
	CSolidCylinder c3(pShaderGreen, Vec3f(0, 0, 0), 1.3f, 6, 1, 64);
	CSolidBox	   b1(pShaderRed, Vec3f(0, 0, 0), 2);
	CSolidSphere   s1(pShaderBlue, Vec3f(0, 0, 0), 2.6f, 64);

	c1.transform(T.translate(0, -3, 0).get());
	c2.transform(T.rotate(Vec3f(1, 0, 0), 90.0f).translate(0, 0, -3).get());
	c3.transform(T.rotate(Vec3f(0, 0, 1), 90.0f).translate(3, 0, 0).get());

	ptr_prim_t	u1 = std::make_shared<CPrimBoolean>(c1, c2, BoolOp::Union);
	ptr_prim_t	u2 = std::make_shared<CPrimBoolean>(u1, c3, BoolOp::Union);
	ptr_prim_t	i1 = std::make_shared<CPrimBoolean>(b1, s1, BoolOp::Intersection);
	ptr_prim_t	d1 = std::make_shared<CPrimBoolean>(i1, u2, BoolOp::Substraction);

	pScene->add(c1);
	pScene->add(c2);
	pScene->add(c3);
	pScene->add(b1);
	pScene->add(s1);
	//pScene->add(d1);

	// light
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(2e2), Vec3f(-10, 10, 10)));

	// camera
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(8, 8, 10), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 30.0f));

	return pScene;
}

std::shared_ptr<CScene> buildSceneTest(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);

	// shaders
	auto pShader = std::make_shared<CShaderFlat>(Vec3f(1, 1, 1));

	// geometry
	ptr_prim_t largeSphere = std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 5.0f);
	ptr_prim_t smallSphere = std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, -5), 1.0f);
	ptr_prim_t composite = std::make_shared<CPrimBoolean>(largeSphere, smallSphere, BoolOp::Substraction);

	//pScene->add(largeSphere);
	//pScene->add(smallSphere);
	pScene->add(composite);

	// Light
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(1e3), Vec3f(0, 0, 0), true));

	// camera
	pScene->add(std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 0, 0), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 45.0f));

	return pScene;
}

int main() {
	
	
	Mat mat, mat32;
	Mat res, res32;
	int k  = 0;
	for (int i = 6822; i < 7304; i++) {
		std::string fileName = "C:\\Users\\Creator\\Desktop\\LITE\\_MG_" + std::to_string(i) + ".tif";
		std::cout << fileName << std::endl;
		mat = imread(fileName, 1);
		mat.convertTo(mat32, CV_32FC3);
		if (res32.empty()) res32 = mat32.clone();
		else res32 += mat32;
		k++;
		//if (k >= 9) break;
	}	
	imwrite("C:\\Users\\Creator\\Desktop\\LITE\\res.tif", res32);
	
	res32.convertTo(res, CV_8UC3, 1.0 / k);
	imwrite("C:\\Users\\Creator\\Desktop\\LITE\\res1.png", res);
	res32.convertTo(res, CV_8UC3, 2.0 / k);
	imwrite("C:\\Users\\Creator\\Desktop\\LITE\\res2.png", res);
	res32.convertTo(res, CV_8UC3, 4.0 / k);
	imwrite("C:\\Users\\Creator\\Desktop\\LITE\\res4.png", res);
	res32.convertTo(res, CV_8UC3, 8.0 / k);
	imwrite("C:\\Users\\Creator\\Desktop\\LITE\\res8.png", res);


	
	
	
	
	const Vec3f bgColor = RGB(0, 0, 0);
	const Size  resolution = Size(800, 600);

	//for (float t = 29; t > -29; t=t-0.5f) {

	auto pScene = buildSceneEarth(bgColor, resolution);
	//auto pScene = buildSceneLens(bgColor, resolution, 0);
	//auto pScene	= buildClassicExample(RGB(255, 255, 255), resolution);
	//auto pScene = buildSceneTest(bgColor, resolution);

	pScene->buildAccelStructure(20, 3);

	// Add everything to scene
	Timer::start("Rendering... ");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(4, true, true));
	Timer::stop();

	imshow("image", img);
	imwrite("D:\\Renders\\CSG.jpg", img);
	//waitKey(5);
	//printf("%f\n", t);
	//}
	waitKey();
	return 0;
}
