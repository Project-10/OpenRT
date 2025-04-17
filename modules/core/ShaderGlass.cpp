#include "ShaderGlass.h"
#include "BRDFLambertian.h"
#include "BRDFPhong.h"
#include "BRDFSpecularReflection.h"
#include "BSDFSpecularTransmission.h"

rt::CShaderGlass::CShaderGlass(const CScene& scene, float refractiveIndex) : CNewShader(scene, RGB(140, 166, 179))
{
	addBSDF(std::make_shared<CBRDFLambertian>(), 0.1f);
	addBSDF(std::make_shared<CBRDFPhong>(80.0f), 2.0f);
	addBSDF(std::make_shared<CBRDFSpecularTransmission>(refractiveIndex), 0.8f);
	addBSDF(std::make_shared<CBRDFSpecularReflection>(), 0.2f);
}