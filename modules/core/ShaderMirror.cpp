#include "ShaderMirror.h"
#include "BRDFPhong.h"
#include "BRDFSpecularReflection.h"

rt::CShaderMirror::CShaderMirror(const CScene& scene) : CNewShader(scene, Vec3f::all(0))
{
	addBSDF(std::make_shared<CBRDFSpecularReflection>());
	addBSDF(std::make_shared<CBRDFPhong>(250.0f), 0.5f);
}