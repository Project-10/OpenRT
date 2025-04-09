#pragma once

#include "ILight.h"
#include "SamplerStratified.h"

namespace rt {
	// ================================ Skylight Class ================================
	/**
	 * @brief Sky light sourse class
	 * @details This class implements the Ambient Occlusion (AO) method which spearheaded by the film industry for emulating the look of true global illumination by using shaders that calculate 
	 * the extent to which an area is occluded, or prevented from receiving incoming light. Used alone, an AO shader, such as the separate mental ray Ambient / Reflective Occlusion shader, 
	 * creates a grayscale output that is dark in areas light cannot reach and bright in areas where it can.
	 * @author Takundey Gora, T.Gora@jacobs-university.de
	 */
	class CLightSky : public ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param maxDistance Defines the radius within which the renderer looks for occluding objects. 
		 * Smaller values restrict the AO effect to small crevices only but are much faster to render. Larger values cover larger areas but render more slowly. 
		 * @param pSampler Pointer to the sampler to be used with the sky light
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSky(Vec3f intensity, float maxDistance = 4, ptr_sampler_t pSampler = nullptr, bool castShadow = true)
			: ILight(intensity, castShadow)
			, m_maxDistance(maxDistance > std::numeric_limits<float>::epsilon() ? maxDistance : std::numeric_limits<float>::infinity())
			, m_pSampler(pSampler)
		{}

		DllExport virtual std::optional<Vec3f>	illuminate(Ray& shadowray, const Vec3f& point, const Vec3f& normal) const override;
		DllExport virtual size_t				getNumSamples(void) const override { return m_pSampler ? m_pSampler->getNumSamples() : 1; }


	private:
		float			m_maxDistance;	///< The radius within which the renderer looks for occluding objects
		ptr_sampler_t	m_pSampler;		///< Pointer to the sampler ref @ref CSampler
	};
}
