#include "ShaderPhong.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"
#include "BRDFPhong.h"

rt::CShaderPhong::CShaderPhong(const CScene& scene, const Vec3f& color, float kd, float ks, float ke) : CNewShader(scene, color)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(90.0f), kd);
	addBSDF(std::make_shared<CBRDFPhong>(ke), ks);
}

rt::CShaderPhong::CShaderPhong(const CScene& scene, const ptr_texture_t pTexture, float kd, float ks, float ke) : CNewShader(scene, pTexture)
{
	addBSDF(std::make_shared<CBRDFLambertian>(), kd);
	//addBSDF(std::make_shared<CBRDFOrenNayar>(), kd);
	addBSDF(std::make_shared<CBRDFPhong>(ke), ks);
}
