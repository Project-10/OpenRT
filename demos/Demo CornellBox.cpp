#include "openrt.h"
#include "core/timer.h"

using namespace rt;

std::shared_ptr<CScene> build_test_2d(const Vec3f& bgColor, const Size resolution) 
{
	const float intensity = 4;
	const float h = 10;
	const float l = 2;

	// Scene
	auto pScene = std::make_shared<CScene>(bgColor);

	// Geometry
	auto plane = pScene->addPlane();

	// Camera
	auto pCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(5, 10, 0) * 2.0f, Vec3f(0, 0, 0), Vec3f(0, 1, 0), 45.0f);

	// Shaders
	auto pShaderArea = std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 255, 255));
	auto pShaderHemisphere = std::make_shared<CShaderHemisphere>(*pScene, RGB(255, 255, 255), std::make_shared<CSamplerStratified>(32));
	auto pShaderWhite = std::make_shared<CShaderFlat>(Vec3f::all(intensity));

	plane->setShader(pShaderArea);
	//plane->setShader(pShaderHemisphere);

	// Lights
	auto pLightArea = std::make_shared<CLightArea>(Vec3f::all(intensity), Vec3f(l, h, l), Vec3f(-l, h, l), Vec3f(-l, h, -l), Vec3f(l, h, -l), std::make_shared<CSamplerStratified>(4));
	auto pLightOmni = std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, h, 0));

	// Geometry
	auto panel = CSolidQuad(pShaderWhite, Vec3f(0, h + .01f, 0), Vec3f(0, -1, 0), Vec3f(0, 0, 1), l);


	pScene->add(pCamera);
	pScene->add(pLightArea);
	pScene->add(panel);

	pScene->buildAccelStructure(0, 3);

	return pScene;
}

std::shared_ptr<CScene> build_test_3d(const Vec3f& bgColor, const Size resolution) {
	auto pScene = std::make_shared<CScene>(bgColor);
	return pScene;
}

std::shared_ptr<CScene> buildSceneCornellBox(const Vec3f& bgColor, const Size resolution)
{
	auto pScene = std::make_shared<CScene>(bgColor);

	const float intensity = 60.0f;
	const Vec3f light_source = RGB(255, 207, 120);
	const Vec3f color_red = RGB(202, 28, 0);
	const Vec3f color_green = RGB(40, 132, 44);

	// Camera
	auto pCamera = std::make_shared<CCameraPerspective>(resolution, Vec3f(278, 273, -800), Vec3f(0, 0, 1), Vec3f(0, 1, 0), 39.3f);

	// Shaders
	auto pShaderLight = std::make_shared<CShaderFlat>(intensity * light_source);
	
	auto pShaderWhite = std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 255, 255));
	auto pShaderRed = std::make_shared<CShaderDiffuse>(*pScene, RGB(255, 0, 0));
	auto pShaderGreen = std::make_shared<CShaderDiffuse>(*pScene, RGB(0, 255, 0));

//	auto pShaderGlobal = std::make_shared<CShaderHemisphere>(*pScene, RGB(255, 255, 255)/*, std::make_shared<CSamplerStratified>(4)*/);
//	auto pShaderGlobalR = std::make_shared<CShaderHemisphere>(*pScene, color_red/*, std::make_shared<CSamplerStratified>(4)*/);
//	auto pShaderGlobalG = std::make_shared<CShaderHemisphere>(*pScene, color_green/*, std::make_shared<CSamplerStratified>(4)*/);


	// Lights
	auto pLightArea = std::make_shared<CLightArea>(intensity * light_source, Vec3f(343, 548.78f, 227), Vec3f(343, 548.78f, 332), Vec3f(213, 548.78f, 332), Vec3f(213, 548.78f, 227), std::make_shared<CSamplerStratified>(4));
	auto pLightOmni = std::make_shared<CLightOmni>(intensity * RGB(255, 255, 255) /*RGB(255, 214, 126)*/, Vec3f(278, 548.78f, 279.5f));

	// Blocks
	CSolidBox shortBlock(pShaderWhite, Vec3f(185.5f, 82.5f, 169), 165, 165, 168);
	CSolidBox tallBlock(pShaderWhite, Vec3f(368.5f, 165, 351.25f), 165, 330, 167);

	shortBlock.transform(CTransform().rotate(Vec3f(0, 1, 0), -16.7f).get());
	tallBlock.transform(CTransform().rotate(Vec3f(0, 1, 0), 17.1f).get());

	pScene->add(pCamera);
	pScene->add(pLightArea);

	// ceiling with a whole
	auto ceiling = CSolidQuad(pShaderWhite, Vec3f(556, 548.8f, 0), Vec3f(556, 548.8f, 559.2f), Vec3f(0, 548.8f, 559.2f), Vec3f(0, 548.8f, 0));
	auto ceiling_lamp_hole = CSolidBox(pShaderWhite, Vec3f(278, 548, 279.5f), 130, 2, 105);
	auto ceiling_with_hole = std::make_shared<CPrimBoolean>(ceiling, ceiling_lamp_hole, BoolOp::Substraction, 0);

	pScene->add(CSolidQuad(pShaderWhite, Vec3f(552.8f, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 0, 559.2f), Vec3f(549.6f, 0, 559.2f)));					// floor
	pScene->add(ceiling);		// ceiling
	pScene->add(CSolidQuad(pShaderWhite, Vec3f(549.6f, 0, 559.2f), Vec3f(0, 0, 559.2f), Vec3f(0, 548.8f, 559.2f), Vec3f(556, 548.8f, 559.2f)));	// back wall
	pScene->add(CSolidQuad(pShaderGreen, Vec3f(0, 0, 559.2f), Vec3f(0, 0, 0), Vec3f(0, 548.8f, 0), Vec3f(0, 548.8f, 559.2f)));					// right wall
	pScene->add(CSolidQuad(pShaderRed, Vec3f(552.8f, 0, 0), Vec3f(549.6f, 0, 559.2f), Vec3f(556, 548.8f, 559.2f), Vec3f(556, 548.8f, 0)));		// left wall
	pScene->add(CSolidQuad(pShaderLight, Vec3f(343, 548.79f, 227), Vec3f(343, 548.79f, 332), Vec3f(213, 548.79f, 332), Vec3f(213, 548.79f, 227)));// light

	pScene->add(shortBlock);
	pScene->add(tallBlock);
	
	pScene->buildAccelStructure(20, 4);

	return pScene;
}

