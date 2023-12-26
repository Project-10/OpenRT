#pragma once

#include "Texture.h"
#include "Gradient.h"
#include "PerlinNoise.h"

namespace rt {
	class CGradient;
/**
	 * @brief Stripes Procedural Texture class
	 * @ingroup moduleTexture
	 * @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	 */
	class CTextureStripes : public CTexture {
	public:
		/**
		 * @brief Constructor
		 * @param gradient Texture color
		 * @param period The number of stripes per 1 unit of WCS
		 * @param pNoise Pointer to the Perlin Noise function (ref. @ref CPrelinNoise)
		 */
		DllExport CTextureStripes(const CGradient& gradient, float period, ptr_perlin_t pNoise = nullptr)
			: m_gradient(gradient)
			, m_period(period) 
			, m_pNoise(pNoise)
		{}
		DllExport virtual ~CTextureStripes(void) = default;
    
		DllExport Vec3f	getTexel(const Ray& ray) const override;


	private:
		CGradient		m_gradient;		///< The color gradient for the wood
		float 			m_period;		///< The number of stripes per 1 unit of WCS
		ptr_perlin_t	m_pNoise;		///< The Perlin Noise
	};
}
