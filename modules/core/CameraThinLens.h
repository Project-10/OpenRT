#pragma once

#include "CameraPerspective.h"

namespace rt {
	// ================================ Perspective Thin Lens Camera Class ================================
	/**
	 * @brief Perspective Thin Lens Camera class
	 * @ingroup moduleCamera
	 * @author Yonatan G. Mamo, y.mamo@jacobs-university.de
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
		DllExport CCameraThinLens(Size resolution, const Vec3f& pos, const Vec3f& dir, const Vec3f& up, float angle, float lensRadius = 0, float focalDistance = 10, int nBlades = 0)
			: CCameraPerspective(resolution, pos, dir, up, angle)
			, m_lensRadius(lensRadius)
			, m_focalDistance(focalDistance)
			, m_nBlades(nBlades)
		{}
		DllExport virtual ~CCameraThinLens(void) = default;
			
		DllExport void InitRay(Ray& ray, int x, int y, const Vec2f& sample = Vec2f::all(0.5f)) override;


	private:
		const float m_lensRadius;		///< The radius of the lense 
		const float m_focalDistance;	///< The distance from Camera origin to the focal plane 
		const int	m_nBlades;			///< Number of aperture blades of the camera
	};
}
