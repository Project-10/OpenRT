#pragma once

#include "IShader.h"

namespace rt {
	/**
	 * @brief Flat shader class
	 */
	class CShaderFlat : public IShader
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free and light-source-free shader
		 * @param color The color of the object
		 */
		DllExport CShaderFlat(Vec3f color = RGB(0.5f, 0.5f, 0.5f)) : m_color(color) {}
	  
		DllExport virtual Vec3f Shade(const Ray& ray = Ray()) const override
		{
			// --- PUT YOUR CODE HERE ---
			return RGB(0, 0, 0);
		}

	private:
		Vec3f m_color;
	};
}
