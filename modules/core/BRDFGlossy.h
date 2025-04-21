// Glossy BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"
#include "Sampler.h"

#pragma once

namespace rt {
	// ================================ Glossy BRDF Interface Class ================================
	/**
	 * @brief Glossy BRDF interface class
	 * @details The Glossy BRDF is used to add reflection with microfacet distribution, used for materials such as metal or mirrors.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFGlossy : public IBxDF
	{
	public:
		/**
		 * @brief Constructor
		 * @param roughness Input for the surface roughness resulting in sharp to blurry reflections.
		 * @param pSampler Pointer to the sampler to be used for perturbing the shape normal during shading.
		 */
		DllExport CBRDFGlossy(float roughness, ptr_sampler_t pSampler = nullptr);
		DllExport virtual ~CBRDFGlossy(void) = default;
		DllExport virtual float		f(const Vec3f& wo, const Vec3f& wi) const;
		DllExport virtual float		Sample_f(const Vec3f& wo, Vec3f& wi, size_t s) const override;

	
	private:
		float			m_roughness;	///< The surface roughness
		ptr_sampler_t	m_pSampler;		///< Pointer to the sampler to be used for sampling the hemisphere around the shading point
	};
}