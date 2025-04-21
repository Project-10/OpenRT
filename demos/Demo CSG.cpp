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
	auto pShaderGlass = std::make_shared<CShaderPrincipled>(*pScene, Vec3f::all(0), 0.0f, 0.0f, 2.0f, 80.0f, 0.2f, 0.8f, 1.5f);

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
	auto pShader1 = std::make_shared<CShaderPhong>(*pScene, RGB(255, 200, 100), 0.1f, 0.9f, 0.5f, 40.0f);
	auto pShader3 = std::make_shared<CShaderPhong>(*pScene, RGB(100, 200, 255), 0.1f, 0.9f, 0.5f, 40.0f);
	auto pShader2 = std::make_shared<CShaderPhong>(*pScene, RGB(200, 255, 100), 0.1f, 0.9f, 0.5f, 40.0f);
	auto pShader4 = std::make_shared<CShaderPhong>(*pScene, RGB(200, 100, 255), 0.1f, 0.9f, 0.5f, 40.0f);

	// geometry
	auto box1 = CSolidBox(pShader1);
	auto box2 = CSolidBox(pShader2);
	auto sphere1 = std::make_shared<CPrimSphere>(pShader3, Vec3f::all(0), 1);
	auto sphere2 = std::make_shared<CPrimSphere>(pShader4, Vec3f::all(0), 1);
	//ptr_prim_t largeSphere = std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, 0), 5.0f);
	//ptr_prim_t smallSphere = std::make_shared<CPrimSphere>(pShader, Vec3f(0, 0, -5), 1.0f);
	//ptr_prim_t composite = std::make_shared<CPrimBoolean>(largeSphere, smallSphere, BoolOp::Substraction);

	CTransform T;
	box1.transform(T.translate(0, 1, 0).get());
	sphere1->transform(T.translate(-1, 2, -1).get());
	box2.transform(T.translate(0, 1, 0).get());
	sphere2->transform(T.translate(-1, 2, -1).get());

	auto composite1 = std::make_shared<CPrimBoolean>(box1, CSolid(sphere1), BoolOp::Substraction);
	auto composite2 = std::make_shared<CPrimBoolean>(box2, CSolid(sphere2), BoolOp::Substraction);

	composite1->transform(T.translate(3, 0, 0).rotate(Vec3f(0, 1, 0), 30).get());
	composite2->transform(T.translate(-1, 0, 0).scale(2).rotate(Vec3f(0, 1, 0), -60).get());
	//pScene->add(box1);
	pScene->add(composite1);
	pScene->add(composite2);
	//pScene->add(largeSphere);
	//pScene->add(smallSphere);
	//pScene->add(composite);

	// Light
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(1e2), Vec3f(-3, 10, 0), true));
	pScene->add(std::make_shared<CLightOmni>(Vec3f::all(1e2), Vec3f(3, 10, -10), true));

	// camera
	pScene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 5, -10), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 60.0f));

	return pScene;
}

int main() {
	const Vec3f bgColor = RGB(0, 0, 0);
	const Size  resolution = Size(800, 600);

	//for (float t = 29; t > -29; t=t-0.5f) {

	//auto pScene = buildSceneEarth(bgColor, resolution);
	//auto pScene = buildSceneLens(bgColor, resolution, 0);
	//auto pScene	= buildClassicExample(RGB(255, 255, 255), resolution);
	auto pScene = buildSceneTest(bgColor, resolution);

	pScene->buildAccelStructure(20, 3);

	// Add everything to scene
	Timer::start("Rendering... ");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(4));
	Timer::stop();

	imshow("image", img);
	imwrite("D:\\Renders\\CSG.jpg", img);
	//waitKey(5);
	//printf("%f\n", t);
	//}
	waitKey();
	return 0;
}
