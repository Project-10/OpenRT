// Camera Abstract Interface class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"

namespace rt {
	struct Ray;
	// ================================ Camera Interface Class ================================
	/**
	 * @brief Basic camera abstract interface class
	 * @ingroup moduleCamera
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class ICamera
	{
	public:
		/**
		 * @brief Constructor
		 * @param resolution The resolution of the camera in pixels
		 */
		DllExport ICamera(Size resolution) 
			: m_resolution(resolution)
			, m_aspectRatio(static_cast<float>(resolution.width) / resolution.height) 
		{}
		DllExport ICamera(const ICamera&) = delete;
		DllExport virtual ~ICamera(void) = default;
		DllExport const ICamera& operator=(const ICamera&) = delete;
		
		/**
		 * @brief Initializes a ray \b ray passing trough a screen pixel with coordinates \b x anf \b y
		 * @details This function initializes the ray pointing from the camera origin to the pixel
		 * on the camera screen defyned by the coodrinates \b (x,y). The pixel coordinates need to lie
		 * in the ranges of camera resolution.
		 * @param[out] ray Reference to the @ref Ray structure to be filled
		 * @param[in] x The x-coordinate of the pixel lying on the camera screen
		 * @param[in] y The y-coordinate of the pixel lying on the camera screen
		 * @param[in] sample The x- and y-shifts to the center of the pixel (used for anti-aliasing).
		 */
		DllExport virtual void InitRay(Ray& ray, int x, int y, const Vec2f& sample = Vec2f::all(0.5f)) = 0;
		/**
		 * @brief Returns the camera's x-axis
		 * @return The camra x-axis in WCS
		 */
		DllExport virtual Vec3f getXAxis(void) const = 0;
		/**
		 * @brief Returns the camera's y-axis
		 * @return The camra y-axis in WCS
		 */
		DllExport virtual Vec3f	getYAxis(void) const = 0;
		/**
		 * @brief Returns the camera's z-axis
		 * @return The camra z-axis in WCS
		 */
		DllExport virtual Vec3f	getZAxis(void) const = 0;
		
		/**
		 * @brief Retuns the camera resolution in pixels
		 * @return The camera resolution in pixels
		 */
		DllExport Size getResolution(void) const { return m_resolution; }
		/**
		 * @brief Returns the camera aspect ratio 
		 * @return The camera aspect ratio
		 */
		DllExport float getAspectRatio(void) const { return m_aspectRatio; }
		

	private:
		const Size	m_resolution;	///< Camera image resolution in pixels
		const float	m_aspectRatio;	///< Camera image aspect ratio
	};

	using ptr_camera_t = std::shared_ptr<ICamera>;
}
