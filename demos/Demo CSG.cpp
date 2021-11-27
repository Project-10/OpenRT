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
    ptr_prim_t temp = std::make_shared<CCompositeGeometry>(solidSphere2, solidSphere3, BoolOp::Union);
    ptr_prim_t row1 = std::make_shared<CCompositeGeometry>(temp, solidSphere4, BoolOp::Union);
    ptr_prim_t temp2 = std::make_shared<CCompositeGeometry>(solidSphere5, solidSphere6, BoolOp::Union);
    ptr_prim_t row2 = std::make_shared<CCompositeGeometry>(temp2, solidSphere7, BoolOp::Union);
    ptr_prim_t temp3 = std::make_shared<CCompositeGeometry>(solidSphere8, solidSphere9, BoolOp::Union);
    ptr_prim_t row3 = std::make_shared<CCompositeGeometry>(temp3, solidSphere10, BoolOp::Union);
    ptr_prim_t temp4 = std::make_shared<CCompositeGeometry>(row1, row2, BoolOp::Union);
    return std::make_shared<CCompositeGeometry>(row3, temp4, BoolOp::Union);
}

std::shared_ptr<CScene> buildSceneEarth(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);
	
	// textures
	auto pTextureEarthDiffuse  = std::make_shared<CTexture>(dataPath + "1_earth_8k.jpg");
	auto pTextureEarthSpecular = std::make_shared<CTexture>(dataPath + "1_earth_specular_map_8k.tif");
	auto pTextureEarthAmbient  = std::make_shared<CTexture>(dataPath + "1_earth_night_map_8k.jpg");
	
	// Shaders
	auto pShaderEarth   = std::make_shared<CShaderPhong>(*pScene, Vec3f::all(1), 0.5f, 1.0f, 0.5f, 5.0f);
	pShaderEarth->setAmbientColor(pTextureEarthAmbient);
	pShaderEarth->setDiffuseColor(pTextureEarthDiffuse);
	pShaderEarth->setSpecularLevel(pTextureEarthSpecular);
	auto pShaderCore    = std::make_shared<CShaderPhong>(*pScene, RGB(1, 1, 0), 0.8f, 0.2f, 0.0f, 40.0f);
	auto pShaderCut     = std::make_shared<CShaderPhong>(*pScene, RGB(0.8f, 0.2f, 0), 0.3f, 0.7f, 0, 40);

	// Geometries
	auto earth          = CSolidSphere(pShaderEarth, Vec3f(0, 0, 0), 1, 64);
	auto core           = CSolidSphere(pShaderCore, Vec3f(0, 0, 0), 0.55f, 24);
	//ptr_prim_t earth        = std::make_shared<CPrimSphere>(pShaderEarth, Vec3f(0, 0, 0), 1);
	//ptr_prim_t core         = std::make_shared<CPrimSphere>(pShaderCore, Vec3f(0, 0, 0), 0.55f);

	// Transform
	CTransform T;
	earth.transform(T.rotate(Vec3f(0, 1, 0), 45).get());
	
	auto box                = CSolidBox(pShaderCut, Vec3f(0.5f, 0.5f, 0.5f), 0.5f);
	ptr_prim_t composite1   = std::make_shared<CCompositeGeometry>(earth, box, BoolOp::Difference);
	ptr_prim_t composite2   = std::make_shared<CCompositeGeometry>(composite1, core, BoolOp::Union);

	//pScene->add(earth);
	//pScene->add(core);
    pScene->add(composite1);

	// Light
	auto sun            = std::make_shared<CLightOmni>(Vec3f::all(1e9), Vec3f(23500, 0, 0), true);
	pScene->add(sun);

	// cameras
	auto camera         = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(1, 2, 3), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 35.0f);
	pScene->add(camera);
	
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
	ptr_prim_t composite 	 = std::make_shared<CCompositeGeometry>(largeSphere, smallSphere, BoolOp::Difference);
	
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
    const Vec3f bgColor     = RGB(0, 0, 0);
    const Size  resolution  = Size(800, 600);

	auto pScene = buildSceneEarth(bgColor, resolution);
	//auto pScene = buildSceneTest(bgColor, resolution);

	pScene->buildAccelStructure(20, 3);

    // Add everything to scene
    Timer::start("Rendering... ");
    Mat img = pScene->render(std::make_shared<CSamplerStratified>(3, true, true));
    Timer::stop();

    imshow("image", img);
    waitKey();
    return 0;
}
