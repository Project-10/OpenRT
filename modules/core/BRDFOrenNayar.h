// Oren-Nayar BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "BxDF.h"

#pragma once

namespace rt {

	// ================================ Oren-Nayar BRDF Interface Class ================================
	/**
	 * @brief Oren-Nayar BRDF interface class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFOrenNayar : public CBxDF
	{
	public:
		/**
		 * @brief Constructor
		 * @param sigma The standard deviation of the microfacet orientation angle in degrees. 0° gives Lambertian model. 90° gives maximum effect.
		 */
		DllExport CBRDFOrenNayar(float sigma = 20.0f);
		DllExport virtual ~CBRDFOrenNayar(void) = default;

		DllExport float		f(const Vec3f& wo, const Vec3f& wi) const override;


	private:
		float m_A;	///< Oren-Nayar BRDF parameter (is calculated in the class constructor)
		float m_B;	///< Oren-Nayar BRDF parameter (is calculated in the class constructor)
	};
}