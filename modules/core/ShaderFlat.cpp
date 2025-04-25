#include "ShaderFlat.h"

Vec3f rt::CShaderFlat::shade(const Ray&) const 
{
	return m_color;
}
	
float rt::CShaderFlat::getOpacity(const Ray&) const
{
	return m_castShadow ? 1.0f : 0.0f;
}

