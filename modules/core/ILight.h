#pragma once

#include "types.h"
#include "ppm.h"
namespace rt {
	struct Ray;
	struct Photon;

	/**
	 * @brief Base light source abstract interface class
	 */
	class ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param castShadow Flag indicating whether the light source casts shadows
		 */
		DllExport ILight(bool castShadow) : m_shadow(castShadow) {}
		DllExport ILight(const ILight&) = delete;
		DllExport virtual ~ILight(void) = default;
		DllExport const ILight& operator=(const ILight&) = delete;

		/**
		 * @brief Calculates the light intensity, at the point \b ray.org which is to be illuminated.
		 * @details This function sets the \b ray.dir to be the the direction vector from the surface point \b ray.org to the light source.
		 * @param[in, out] ray The ray from object point to the light source. The direction ray.dir is modified within the function
		 * @return The intensity of light hitting the point \b ray.org
		 */
		DllExport virtual std::optional<Vec3f>  illuminate(Ray& ray) = 0;
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
		/**
		 * @brief Returns recommended number of samples for the particular light source implementation
		 * @return The recommended number of samples 
		 */
		DllExport virtual size_t				getNumberOfSamples(void) const { return 1; }

		DllExport virtual std::optional<Photon> sample_le(void) = 0;
		
		
	private:
		bool	m_shadow;
	};
}
