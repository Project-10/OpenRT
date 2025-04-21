#include "ShaderPrincipled.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"
#include "BRDFPhong.h"
#include "BRDFBlinn.h"
#include "BRDFSpecularReflection.h"
#include "BTDFSpecularTransmission.h"

rt::CShaderPrincipled::CShaderPrincipled(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke, float km, float kt, float refractiveIndex, ptr_sampler_t pSampler)
	: CNewShader(scene, color)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(20.0f), kd);
	addBSDF(std::make_shared<CBRDFPhong>(ke), ks);
	addBSDF(std::make_shared<CBRDFSpecularReflection>(), km);
	addBSDF(std::make_shared<CBTDFSpecularTransmission>(refractiveIndex), kt);
}

rt::CShaderPrincipled::CShaderPrincipled(const CScene& scene, const ptr_texture_t pTexture, float ka, float kd, float ks, float ke, float km, float kt, float refractiveIndex, ptr_sampler_t pSampler)
	: CNewShader(scene, pTexture)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(20.0f), kd);
	addBSDF(std::make_shared<CBRDFPhong>(ke), ks);
	addBSDF(std::make_shared<CBRDFSpecularReflection>(), km);
	addBSDF(std::make_shared<CBTDFSpecularTransmission>(refractiveIndex), kt);
}
