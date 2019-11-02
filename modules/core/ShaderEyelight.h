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
		DllExport CShaderEyelight(Vec3f color = RGB(0.5f, 0.5f, 0.5f))
			: CShaderFlat(color)
		{}
		DllExport virtual ~CShaderEyelight(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override
		{
			return CShaderFlat::shade() * fabs(ray.dir.dot(ray.hit->getNormal(ray)));
		}
	};
}
