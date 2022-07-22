//
//  Created by Mahmoud El Bergui on 21.04.22.
//

#include "Texture.h"
#include "Gradient.h"

namespace rt {

	class CTextureWood : public CTexture {
	public:
		/**
		 * @brief Constructor
		 * @param period Number of periods
		 */
		DllExport CTextureWood(const CGradient& gradient, float period = 1.0f) : m_gradient(gradient), m_period(period) {}
		DllExport virtual ~CTextureWood(void) = default;
     
		DllExport Vec3f getTexel(const Vec3f &uvw) const override;
		DllExport bool isProcedural(void) const override { return true; }
     
     
	private:
		CGradient	m_gradient;		///< The color gradient for the wood
		float		m_period;		///< Period of the rings
	};
}
