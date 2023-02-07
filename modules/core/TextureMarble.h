//  Created by Mahmoud El Bergui on 21.04.22.
#pragma once

#include "Texture.h"
#include "Gradient.h"
#include "PerlinNoise.h"

namespace rt {
	/**
	* @brief Marble procedural texture class
	* @details This class is based on the stripes (@ref CTextureStripes) class
	* @ingroup moduleTexture
	* @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	*/
	class CTextureMarble : public CTexture {
	public:
		/**  
		 * @brief Marble texture contructor
		 * @param gradient Texture color
		 * @param period The number of stripes per 1 unit of WCS
		 * @param pNoise Pointer to the Perlin Noise function (ref. @ref CPrelinNoise) 
 		 */
		DllExport CTextureMarble(const CGradient& gradient, float period, ptr_perlin_t pNoise = nullptr)
			: m_gradient(gradient)
			, m_period(period)
			, m_pNoise(pNoise)
		{}
		DllExport virtual ~CTextureMarble(void) = default;
     
		DllExport Vec3f	getTexel(const Ray& ray) const override;
    
     
	private:
		CGradient		m_gradient;		///< The color gradient for the wood
		float			m_period;		///< The period of the noise
		ptr_perlin_t	m_pNoise;		///< The Perlin Noise
	};
}
