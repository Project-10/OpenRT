#pragma once

#include "LightPoint.h"

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
		 * @param alpha The opening angle of the cone with constant surface illumination
		 * @param beta Added to alpha for attenuted illumination on the surface away from angle alpha
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpot(Vec3f intensity, Vec3f position, Vec3f direction, float alpha,float beta = 0.0f, bool castShadow = true)
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
			
			float angle = acosf(m_direction.dot(-ray.dir)) * 180/Pif;
			if (angle > (m_alpha  + m_beta)) return std::nullopt;
			else {
				float attenuation = 1 / (ray.t * ray.t);
				//float scale = (angle <= m_alpha) ? 1.0f : cosf(1.5f*(angle - m_alpha) / m_beta); // (0.07 , 1]
				float scale = (angle <= m_alpha) ? 1.0f : -1*powf((angle - m_alpha) / m_beta,2) + 1; // [0,1]
				//float scale = (angle <= m_alpha) ? 1.0f : 1.0f - (angle - m_alpha) / m_beta;

				return attenuation * m_intensity*scale;
			}
		}


	private:
		Vec3f m_intensity; ///< emission (red, green, blue)
		Vec3f m_position;  ///< The light source origin
		Vec3f m_direction;
		float m_alpha;
		float m_beta;
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
		 * @param beta The opening angle of the cone with attenuted illumination on the surface away from angle alpha
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpotDirected(Vec3f intensity, Vec3f position, Vec3f target, float alpha,float beta = 0.0f, bool castShadow = true)
			: CLightSpot(intensity, position, normalize(target - position), alpha,beta, castShadow) {}
		DllExport virtual ~CLightSpotDirected(void) = default;
	};
}

