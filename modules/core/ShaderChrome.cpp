#include "ShaderChrome.h"
#include "BRDFLambertian.h"
#include "BRDFChrome.h"

rt::CShaderChrome::CShaderChrome(const CScene& scene, ptr_sampler_t pSampler) : CNewShader(scene, RGB(255, 200, 200)) {
	addBSDF(std::make_shared<CBRDFLambertian>(), 0.2f);
	addBSDF(std::make_shared<CBRDFChrome>(pSampler), 0.8f);
}
