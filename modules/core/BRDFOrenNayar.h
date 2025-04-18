// Oren-Nayar BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"

#pragma once

namespace rt {

	// ================================ Oren-Nayar BRDF Interface Class ================================
	/**
	 * @brief Oren-Nayar BRDF interface class
	 * @ingroup moduleBxDF
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFOrenNayar : public IBxDF
	{
	public:
		DllExport CBRDFOrenNayar(float sigma = 20.0f);
		DllExport virtual ~CBRDFOrenNayar(void) = default;

		DllExport virtual float		f(const Vec3f& wo, const Vec3f& wi) const override;
		DllExport virtual float		Sample_f(const Vec3f& wo, Vec3f& wi) const override { return 0; }
		DllExport virtual size_t	getNumSamples(void) const override { return 0; }


	private:
		float m_A;
		float m_B;
	};
}