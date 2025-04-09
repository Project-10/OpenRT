// Light Source Abstract Interface class
// Written by Dr. Sergey Kosov in 2019 for Jacobs University
// Modified by Dr. Sergey Kosov in 2024 for Project X
#pragma once

#include "types.h"

namespace rt {
	struct Ray;

	// ================================ Light Interface Class ================================
	/**
	 * @brief Base light source abstract interface class
	 * @ingroup moduleLight
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param castShadow Flag indicating whether the light source casts shadows
		 */
		DllExport ILight(const Vec3f& intensity, bool castShadow) : m_intensity(intensity), m_shadow(castShadow) {}
		DllExport ILight(const ILight&) = delete;
		DllExport virtual ~ILight(void) = default;
		DllExport const ILight& operator=(const ILight&) = delete;

		/**
		 * @brief Calculates and return incident radiance at the point \b point and fills-out the \b shadowray.
		 * @details This method returns incident radiance (L) from the light source at a point \b point 
		 * and also returns the shadoew ray \b shadowray that gives the direction from which radiance is arriving.
		 * @param[out] shadowray The shadow ray from object point given by \b point to the light source
		 * @param[in] point The point of space in WCS to be illuminated
		 * @param[in] normal The normal to the surface at that point (if exists). Some light sources (e.g. Sky light source) may need it
		 * @return The intensity of light hitting the point \b ray.org and the shadow ray \b ray
		 */
		DllExport virtual std::optional<Vec3f>  illuminate(Ray& shadowray, const Vec3f& point, const Vec3f& normal = Vec3f::all(0)) const = 0;
		/**
		 * @brief Returns recommended number of samples for the particular light source implementation
		 * @return The recommended number of samples
		 */
		DllExport virtual size_t				getNumSamples(void) const = 0;
		/**
		 * @brief Sets light source intensity
		 * @param intensity The emission color and strength of the light source
		 */
		DllExport virtual void					setIntensity(const Vec3f& intensity) { m_intensity = intensity; }
		/**
		 * @brief Returns the intensity of the light source
		 * @return The emission color and strength of the light source
		 */
		DllExport Vec3f							getIntensity(void) const { return m_intensity; }
		/**
		 * @brief Flag indicating if the light source casts shadow or not
		 * @retval true If the light source casts shadow
		 * @retval false Otherwise
		 */
		DllExport virtual bool 					shadow(void) const { return m_shadow; }
		/**
		 * @brief Turns the shadow casting on
		 */
		DllExport void							turnShadowOn(void) { m_shadow = true; }
		/**
		 * @brief Turns the shadow casting off
		 */
		DllExport void							turnShadowOff(void) { m_shadow = false; }
		
		
	private:
		Vec3f	m_intensity;	///< The emission (red, green, blue)
		bool	m_shadow;		///< Flag indicating whether the light source casts shadows
	};

	using ptr_light_t = std::shared_ptr<ILight>;
}
