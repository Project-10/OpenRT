// Camera Abstract Interface class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ray.h"

namespace rt {
	/**
	 * @brief Basic camera abstract interface class
	 */
	class ICamera
	{
	public:
		/**
		 * @brief Constructor
		 * @param resolution The resolution of the camera
		 */
		ICamera(Size resolution) : m_resolution(resolution) {}
		ICamera(const ICamera&) = delete;
		virtual ~ICamera(void) = default;
		const ICamera& operator=(const ICamera&) = delete;
		
		/**
		 * @brief Initializes the ray
		 * @details This function initializes the ray pointing from the camera origin to the pixel
		 * on the camera screed defyned by the coodrinates \b x and \b y
		 * @param[in] x The x-coordinate of the pixel lying on the camera screen
		 * @param[in] y The y-coordinate of the pixel lying on the camera screen
		 * @param[out] ray Reference to the @ref Ray structure to be filled
		 */
		virtual void InitRay(float x, float y, Ray& ray) = 0;
		
		/**
		 * @brief Retuns the camera resolution
		 * @return The camera resolution
		 */
		Size getResolution(void) const { return m_resolution; }
		
		
	private:
		Size m_resolution;	///< Camera resolution
	};
}
