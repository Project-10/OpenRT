// Chrome BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"
#include "Sampler.h"

#pragma once

namespace rt {

	class CBRDFChrome : public IBxDF
	{
	public:
		DllExport CBRDFChrome(ptr_sampler_t pSampler = nullptr);
		DllExport virtual ~CBRDFChrome(void) = default;
		DllExport virtual float		f(const Vec3f& wo, const Vec3f& wi) const;
		DllExport virtual float		Sample_f(const Vec3f& wo, Vec3f& wi) const override;
		DllExport virtual size_t	getNumSamples(void) const override;

	
	private:
		ptr_sampler_t	m_pSampler;		///< Pointer to the sampler to be used for sampling the hemisphere around the shading point
	};
}