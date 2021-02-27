// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

namespace rt {
	// ================================ Perspective Camera Class ================================
	/**
	 * @brief Perspective Camera class
	 * @ingroup moduleCamera
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CCameraPerspective : public ICamera
	{
	public:
		/**
		 * @brief Constructor
		 * @details Creates a default camera in the origin of the world coordinate system (WCS)
		 * @param resolution The resolution of the camera in pixels
		 */
		DllExport CCameraPerspective(Size resolution) : ICamera(resolution) {}
		/**
		 * @brief Constructor
		 * @param resolution The image resolution in pixels
		 * @param pos Camera origin (center of projection)
		 * @param dir Normalized camera viewing direction
		 * @param up Normalized camera up-vector
		 * @param angle (Vertical) full opening angle of the viewing frustum in degrees
		 */

		DllExport CCameraPerspective(Size resolution, const Vec3f& pos, const Vec3f& dir,
			const Vec3f& up, float angle)
			: ICamera(resolution)
			, m_pos(pos)
			, m_dir(dir)
			, m_up(up)
			, m_focus(1.0f / tanf(angle * Pif / 360))	// f = 1 / tg(angle / 2)
		{}

		DllExport CCameraPerspective(Size resolution, const Vec3f& pos, const Vec3f& dir, 
									const Vec3f& up, float angle, float lensRadius, float focalDistance, int nBlades = 0)
			: ICamera(resolution, lensRadius, focalDistance, nBlades)
			, m_pos(pos)
			, m_dir(dir)
			, m_up(up)
			, m_focus(1.0f / tanf(angle * Pif / 360))	// f = 1 / tg(angle / 2)
		{}
		DllExport virtual ~CCameraPerspective(void) = default;

		DllExport virtual void	InitRay(Ray& ray, int x, int y, const Vec2f& sample = Vec2f::all(0.5f)) override;

		/**
		 * @brief Sets new camera position
		 * @param pos Camera origin (center of projection)
		 */	
		DllExport virtual void	setPosition(const Vec3f& pos) { m_pos = pos; }
		/**
		 * @brief Sets new camera direction
		 * @param dir Normalized camera viewing direction
		 */
		DllExport virtual void	setDirection(const Vec3f& dir) {
			m_dir = dir;
			m_needUpdateAxes = true;
		}
		/**
		 * @brief Sets camera up-vector
		 * @param up Normalized camera up-vector
		 */
		DllExport virtual void	setUpVector(const Vec3f& up) {
			m_up = up;
			m_needUpdateAxes = true;
		}
		/**
		 * @brief Sets camera opening angle
		 * @param angle Camera opening angle
		 */
		DllExport virtual void	setAngle(float angle) { m_focus = 1.0f / tanf(angle * Pif / 360); }
		
		/**
		 * @brief Returns the camera position
		 * @return The camera position
		 */
		DllExport Vec3f			getPosition(void) const { return m_pos; }
		/**
		 * @brief Returns the camera direction
		 * @return The camera direction
		 */
		DllExport Vec3f			getDirection(void) const { return m_dir; }
		/**
		 * @brief Returns the camera up-vector
		 * @return The camera up-vector
		 */
		DllExport Vec3f			getUpVector(void) const { return m_up; }
		/**
		 * @brief Returns the camera opening angle
		 * @return The camera opening angle
		 */
		DllExport float			getAngle(void) const { return 360 * atanf(1.0f / m_focus) / Pif; }


	private:
		// input values
		Vec3f m_pos		= Vec3f(0, 0, 0);	///< Camera origin (center of projection)
		Vec3f m_dir		= Vec3f(0, 0, 1);	///< Camera viewing direction
		Vec3f m_up		= Vec3f(0, 1, 0);	///< Camera up-vector
		float m_focus	= 1;				///< The focal length

		// preprocessed values
		bool  m_needUpdateAxes = true;		///< Flag indicating that the axes must me updated
		Vec3f m_xAxis;						///< Camera x-axis in WCS
		Vec3f m_yAxis;						///< Camera y-axis in WCS
		Vec3f m_zAxis;						///< Camera z-axis in WCS
	};
}
