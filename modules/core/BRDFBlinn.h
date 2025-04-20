// Blinn BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"

#pragma once

namespace rt {

	// ================================ Blinn BRDF Interface Class ================================
	/**
	 * @brief Blinn specular BRDF interface class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFBlinn : public IBxDF
	{
	public:
		/**
		 * @brief Constructor
		 * @param ke The shininess exponent
		 */
		DllExport CBRDFBlinn(float ke);
		DllExport virtual ~CBRDFBlinn(void) = default;

		DllExport virtual float		f(const Vec3f& wo, const Vec3f& wi) const override;
		DllExport virtual float		Sample_f(const Vec3f& wo, Vec3f& wi) const override;


	private:
		float m_ke;		///< The shininess exponent
	};
}