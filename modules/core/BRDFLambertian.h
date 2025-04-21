// Lambertian BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "BxDF.h"

#pragma once

namespace rt {
	// ================================ Lambertian BRDF Interface Class ================================
	/**
	 * @brief Lambertian BRDF interface class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFLambertian : public CBxDF
	{
	public:
		DllExport CBRDFLambertian(void);
		DllExport virtual ~CBRDFLambertian(void) = default;

		DllExport float		f(const Vec3f& wo, const Vec3f& wi) const override;
	};
}