#include "BRDFSpecularReflection.h"

float rt::CBRDFSpecularReflection::Sample_f(const Vec3f& wo, Vec3f& wi) const 
{
	wi = Vec3f(-wo[0], -wo[1], wo[2]);
	return 1.0f;
}