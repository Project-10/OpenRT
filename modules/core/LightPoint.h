#pragma once

#include "ILight.h"

namespace rt {
	/**
	 * @brief Point light source class
	 */
	class CLightPoint : public ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param position The position (origin) of the light source
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightPoint(Vec3f intensity, Vec3f position, bool castShadow = true)
			: ILight(castShadow)
			, m_intensity(intensity)
			, m_position(position)
		{}
		DllExport virtual ~CLightPoint(void) = default;

		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) override
		{
			// ray towards point light position
			ray.dir = m_position - ray.org;
			ray.t = norm(ray.dir);
			ray.dir = normalize(ray.dir);
			ray.hit = nullptr;	
			float attenuation = 1 / (ray.t * ray.t);
			return attenuation * m_intensity;
		}
		DllExport virtual Photon sample_le(void) override{
			Photon ray;
			return ray;
		}


	private:
		Vec3f m_intensity; ///< emission (red, green, blue)
		Vec3f m_position;  ///< The light source origin
	};
}

