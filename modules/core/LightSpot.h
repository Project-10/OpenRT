#pragma once

#include "LightPoint.h"

namespace rt {
	/**
	 * @brief Spot light source class
	 * @author Takundey Gora, T.Gora@jacobs-university.de
	 */
	class CLightSpot : public ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param position The position (origin) of the light source
		 * @param direction The direction of the light source
		 * @param alpha The opening angle of the cone with constant surface illumination
		 * @param beta The additional opening angle for attenuted illumination
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpot(Vec3f intensity, Vec3f position, Vec3f direction, float alpha, float beta = 0.0f, bool castShadow = true)
			: ILight(castShadow)
			, m_intensity(intensity)
			, m_position(position)
			, m_direction(normalize(direction))
			, m_alpha(alpha/2)
			, m_beta(beta/2)
		{}
		DllExport virtual ~CLightSpot(void) = default;

		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) override
		{
			// ray towards spot light position
			ray.dir = m_position - ray.org;
			ray.t = norm(ray.dir);
			ray.dir = normalize(ray.dir);
			ray.hit = nullptr;
			
			float angle = acosf(m_direction.dot(-ray.dir)) * 180 / Pif;
			if (angle > (m_alpha  + m_beta)) return std::nullopt;	// no light
	
			float attenuation = 1 / (ray.t * ray.t);
			if (angle <= m_alpha) return attenuation * m_intensity;	// 100% light
			
			// angle \in (m_alpha; m_alpha + m_beta]
			float k = (angle - m_alpha) / m_beta;					// k \in (0, 1]
			float scale;
			switch (2) {
				case 0: scale = 1 - k; 					 break;
				case 1: scale = 1 - k * k; 				 break;
				case 2: scale = (1 + cosf(Pif * k)) / 2; break;
				default: scale = 1;
			}
			return attenuation * m_intensity * scale;				// attenuated light
		}


	private:
		Vec3f m_intensity;	///< Emission (red, green, blue)
		Vec3f m_position;	///< The light source origin
		Vec3f m_direction;	///< The direction of the light source
		float m_alpha;		///< The opening angle of the cone with constant surface illumination
		float m_beta;		///< The additional opening angle for attenuted illumination
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
		 * @param alpha The opening angle of the cone with constant surface illumination
		 * @param beta The additional opening angle for attenuted illumination
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpotDirected(Vec3f intensity, Vec3f position, Vec3f target, float alpha, float beta = 0.0f, bool castShadow = true)
			: CLightSpot(intensity, position, normalize(target - position), alpha,beta, castShadow) {}
		DllExport virtual ~CLightSpotDirected(void) = default;
	};
}

