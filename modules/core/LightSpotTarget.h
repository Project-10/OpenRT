
#pragma once

#include "LightSpot.h"

namespace rt {
	/**
	 * @brief The directed spotlight class
	 */
	class CLightSpotTarget : public CLightSpot
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param org The position (origin) of the light source
		 * @param target The target point
		 * @param alpha The opening angle of the cone with constant surface illumination
		 * @param beta The additional opening angle for attenuted illumination
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightSpotTarget(const Vec3f& intensity, const Vec3f& org, const Vec3f& target, float alpha, float beta = 0.0f, bool castShadow = true)
			: CLightSpot(intensity, org, normalize(target - org), alpha, beta, castShadow) 
			, m_target(target)
		{}
		DllExport virtual ~CLightSpotTarget(void) = default;

		DllExport virtual void	setOrigin(const Vec3f& org) override {
			CLightSpot::setOrigin(org);
			CLightSpot::setDirection(normalize(m_target - org));
		}

		/**
		 * @brief Sets light target point
		 * @param target The target point
		 */
		DllExport virtual void	setTarget(const Vec3f& target) {
			m_target = target;
			CLightSpot::setDirection(normalize(m_target - getOrigin()));
		}
		/**
		 * @brief Returns the camera target point
		 * @return The camera target point
		 */
		DllExport Vec3f			getTarget(void) const { return m_target; }


	private:
		Vec3f m_target;		///< Light source target point
	};
}
