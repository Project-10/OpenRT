#include "ShaderMirror.h"
#include "BRDFSpecularReflection.h"

rt::CShaderMirror::CShaderMirror(const CScene& scene) : CNewShader(scene, Vec3f::all(0))
{
	addBSDF(std::make_shared<CBRDFSpecularReflection>());
}