#include "NewShaderMirror.h"
#include "BRDFSpecularReflection.h"

#include "BRDFPhong.h"
#include "BRDFLambertian.h"

rt::CNewShaderMirror::CNewShaderMirror(const CScene& scene) : CNewShader(scene, Vec3f::all(0))
{
	add(std::make_shared<CBRDFSpecularReflection>());
}