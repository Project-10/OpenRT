//  Created by Mahmoud El Bergui on 18.04.22.
//
#pragma once

#include"Texture.h"

namespace rt{
//	class CTextureRings : public CTexture{
//		public:
//		DllExport CTextureRings(float period) : m_period(period) {}
//		DllExport virtual ~CTextureRings(void) = default;
//    
//
//		DllExport Vec3f getTexel(const Vec3f &uvw) const override;
//    
//		DllExport bool isProcedural(void) const override { return true; }
//
//
//	private:
//		float m_period;
  
     class CTextureRings : public CTexture{
     
          public:
     DllExport CTextureRings(float period) : m_period(period) {}
     DllExport virtual ~CTextureRings(void) = default;
    

     DllExport Vec3f getTexel(const Vec3f &uvw) const override;
    
     DllExport bool isProcedural(void) const override { return true; }
     

	private:
		float m_period;
	};
}
