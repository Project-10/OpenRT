#pragma once

#include "ICamera.h"

namespace rt {
	// ================================ Perspective Thin Lens Camera Class ================================
	/**
	 * @brief Perspective Thin Lens Camera class
	 * @ingroup moduleCamera
	 * @author Yonatan G. Mamo, y.mamo@jacobs-university.de
	 */
	class CCameraThinLens : public ICamera
	{
	public:
		/**
		 * @brief Constructor
		 * @param pCamera Pointer to the base camera
		 * @param lensRadius The radius of the lense 
		 * @param focalDistance distance from Camera origin to the focal plane 
		 * @param nBlades number of aperture blades of the camera
		 */
		DllExport CCameraThinLens(const ptr_camera_t pCamera, float lensRadius = 0, float focalDistance = 10, int nBlades = 0)
			: ICamera(pCamera->getResolution())
			, m_pCamera(pCamera)
			, m_lensRadius(lensRadius)
			, m_focalDistance(focalDistance)
			, m_nBlades(nBlades)
		{}
		DllExport virtual ~CCameraThinLens(void) = default;
			
		DllExport void InitRay(Ray& ray, int x, int y, const Vec2f& sample = Vec2f::all(0.5f)) override;
		DllExport virtual Vec3f	getXAxis(void) const override { return m_pCamera->getXAxis(); }
		DllExport virtual Vec3f	getYAxis(void) const override { return m_pCamera->getYAxis(); }
		DllExport virtual Vec3f	getZAxis(void) const override { return m_pCamera->getZAxis(); }


	private:
		const ptr_camera_t	m_pCamera;			///< Pointer to the base camera
		const float			m_lensRadius;		///< The radius of the lense 
		const float			m_focalDistance;	///< The distance from Camera origin to the focal plane 
		const int			m_nBlades;			///< Number of aperture blades of the camera
	};
}
