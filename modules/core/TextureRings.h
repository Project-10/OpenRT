//
//  Rings.hpp
//  Demo_AreaLight
//
//  Created by Mahmoud El Bergui on 18.04.22.
//
#pragma once

#include"Texture.h"

namespace rt{
class CTextureRings : public CTexture{
public:
     DllExport CTextureRings(float period) : m_period(period) {}
     DllExport virtual ~CTextureRings(void) = default;
     
     /**
      @brief Returns the texture element with coordinates \b (uvw)
      @param uv The textel coordinates in World space
      @return The texture elment (color)
      */
     DllExport Vec3f getTexel(const Vec3f &uvw) const override;
     
     DllExport bool isProcedural(void) const override { return true; }
     
     
private:
     float m_period;
};
}
