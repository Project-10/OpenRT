#include "ShaderPhong.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"
#include "BRDFPhong.h"

rt::CShaderPhong::CShaderPhong(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke) : CNewShader(scene, color)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(90.0f), kd);
	addBSDF(std::make_shared<CBRDFPhong>(ke), ks);
	setAmbientColor(Vec3f::all(ka));
	// TODO: Now the specular level may be passed eigther throus the scale of the BRDF function, or via setSpecularLevel. We need to set both and sent one of them to 1.
}

rt::CShaderPhong::CShaderPhong(const CScene& scene, const ptr_texture_t pTexture, float ka, float kd, float ks, float ke) : CNewShader(scene, pTexture)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(), kd);
	addBSDF(std::make_shared<CBRDFPhong>(ke), ks);
	setAmbientColor(pTexture, 1.0f);
}
