#pragma once

#include "types.h"

namespace rt {
	struct Ray;

	/**
	 * @brief Base shader abstract interface class
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
		 * @param ray The ray hitting the primitive
		 * @return The color of the hit objesct
		 */
		DllExport virtual Vec3f shade(const Ray& ray) const = 0;
	};

	using ptr_shader_t = std::shared_ptr<IShader>;
}
