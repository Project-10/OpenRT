#pragma once

#include "Texture.h"
#include "Gradient.h"

namespace rt {
	class CGradient;
/**
	 * @brief Stripes Procedural Texture class
	 * @note This class is an experimental class
	 * @ingroup moduleTexture
	 * @author Mahmoud El Bergui, m.elbergui@jacobs-university.de
	 */
	class CTextureStripes : public CTexture {
	public:
		/**
		 * @brief Constructor
		 * @ingroup moduleTexture
		 * @param gradient Texture color
		 * @param period The number of stripes per 1 unit of WCS
		 */
		DllExport CTextureStripes(const CGradient& gradient, float period) : m_gradient(gradient), m_period(period) {}
		DllExport virtual ~CTextureStripes(void) = default;
    
		DllExport Vec3f	getTexel(const Ray& ray) const override;


	private:
		CGradient	m_gradient;		///< The color gradient for the wood
		float 		m_period;		///< The number of stripes per 1 unit of WCS
	};
}
