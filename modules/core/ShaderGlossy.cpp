#include "ShaderGlossy.h"
#include "BRDFSpecularReflection.h"
#include "BRDFGlossy.h"

rt::CShaderGlossy::CShaderGlossy(const CScene& scene, const Vec3f& color, float roughness, ptr_sampler_t pSampler)
	: CNewShader(scene, Vec3f::all(0))
{
	if (roughness < Epsilon) addBSDF(std::make_shared<CBRDFSpecularReflection>());
	else {
		addBSDF(std::make_shared<CBRDFGlossy>(roughness, pSampler));
	}
	setReflectColor(color);
}

rt::CShaderGlossy::CShaderGlossy(const CScene& scene, const ptr_texture_t pTexture, float roughness, ptr_sampler_t pSampler)
	: CNewShader(scene, Vec3f::all(0))
{
	if (roughness < Epsilon) addBSDF(std::make_shared<CBRDFSpecularReflection>());
	else {
		addBSDF(std::make_shared<CBRDFGlossy>(roughness, pSampler));
	}
	setReflectColor(pTexture);
}
