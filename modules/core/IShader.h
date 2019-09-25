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
		IShader(void) = default;
		IShader(const IShader&) = delete;
		virtual ~IShader(void) = default;
		const IShader& operator=(const IShader&) = delete;

		
		/**
		 * @brief Calculates the color of the hit by the ray \ray object
		 * @param ray The ray
		 * @return The color of the hit objesct
		 */
		virtual Vec3f Shade(const Ray& ray) const = 0;
	};
}
