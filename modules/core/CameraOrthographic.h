// Orthographic Camera class
// Written by Sergey Kosov in 2010 for Jacobs University
#pragma once

#include "ICamera.h"

namespace rt {
	class CCameraOrthographic : public ICamera
	{
	public:
		/**
		 * @brief Constructor
		 * @details Creates a default camera in the origin of the world coordinate system (WCS)
		 * @param resolution The resolution of the camera in pixels
		 */
		DllExport CCameraOrthographic(Size resolution) : ICamera(resolution) {}
		/**
		 * @brief Constructor
		 * @param resolution The image resolution in pixels
		 * @param pos Camera origin (center of projection)
		 * @param dir Normalized camera viewing direction
		 * @param up Normalized camera up-vector
		 * @param size The relative camera's sensor size
		 */
		DllExport CCameraOrthographic(Size resolution, const Vec3f& pos, const Vec3f& dir, const Vec3f& up, float size)
			: ICamera(resolution)
			, m_pos(pos)
			, m_dir(dir)
			, m_up(up)
			, m_size(size)
		{}
		DllExport virtual ~CCameraOrthographic(void) = default;
		
		DllExport virtual void	InitRay(Ray& ray, int x, int y, Vec2f sample = Vec2f::all(0.5f)) override;
		
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
		 * @rief Returns the camera position
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
		
		
	private:
		// input values
		Vec3f m_pos		= Vec3f(0, 0, 0);	///< Camera origin (center of projection)
		Vec3f m_dir		= Vec3f(0, 0, 1);	///< Camera viewing direction
		Vec3f m_up		= Vec3f(0, 1, 0);	///< Camera up-vector
		float m_size	= 1;				///< Camera's sensor size

		// preprocessed values
		bool  m_needUpdateAxes = true;		///< Flag indicating that the axes must me updated
		Vec3f m_xAxis;						///< Camera x-axis in WCS
		Vec3f m_yAxis;						///< Camera y-axis in WCS
		Vec3f m_zAxis;						///< Camera z-axis in WCS
	};
}
