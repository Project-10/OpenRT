// Orthographic Target Camera class
// Written by Sergey Kosov in 2020 for Jacobs University Bremen
#pragma once

#include "CameraOrthographic.h"

namespace rt {
	// ================================ Orthographic Target Camera Class ================================
	/**
	 * @brief Target Orthographic Camera class
	 * @ingroup moduleCamera
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CCameraOrthographicTarget : public CCameraOrthographic
	{
	public:
		/**
		 * @brief Constructor
		 * @param resolution The image resolution
		 * @param pos Camera origin (center of projection)
		 * @param target The target point
		 * @param up Camera up-vector
		 * @param size The relative camera's sensor size
		 */
		DllExport CCameraOrthographicTarget(Size resolution, const Vec3f& pos, const Vec3f& target, const Vec3f& up, float size)
			: CCameraOrthographic(resolution, pos, normalize(target - pos), up, size)
			, m_target(target)
		{}
		DllExport virtual ~CCameraOrthographicTarget(void) = default;

		DllExport virtual void	setPosition(const Vec3f& pos) override {
			CCameraOrthographic::setPosition(pos);
			CCameraOrthographic::setDirection(normalize(m_target - pos));
		}

		/**
		 * @brief Sets camera target point
		 * @param target Camera target point
		 */
		DllExport virtual void	setTarget(const Vec3f& target) {
			m_target = target;
			CCameraOrthographic::setDirection(normalize(m_target - getPosition()));
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
