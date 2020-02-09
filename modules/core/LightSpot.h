#pragma once

#include "LightPoint.h"

#define _USE_MATH_DEFINES // for C++
#include <cmath>

namespace rt {
	/**
	 * @brief Spot light source class
	 * @todo Add attenuation angle
	 */
	class CLightSpot : public ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param position The position (origin) of the light source
		 * @param direction The direction f the light source
		 * @param angle The opening angle of the cone
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpot(Vec3f intensity, Vec3f position, Vec3f direction, float angle, bool castShadow = true)
			: ILight(castShadow)
			, m_intensity(intensity)
			, m_position(position)
			, m_direction(normalize(direction))
			, m_cosAngle(cosf(angle * M_PI / 360))	// 360 instead of 180 -> we use halfangle
		{}
		DllExport virtual ~CLightSpot(void) = default;

		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) override
		{
			// ray towards spot light position
			ray.dir = m_position - ray.org;
			ray.t = norm(ray.dir);
			ray.dir = normalize(ray.dir);
			
			float cosAngle = m_direction.dot(-ray.dir);
			if (cosAngle < m_cosAngle) return std::nullopt;	// bacause working not with angle but with their cosines
			else {
				float attenuation = 1 / (ray.t * ray.t);
				attenuation *= (1.0 - (1.0 - cosAngle) / (1.0 - m_cosAngle));	// additional linear attenuation
				return attenuation * m_intensity;
			}
		}


	private:
		Vec3f m_intensity; ///< emission (red, green, blue)
		Vec3f m_position;  ///< The light source origin
		Vec3f m_direction;
		float m_cosAngle;
	};

	/**
	 * @brief The directed spotlight class
	 */
	class CLightSpotDirected : public CLightSpot
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param position The position (origin) of the light source
		 * @param target  The target point
		 * @param angle The opening angle of the cone
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpotDirected(Vec3f intensity, Vec3f position, Vec3f target, float angle, bool castShadow = true)
			: CLightSpot(intensity, position, normalize(target - position), angle, castShadow) {}
		DllExport virtual ~CLightSpotDirected(void) = default;
	};
}

