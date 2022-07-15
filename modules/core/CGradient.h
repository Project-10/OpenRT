//  Created by Mahmoud El Bergui on 12.07.22.

#pragma once
#pragma once

#include "types.h"

namespace rt{
	class CGradient{
	public:
		/**
		* @brief Defines the borders of the color gradient
		* @param color0
		* @param color1
		*/
		DllExport CGradient(const Vec3f& color0, const Vec3f& color1);
     
		/**
		@Brief Adds a color and its weight to the gradient vector
		@Details 0 <newcolor's weight<1 because 0 and 1 are already taken
		*/
		DllExport void addColor(const Vec3f& color, float pos);
     
		/**
		@Brief Calculates the gradient of val
		*/
		DllExport Vec3f getColor(float val) const;
     
     
	private:
		 Vec3f m_color0;                                 // RGB color that has a weight value of 0
		 Vec3f m_color1;                                 // RGB color that has a weight value of 1
	//     std::vector<Element> m_colorsVec;                 // Vector that stores the RGB colors and their weight
     
	};
}
