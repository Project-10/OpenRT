//
//  Created by Mahmoud El Bergui on 21.04.22.
//


#include"Texture.h"


namespace rt {

     class CTextureWood : public CTexture{
     
          public:
     /**  @brief wood constructor
          @param Number of periods
     */
     DllExport CTextureWood(float period) : m_period(period) {}
     
     DllExport virtual ~CTextureWood(void) = default;
     
     /**  @brief Returns the texture element with coordinates \b (uvw)
      *   @param uv The textel coordinates in World space
      *   @return The texture elment (color)
      */
     DllExport Vec3f getTexel(const Vec3f &uvw) const override;
     
     /**   @Brief Checks if we are dealing with procedural textiures
     */
     DllExport bool isProcedural(void) const override { return true; }
     /**  @Brief Function to interpolate between pillar two wood colors
          @param value value that we want to map
          @return mapped color
     */
     DllExport Vec3f woodMap(float value) const;


	private:
		float m_period;///<Period of the rings
  };
}
