#pragma once

#include "ShaderFlat.h"

namespace rt {
	/**
	 * @brief Eye-light shader class
	 */
	class CShaderEyelight : public CShaderFlat
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free and light-source-free shader
		 * @param scene Reference to the scene
		 * @param color The color of the object
		 */
		CShaderEyelight(Vec3f color = RGB(0.5f, 0.5f, 0.5f))
			: CShaderFlat(color)
		{}
		virtual ~CShaderEyelight(void) = default;

		virtual Vec3f Shade(const Ray& ray) const override
		{
			// --- PUT YOUR CODE HERE ---
			return RGB(0, 0, 0);
		}
	};
}
