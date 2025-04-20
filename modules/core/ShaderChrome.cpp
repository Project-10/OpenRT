#include "ShaderChrome.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"
#include "BRDFGlossy.h"

rt::CShaderChrome::CShaderChrome(const CScene& scene, float roughness, ptr_sampler_t pSampler) 
	: CNewShader(scene, RGB(230, 191, 179))
{
	//addBSDF(std::make_shared<CBRDFOrenNayar>(roughness * 90.0f), 0.5f);
	addBSDF(std::make_shared<CBRDFGlossy>(roughness, pSampler), 1.0f);
}
