#include "ShaderBlinn.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"
#include "BRDFBlinn.h"

rt::CShaderBlinn::CShaderBlinn(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke) : CNewShader(scene, color)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(), kd);
	addBSDF(std::make_shared<CBRDFBlinn>(4 * ke));
	setAmbientColor(Vec3f::all(ka));
	setSpecularColor(Vec3f::all(ks));
	// TODO: Now the specular level may be passed eigther throus the scale of the BRDF function, or via setSpecularLevel. We need to set both and sent one of them to 1.
}

rt::CShaderBlinn::CShaderBlinn(const CScene& scene, const ptr_texture_t pTexture, float ka, float kd, float ks, float ke) : CNewShader(scene, pTexture)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(), kd);
	addBSDF(std::make_shared<CBRDFBlinn>(4 * ke));
	setAmbientColor(Vec3f::all(ka));
	setSpecularColor(Vec3f::all(ks));
}
