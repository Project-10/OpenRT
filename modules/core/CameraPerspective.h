// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

namespace rt {
	/**
	 * @brief Perspective Camera class
	 */
	class CCameraPerspective : public ICamera
	{
	public:
		/**
		 * @brief Constructor
		 * @param pos Camera origin (center of projection)
		 * @param dir Camera viewing direction
		 * @param up Camera up-vector
		 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
		 * @param resolution The image resolution
		 */
		DllExport CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
			: ICamera(resolution)
			, m_pos(pos)
			, m_dir(dir)
			, m_up(up)
		{
			updateAxes();

			m_aspect = static_cast<float>(resolution.width) / resolution.height;
			m_focus = 1.0f / tanf(angle * Pif / 360);		// f = 1 / tg(angle / 2)
		}
		DllExport virtual ~CCameraPerspective(void) = default;

		DllExport virtual void InitRay(Ray& ray, int x, int y, Vec2f sample) override;

		/**
		 * @brief Sets new camera position
		 * @param pos Camera origin (center of projection)
		 */
		DllExport void	setPosition(Vec3f pos) {
			m_pos = pos;
			m_uAxes = true;
		}
		/**
		 * @brief Sets new camera direction
		 * @param dir Camera viewing direction
		 */
		DllExport void	setDirection(Vec3f dir) {
			m_dir = dir;
			m_uAxes = true;
		}


	private:
		void updateAxes(void) {
			m_zAxis = m_dir;
			m_xAxis = normalize(m_zAxis.cross(m_up));
			m_yAxis = normalize(m_zAxis.cross(m_xAxis));
			m_uAxes = false;
		}

	private:
		// input values
		Vec3f m_pos;		///< Camera origin (center of projection)
		Vec3f m_dir;		///< Camera viewing direction
		Vec3f m_up;			///< Camera up-vector

		// preprocessed values
		Vec3f m_xAxis;		///<
		Vec3f m_yAxis;		///<
		Vec3f m_zAxis;		///<
		bool  m_uAxes;		///< Flag indicating that the axes must me updated
		float m_aspect;		///< image aspect ratio
		float m_focus;		///< The focal length
		
	};
}
