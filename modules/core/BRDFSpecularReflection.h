// Specular Reflection BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"

#pragma once

namespace rt {

	class CBRDFSpecularReflection : public IBxDF
	{
	public:
		DllExport CBRDFSpecularReflection(void) : IBxDF(BxDFType::reflection) {}
		DllExport virtual ~CBRDFSpecularReflection(void) = default;
		DllExport virtual float f(const Vec3f& wo, const Vec3f& wi) const { return 0; }
		DllExport float Sample_f(const Vec3f& wo, Vec3f& wi) const override;
	};
}