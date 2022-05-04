//  Created by Mahmoud El Bergui on 21.04.22.
//

#include "TextureMarble.h"
#include "PerlinNoise.h"

namespace rt{


	Vec3f CTextureMarble::getTexel(const Vec3f& uvw) const
	{
		//Getting coordinate info
		float u = uvw.val[0];
		float v = uvw.val[1];
		float w = uvw.val[2];
  
          CPerlinNoise pn;
          double t =  pn.turbulence(u, v, w , m_octaves, m_frequency , m_amplitude , m_lacunarity, m_persistence);
          Vec3f color;
           if (m_weird ==  true) {
               t = t - floor(t);
               color = marbleMap(abs(sin(t)));
           }
           else
               color = marbleMap(abs(sin(0.5*u + t)));

         //Vec3f color = marbleMap(abs(t));
          Vec3f white = Vec3f::all(1);
          color = mix(color, white, 0.2);
                    
          return color;
               
     }
 
     Vec3f CTextureMarble::marbleMap(float value) const{
               
          Vec3f white = Vec3f(1,1,1);
          Vec3f blue = Vec3f(0.6 , 0.53 , 0.467);
          Vec3f color = (Vec3f) ((white - blue) * value + blue);
               
               return color;
     }
     
     double CTextureMarble::smoothstep(float val) const{
          return val * val * val *(val * (val * 6 -15) + 10);
     }
     
         Vec3f CTextureMarble::mix(Vec3f& C0, Vec3f& C1, float f ) const{
        
        return (1-f) * C0 + f * C1;
    }
    
    float CTextureMarble::step(float x, float a) const{
          return (float) (x>a);
    }
}
