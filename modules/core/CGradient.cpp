//  Created by Mahmoud El Bergui on 12.07.22.

#include "CGradient.h"
#include "macroses.h"

namespace rt{

namespace{

Vec3f mix(const Vec3f& C0, const Vec3f& C1, float f)
{
     return (1 - f) * C0 + f * C1;
}


}

float Element::getWeight(){
     return this->m_weight;
}

Vec3f Element::getColor(){
     return this->m_color;
}

//Add color in the vector considering its weight with respect to the other element's weights
void CGradient::addColor(Element newColor){
     float weight = newColor.getWeight();
     Vec3f color = newColor.getColor();
     for (int it = 0; it < m_colorsVec.size(); it++) {
          if (m_colorsVec[it].getWeight() < weight) {
               m_colorsVec.insert(m_colorsVec.begin() + it + 1, newColor);
               break;
          }
          
          if(m_colorsVec[it].getWeight() == weight || m_colorsVec[it].getColor() == color){
               RT_ASSERT_MSG(false, "Weight or color already mentioned, please change");
          }
          
     }
}

//Calculate color gradient
Vec3f CGradient::getColorGradient(float val){
     std::vector<Element>::iterator it;
     
     for (int it = 0; it < m_colorsVec.size(); it++) {
          if (val > 1 || val < 0) {
               RT_ASSERT_MSG(false, "Val problem");
          }
          if(val > m_colorsVec[it].getWeight()  && val < m_colorsVec[it+1].getWeight()){
               return mix(m_colorsVec[it].getColor() , m_colorsVec[it+1].getColor() , val);
          }
          
          if (val == 1) {
               return m_colorsVec[it+m_colorsVec.size()-1].getColor();
          }
          
          else return m_colorsVec[0].getColor();
     }
     
     
}
}
