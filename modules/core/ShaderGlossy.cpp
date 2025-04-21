#include "ShaderGlossy.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"
#include "BRDFGlossy.h"

rt::CShaderGlossy::CShaderGlossy(const CScene& scene, const Vec3f& color, float roughness, ptr_sampler_t pSampler)
	: CNewShader(scene, color)
{
	//addBSDF(std::make_shared<CBRDFOrenNayar>(roughness * 90.0f), 0.5f);
	addBSDF(std::make_shared<CBRDFGlossy>(roughness, pSampler), 1.0f);
}

rt::CShaderGlossy::CShaderGlossy(const CScene& scene, const ptr_texture_t pTexture, float roughness, ptr_sampler_t pSampler)
	: CNewShader(scene, pTexture)
{
	//addBSDF(std::make_shared<CBRDFOrenNayar>(roughness * 90.0f), 0.5f);
	addBSDF(std::make_shared<CBRDFGlossy>(roughness, pSampler), 1.0f);
}
