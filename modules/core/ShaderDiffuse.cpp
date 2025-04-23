#include "ShaderDiffuse.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"

// Constructor
rt::CShaderDiffuse::CShaderDiffuse(const CScene& scene, const Vec3f& color, float roughness) : CNewShader(scene, color)
{
	if (roughness < Epsilon) addBSDF(std::make_unique<CBRDFLambertian>());
	else {
		float sigma = std::min(1.0f, roughness) * 90.0f;
		addBSDF(std::make_shared<CBRDFOrenNayar>(sigma));
	}
}
	
// Constructor
rt::CShaderDiffuse::CShaderDiffuse(const CScene& scene, const ptr_texture_t pTexture, float roughness) : CNewShader(scene, pTexture)
{
	if (roughness < Epsilon) addBSDF(std::make_unique<CBRDFLambertian>());
	else {
		float sigma = std::min(1.0f, roughness) * 90.0f;
		addBSDF(std::make_shared<CBRDFOrenNayar>(sigma));
	}
}
