// Perspective Target Camera class
// Written by Sergey Kosov in 2019 for Jacobs University Bremen
#pragma once

#include "CameraPerspective.h"

namespace rt {
	// ================================ Perspective Target Camera Class ================================
	/**
	 * @brief Target Perspective Camera class
	 * @ingroup moduleCamera
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CCameraPerspectiveTarget : public CCameraPerspective
	{
	public:
		/**
		 * @brief Constructor
		 * @param resolution The image resolution
		 * @param pos Camera origin (center of projection)
		 * @param target The target point
		 * @param up Camera up-vector
		 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
		 */
		DllExport CCameraPerspectiveTarget(Size resolution, const Vec3f& pos, const Vec3f& target, const Vec3f& up, float angle)
			: CCameraPerspective(resolution, pos, normalize(target - pos), up, angle)
			, m_target(target)
		{}
		DllExport virtual ~CCameraPerspectiveTarget(void) = default;

		DllExport virtual void	setPosition(const Vec3f& pos) override {
			CCameraPerspective::setPosition(pos);
			CCameraPerspective::setDirection(normalize(m_target - pos));
		}

		/**
		 * @brief Sets camera target point
		 * @param target Camera target point
		 */
		DllExport virtual void	setTarget(const Vec3f& target) {
			m_target = target;
			CCameraPerspective::setDirection(normalize(m_target - getPosition()));
		}
		/**
		 * @brief Returns the camera target point
		 * @return The camera target point
		 */
		DllExport Vec3f			getTarget(void) const { return m_target; }


	private:
		Vec3f m_target;		///< Camera target point in WCS
	};
}
