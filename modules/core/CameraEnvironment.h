// Environment Camera class
#pragma once

#include "ICamera.h"

namespace rt {
    // ================================ Environment Camera Class ================================
    /**
     * @brief Environment Camera class
     * @ingroup moduleCamera
     * @details This calss implements an <a href="https://pbr-book.org/3ed-2018/Camera_Models/Environment_Camera" target="_blank">Environment Camera</a> model and may be used for rendering 360 degrees spherical panoramic images.
	 * @note This calss can be also used for rendering stereoscopic images for Virutual Reality (VR). To do this, use the \b PD (pupillary distance) argument in the class constructor. 
	 * Camera with negative pupillary distance will capture an image for the left eye and camera with positive pupillary distance - for the right eye. The resulting stereoscopic image may be viewed in a 
	 * 3D glasses as google cardboard.
	 * @author Fjolla Dedaj, dedajfjolla@gmail.com
     */
    class CCameraEnvironment : public ICamera
    {
    public:
        /**
         * @brief Constructor
         * @details Creates a default camera in the origin of the world coordinate system (WCS)
         * @param resolution The resolution of the camera in pixels
         */
        DllExport CCameraEnvironment(Size resolution) : ICamera(resolution) {}
        /**
         * @brief Constructor
         * @param resolution The image resolution in pixels
         * @param pos Camera origin (center of projection)
         * @param dir Normalized camera viewing direction
         * @param up Normalized camera up-vector
		 * @param PD The monocular pupillary distance (the distance between each eye and the bridge of the nose). Should be nagative for the left eye and positive for the right eye.
		 * Note that the PD for an adult male is 32mm and for an adult femail is 30.85mm. The argument should be a converted value from millimters to WCS units. 
         */
        DllExport CCameraEnvironment(Size resolution, const Vec3f& pos, const Vec3f& dir, const Vec3f& up, float PD = 0)
            : ICamera(resolution)
            , m_pos(pos)
            , m_dir(dir)
            , m_up(up)
			, m_PD(PD)
        {}
        DllExport virtual ~CCameraEnvironment(void) = default;

        DllExport void InitRay(Ray& ray, int x, int y, const Vec2f& sample = Vec2f::all(0.5f)) override;

        /**
         * @brief Sets new camera position
         * @param pos Camera origin (center of projection)
         */
        DllExport virtual void    setPosition(const Vec3f& pos) { m_pos = pos; }
        /**
         * @brief Sets new camera direction
         * @param dir Normalized camera viewing direction
         */
        DllExport virtual void    setDirection(const Vec3f& dir) {
            m_dir = dir;
            m_needUpdateAxes = true;
        }
        /**
         * @brief Sets camera up-vector
         * @param up Normalized camera up-vector
         */
        DllExport virtual void    setUpVector(const Vec3f& up) {
            m_up = up;
            m_needUpdateAxes = true;
        }
		/**
		 * @brief Sets the monocular pupillary distance (the distance between each eye and the bridge of the nose). Should be nagative for the left eye and positive for the right eye.
		 * @param IPD The pupillary distance
		 */
		DllExport virtual void    setIPD(float IPD) { m_PD = IPD; }
        /**
         * @brief Returns the camera position
         * @return The camera position
         */
        DllExport Vec3f            getPosition(void) const { return m_pos; }
        /**
         * @brief Returns the camera direction
         * @return The camera direction
         */
        DllExport Vec3f            getDirection(void) const { return m_dir; }
        /**
         * @brief Returns the camera up-vector
         * @return The camera up-vector
         */
        DllExport Vec3f            getUpVector(void) const { return m_up; }
		/**
		 * @brief Returns the camera pupillary distance
		 * @return The pupillary distance 
		 */
		DllExport float            getIPD(void) const { return m_PD; }


    private:
        // input values
        Vec3f m_pos			= Vec3f(0, 0, 0);	///< Camera origin (center of projection)
        Vec3f m_dir			= Vec3f(0, 0, 1);	///< Camera viewing direction
        Vec3f m_up			= Vec3f(0, 1, 0);   ///< Camera up-vector
		float m_PD			= 0;				///< Pupillary distance

        // preprocessed values
        bool  m_needUpdateAxes = true;			///< Flag indicating that the axes must me updated
        Vec3f m_xAxis;							///< Camera x-axis in WCS
        Vec3f m_yAxis;							///< Camera y-axis in WCS
        Vec3f m_zAxis;							///< Camera z-axis in WCS
    };
}
