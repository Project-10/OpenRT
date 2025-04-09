// Specular Transmission BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"

#pragma once

namespace rt {

	class CBRDFSpecularTransmission : public IBxDF
	{
	public:
		/**
		 * @param refractiveIndex The refractive index of the medium (for glass use 1.517)
		 */
		DllExport CBRDFSpecularTransmission(float refractiveIndex) 
			: IBxDF(BxDFType::transmission)
			, m_refractiveIndex(refractiveIndex)
		{}
		DllExport virtual ~CBRDFSpecularTransmission(void) = default;
		DllExport virtual float f(const Vec3f& wo, const Vec3f& wi) const { return 0; }
		DllExport float Sample_f(const Vec3f& wo, Vec3f& wi) const override;


	private:
		float m_refractiveIndex;
	};
}