#pragma once

#include "IShader.h"
#include "ray.h"

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
		DllExport virtual ~CShaderFlat(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray = Ray()) const override { return m_color; }


	private:
		Vec3f m_color;
	};
}
