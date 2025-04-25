// Shader Abstract Interface class
// Written by Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "types.h"

namespace rt {
	struct Ray;
	// ================================ Shader Interface Class ================================
	/**
	 * @brief Basic shader abstract interface class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class IShader
	{
	public:
		DllExport IShader(void) = default;
		DllExport IShader(const IShader&) = delete;
		DllExport virtual ~IShader(void) = default;
		DllExport const IShader& operator=(const IShader&) = delete;

		/**
		 * @brief Calculates the color of the hit by the ray \b ray object
		 * @param ray The ray hitting the primitive. ray.hit must point to the primitive
		 * @return The color of the hit objesct
		 */
		DllExport virtual Vec3f shade(const Ray& ray) const = 0;
		/**
		 * @brief Returns the opacity of the hit by the ray \b ray object
		 * @param ray The ray hitting the primitive. ray.hit must point to the primitive
		 * @return The opacity value
		 */
		DllExport virtual float getOpacity(const Ray& ray) const = 0;
	};

	using ptr_shader_t = std::shared_ptr<IShader>;
}
