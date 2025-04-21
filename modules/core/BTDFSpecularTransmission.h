// Specular Transmission BTDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"

#pragma once

namespace rt {
	// ================================ Specular Transmission BTDF Interface Class ================================
	/**
	 * @brief Perfect specular transmission BTDF interface class
	 * @details This BTDF is used to model (semi-)transparant mediums like glass, water, etc.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBTDFSpecularTransmission : public IBxDF
	{
	public:
		/**
		 * @brief Constructor 
		 * @param refractiveIndex The refractive index of the medium (for glass use 1.517)
		 */
		DllExport CBTDFSpecularTransmission(float refractiveIndex);
		DllExport virtual ~CBTDFSpecularTransmission(void) = default;
		DllExport virtual float		f(const Vec3f& wo, const Vec3f& wi) const;
		DllExport virtual float		Sample_f(const Vec3f& wo, Vec3f& wi, size_t s) const override;


	private:
		float m_refractiveIndex;	///< The refractive index of the medium
	};
}