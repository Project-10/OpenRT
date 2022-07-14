//  Created by Mahmoud El Bergui on 12.07.22.

#pragma once
#include <stdio.h>
#include "Texture.h"
#include<list>
#include<vector>
#include"macroses.h"

namespace rt{

/**
 @Brief this small class is used to define the one instance of the m_colorsVec
 */
class Element{
public:
     /**
      @Brief Creates an instance with a color and its weight
      */
     DllExport Element(Vec3f color , float val): m_color(color) , m_weight(val){
          if (m_weight > 1 || m_weight < 0 )
               RT_ASSERT_MSG(false,"Weight should be between 0 and 1");
     };
     
     /**
      @Brief get the weight of the element
      */
     float getWeight();
     
     /**
      @Brief get the color of the element
      */
     Vec3f getColor();
     
private:
     Vec3f m_color;
     float m_weight;
};


class CGradient{
public:
     /**
      @Brief Defines the borders of the color gradient
      */
     DllExport CGradient(Element color1 , Element color2 , float val):
     m_color1(color1), m_color2(color2) , m_val(val)
     {
          if(color1.getWeight() != 0 || color2.getWeight() != 1)
               RT_ASSERT_MSG(false, "First and second elements should always have a weight value of 0 and 1 respectively");
          m_colorsVec.push_back(Element(color1));
          m_colorsVec.push_back(Element(color2));
     };
     
     /**
      @Brief Adds a color and its weight to the gradient vector
      @Details 0 <newcolor's weight<1 because 0 and 1 are already taken
      */
     DllExport void addColor(Element newcolor);
     
     /**
      @Brief Calculates the gradient of val
      */
     DllExport Vec3f getColorGradient(float val);
     
     
private:
     Element m_color1;                                 //RGB color that has a weight value of 0
     Element m_color2;                                 //RGB color that has a weight value of 1
     float m_val;                                      //Value of the interpolation
     std::vector<Element> m_colorsVec;                 //Vector that stores the RGB colors and their weight
     
};
}
