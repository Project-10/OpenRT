#include "ShaderBlinn.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"
#include "BRDFBlinn.h"

rt::CShaderBlinn::CShaderBlinn(const CScene& scene, const Vec3f& color, float kd, float ks, float ke) : CNewShader(scene, color)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(), kd);
	addBSDF(std::make_shared<CBRDFBlinn>(4 * ke), ks);
}

rt::CShaderBlinn::CShaderBlinn(const CScene& scene, const ptr_texture_t pTexture, float kd, float ks, float ke) : CNewShader(scene, pTexture)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(), kd);
	addBSDF(std::make_shared<CBRDFBlinn>(4 * ke), ks);
}
