// Specular Reflection BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"

#pragma once

namespace rt {
	// ================================ Specular Reflection BRDF Interface Class ================================
	/**
	 * @brief Perfect specular reflection BRDF interface class
	 * @details This BRDF is used to model mirror reflection
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFSpecularReflection : public IBxDF
	{
	public:
		DllExport CBRDFSpecularReflection(void) : IBxDF(BxDFType::reflection, 1) {}
		DllExport virtual ~CBRDFSpecularReflection(void) = default;
		DllExport virtual float		f(const Vec3f& wo, const Vec3f& wi) const { return 0; }
		DllExport virtual float		Sample_f(const Vec3f& wo, Vec3f& wi) const override;
	};
}