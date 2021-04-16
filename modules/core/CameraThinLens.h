#pragma once

#include "CameraPerspective.h"

namespace rt {
	// ================================ Perspective Thin Lens Camera Class ================================
	/**
	 * @brief Perspective Thin Lens Camera class
	 * @ingroup moduleCamera
	 */
	class CCameraThinLens : public CCameraPerspective
	{
	public:
		/**
		 * @brief Constructor
		 * @param resolution The image resolution
		 * @param pos Camera origin (center of projection)
		 * @param target The target point
		 * @param up Camera up-vector
		 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
		 * @param lensRadius The radius of the lense 
		 * @param focalDistance distance from Camera origin to the focal plane 
		 * @param nBlades number of aperture blades of the camera
		 */
		DllExport CCameraThinLens(Size resolution, const Vec3f& pos, const Vec3f& dir,
								  const Vec3f& up, float angle, float lensRadius = 0, float focalDistance =0, int nBlades = 0)
			: CCameraPerspective(resolution, pos, dir, up, angle)
			, m_lensRadius(lensRadius)
			, m_focalDistance(focalDistance)
			, m_nBlades(nBlades)
		{}

		DllExport virtual ~CCameraThinLens(void) = default;
			
		DllExport void			InitRay(Ray& ray, int x, int y, const Vec2f& sample = Vec2f::all(0.5f)) override;
		/**
		 * @brief Returns the lens radius
		 * @return The lens radius
		 */
		DllExport float			getlensRadius(void) const { return m_lensRadius; }
		/**
		 * @brief Returns the focal distance
		 * @return The focal distance
		 */
		DllExport float			getfocalDistance(void) const { return m_focalDistance; }
		/**
		* @brief Returns the number of aperture blades of the camera
		* @return The number of aperture blades
		*/
		DllExport int			getnBlades(void) const { return m_nBlades; }


	private:
		const float m_lensRadius = 0;
		const float m_focalDistance = 10;
		const int m_nBlades = 0;
	};
}
