// Lambertian BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"

#pragma once

namespace rt {

	// ================================ Lambertian BRDF Interface Class ================================
	/**
	 * @brief Lambertian BRDF interface class
	 * @ingroup moduleBxDF
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFLambertian : public IBxDF
	{
	public:
		DllExport CBRDFLambertian(void) : IBxDF(BxDFType::diffuse) {}
		DllExport virtual ~CBRDFLambertian(void) = default;

		DllExport virtual float f(const Vec3f& wo, const Vec3f& wi) const override;
	};
}