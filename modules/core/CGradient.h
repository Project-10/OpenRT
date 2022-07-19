//  Created by Mahmoud El Bergui on 12.07.22.

#pragma once
#pragma once

#include "types.h"

namespace rt{
	/**
	 * brief Gradient class interpolates between the given golors in range [0; 1]
	 */
	class CGradient{
	public:
		/**
		* @brief Constructor
		* @param color0 Color value for the point 0
		* @param color1 Color point for the point 1
		*/
		DllExport CGradient(const Vec3f& color0 = Vec3f::all(0), const Vec3f& color1 = Vec3f::all(1)) : m_mColors({{0, color0}, {1, color1}}) {}
		/**
		* @brief Constructor
		* @param colors The map with colors and their positions
		* @warning Take care to assign a color for points 0 and 1
		*/
		DllExport CGradient(const std::map<float, Vec3f>& colors) : m_mColors(colors) {}
		DllExport CGradient(const CGradient&) = delete;
		DllExport ~CGradient(void) = default;
		DllExport const CGradient& operator=(const CGradient&) = delete;
     
		/**
		 * @brief Adds a color to gradient
		 * @param pos The point at which the color should be added in range [0; 1]
		 * @param color The color
		 */
		DllExport void addColor(float pos, const Vec3f& color) { m_mColors[pos] = color; }
     
		/**
		 * @brief Returns the color at given point
		 * @param pos The poiint from which the color value should be calculated and returnes
		 * @returns The color value
		 */
		DllExport Vec3f getColor(float pos) const;
     
     
	private:
		std::map<float, Vec3f>	m_mColors;	//< Data container that stores the RGB colors and their positions
	};
}
