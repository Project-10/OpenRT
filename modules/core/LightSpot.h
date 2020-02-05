#pragma once

#include "LightPoint.h"
#include <corecrt_math_defines.h>
namespace rt {
	/**
	 * @brief Spot light source class
	 */
	class CLightSpot : public ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param position The position (origin) of the light source
		 * @param position The direction f the light source
		 * @param angle The opening angle of the cone
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpot(Vec3f intensity, Vec3f position, Vec3f direction,float angle, bool castShadow = true)
			: ILight(castShadow)
			, m_intensity(intensity)
			, m_position(position)
			, m_direction(normalize(direction))
			, m_angle(cos(angle *M_PI/180.0f))
		{}
		DllExport virtual ~CLightSpot(void) = default;

		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) override
		{
			// ray towards spot light position
			ray.dir = m_position - ray.org ;
			ray.t = norm(ray.dir);
			ray.dir = normalize(ray.dir);
			float angle_light_ray = ray.dir.dot(-m_direction);
			float attenuation = 1 / (ray.t * ray.t);
			//if (acos(angle_light_ray) <  acos(m_angle)) {
			if (angle_light_ray > m_angle) {
				// Light Intensity reduces away from m_direction
				float scale = (1.0 - (1.0 - angle_light_ray) * 1.0 / (1.0 - m_angle));
				return attenuation * m_intensity * scale;
			}
			else {
				return std::nullopt;
			}
		}


	private:
		Vec3f m_intensity; ///< emission (red, green, blue)
		Vec3f m_position;  ///< The light source origin
		Vec3f m_direction;
		float m_angle;
	};
}