int main()
{
	const Vec3f	bgColor = RGB(0, 0, 0);
	const Size	resolution = Size(512, 512); //Size(1024 / 3, 1024 / 3);

	//auto pScene = build_test_2d(bgColor, resolution);
	//auto pScene = build_test_3d(bgColor, resolution);
	auto pScene = buildSceneCornellBox(bgColor, resolution);
	
	Timer::start("Rendering... ");
	Mat img = pScene->render(std::make_shared<CSamplerStratified>(4), 64);
	Timer::stop();
	imshow("image", img);
	imwrite("D:\\renders\\area-3bounces.jpg", img);
	waitKey();
	return 0;
}

int main3d()
{
	const float intencity = 1.0f;
	const float h = 2.0f;
	const float l = 10.0f;
	const float length = 2 * l;
	const float A = atanf(l / h);
	
	const Vec3f O(0, 0, 0);
	const Vec3f normal(0, 0, 1);

	const size_t nSamples = 1000;

	

	// Integral over light source
	float Sum1 = 0;
	const float dl = 2 * l / nSamples;
	for (size_t y = 0; y <= nSamples; y++) {
		for (size_t x = 0; x < nSamples; x++) {
			Vec3f p(-l + dl * x, -l + dl * y, h);
			Vec3f dir = p - O;
			double t = norm(dir);
			dir = normalize(dir);

			float cosAlpha = dir.dot(normal);

			Sum1 += cosAlpha * cosAlpha * intencity * length * length / static_cast<float>(t * t);
		}
	}
	Sum1 *= 1.0f / (nSamples * nSamples);
	

	// Integral over all directions	
	float Sum2 = 0;
	const float dPhi	= 2 * Pif / nSamples;
	const float dTheta	= 0.5f * Pif / nSamples;
	for (size_t sPhi = 0; sPhi <= nSamples; sPhi++) {
		float phi = sPhi * dPhi;
		for (size_t sTheta = 0; sTheta <= nSamples; sTheta++) {
			float theta = sTheta * dTheta;

			float z = cosf(theta);
			Vec3f dir(sinf(theta) * cosf(phi), sinf(theta) * sinf(phi), z);
			if (z > 0) {
				float m = h / z;
				dir = dir * m;

				float x = O.val[0] + dir.val[0];
				float y = O.val[1] + dir.val[1];

				if (x >= -l && x <= l && y >= -l && y <= l)
					Sum2 += intencity * cosf(theta) * sinf(theta);
			}

		}
	}
	Sum2 *= Pif * Pif / (nSamples* nSamples);
	
	//for (size_t s = 0; s <= nSamples; s++) {
	//	float omega = dOmega * s;
	//	

	//	if (omega >= atan2f(h, l - O.val[0]) && omega <= atan2f(h, -l - O.val[0])) {
	//		float alpha = Pif / 2 - omega;
	//		Sum2 += intencity * cosf(alpha);
	//	}
	//	
	//	//if (fabs(alpha) < A)
	//	//	Sum2 += intencity * cosf(alpha);

	//}
	//Sum2 *= Pif / (nSamples + 1);
	
	printf("Integrals: %f; %f\n", Sum1, Sum2);

	return 0;
}