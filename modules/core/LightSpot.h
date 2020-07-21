#pragma once

#include "LightOmni.h"

namespace rt {
	// ================================ Point Light Class ================================
	/**
	 * @brief Spot light source class
	 * @ingroup moduleLight
	 * @author Takundey Gora, T.Gora@jacobs-university.de
	 */
	class CLightSpot : public CLightOmni
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param org The position (origin) of the light source
		 * @param dir The direction of the light source
		 * @param alpha The opening angle of the cone with constant surface illumination
		 * @param beta The additional opening angle for attenuted illumination
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpot(const Vec3f& intensity, const Vec3f& org, const Vec3f& dir, float alpha, float beta = 0.0f, bool castShadow = true)
			: CLightOmni(intensity, org, castShadow)
			, m_dir(normalize(dir))
			, m_alpha(alpha/2)
			, m_beta(beta/2)
		{}
		DllExport virtual ~CLightSpot(void) = default;

		DllExport virtual std::optional<Vec3f>	illuminate(Ray& ray) override;

		// Accessors
		/**
		 * @brief Sets new light direction
		 * @param dir he direction of the light source
		 */
		DllExport virtual void	setDirection(const Vec3f& dir) { m_dir = dir; }
		/**
		 * @brief Returns the light direction
		 * @return The light direction
		 */
		DllExport Vec3f			getDirection(void) const { return m_dir; }


	private:
		Vec3f m_dir;		///< The direction of the light source
		float m_alpha;		///< The opening angle of the cone with constant surface illumination
		float m_beta;		///< The additional opening angle for attenuted illumination
	};
}

