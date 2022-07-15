//  Created by Mahmoud El Bergui on 12.07.22.

#include "CGradient.h"
#include "macroses.h"

namespace rt {

	// Constructor
	CGradient::CGradient(const Vec3f& color0, const Vec3f& color1) 
		: m_color0(color0)
		, m_color1(color1)
	{
		//if (color1.getWeight() != 0 || color2.getWeight() != 1)
		//	RT_ASSERT_MSG(false, "First and second elements should always have a weight value of 0 and 1 respectively");
		//m_colorsVec.push_back(Element(color1));
		//m_colorsVec.push_back(Element(color2));
	};


	void CGradient::addColor(const Vec3f& color, float pos)
	{
		 //float weight = newColor.getWeight();
		 //Vec3f color = newColor.getColor();
		 //for (int it = 0; it < m_colorsVec.size(); it++) {
			//  if (m_colorsVec[it].getWeight() < weight) {
			//	   m_colorsVec.insert(m_colorsVec.begin() + it + 1, newColor);
			//	   break;
			//  }
   //       
			//  if(m_colorsVec[it].getWeight() == weight || m_colorsVec[it].getColor() == color){
			//	   RT_ASSERT_MSG(false, "Weight or color already mentioned, please change");
			//  }
   //       
		 //}
	}


	Vec3f CGradient::getColor(float val) const
	{
		// These 2 lines are for debugging
		if (val < 0) return RGB(0, 0, 255);
		if (val > 1) return RGB(255, 0, 0);
		
		return (1 - val) * m_color0 + val * m_color1;

		 //std::vector<Element>::iterator it;
   //  
		 //for (int it = 0; it < m_colorsVec.size(); it++) {
			//  if (val > 1 || val < 0) {
			//	   RT_ASSERT_MSG(false, "Val problem");
			//  }
			//  if(val > m_colorsVec[it].getWeight()  && val < m_colorsVec[it+1].getWeight()){
			//	   return mix(m_colorsVec[it].getColor() , m_colorsVec[it+1].getColor() , val);
			//  }
   //       
			//  if (val == 1) {
			//	   return m_colorsVec[it+m_colorsVec.size()-1].getColor();
			//  }
   //       
			//  else return m_colorsVec[0].getColor();
		 //}
	}
}
