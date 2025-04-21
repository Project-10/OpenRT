#include "BRDFSpecularReflection.h"

float rt::CBRDFSpecularReflection::Sample_f(const Vec3f& wo, Vec3f& wi, size_t) const 
{
	wi = Vec3f(-wo[0], -wo[1], wo[2]); // Reflected direction in LCS
	return 1.0f;
}