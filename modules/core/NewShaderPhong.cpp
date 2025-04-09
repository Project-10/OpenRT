#include "NewShaderPhong.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"
#include "BRDFPhong.h"

rt::CNewShaderPhong::CNewShaderPhong(const CScene& scene, const Vec3f& color, float ka, float kd, float ks, float ke) : CNewShader(scene, color)
{
	add(std::make_shared<CBRDFLambertian>(), kd);
	//add(std::make_shared<CBRDFOrenNayar>(), kd);
	add(std::make_shared<CBRDFPhong>(ke));
	setAmbientColor(Vec3f::all(ka));
	setSpecularLevel(ks);
	// TODO: Now the specular level may be passed eigther throus the scale of the BRDF function, or via setSpecularLevel. We need to set both and sent one of them to 1.
}

rt::CNewShaderPhong::CNewShaderPhong(const CScene& scene, const ptr_texture_t pTexture, float ka, float kd, float ks, float ke) : CNewShader(scene, pTexture)
{
	add(std::make_shared<CBRDFLambertian>(), kd);
	//add(std::make_shared<CBRDFOrenNayar>(), kd);
	add(std::make_shared<CBRDFPhong>(ke));
	setAmbientColor(Vec3f::all(ka));
	setSpecularLevel(ks);
}
