//  Created by Mahmoud El Bergui on 18.04.22.
#pragma once

#include "Texture.h"
#include "Gradient.h"

namespace rt {
	/**
	 * @brief Rings Procedural Texture class
	 * @note This class is an experimental class
	 * @ingroup moduleTexture
	 * @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	 */
	class CTextureRings : public CTexture {
	public:
		/**
		 * @brief Constructor
		 * @ingroup moduleTexture
		 * @param gradient Texture color
		 * @param period The number of rings per 1 unit of WCS
		 */
		DllExport CTextureRings(const CGradient& gradient, float period) : m_gradient(gradient), m_period(period) {}
		DllExport virtual ~CTextureRings(void) = default;
    
		DllExport Vec3f	getTexel(const Ray& ray) const override;


	private:
		CGradient	m_gradient;		///< The color gradient for the wood
		float 		m_period;		///< The number of rings per 1 unit of WCS
	};
}
