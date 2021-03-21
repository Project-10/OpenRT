// Environment Target Camera class
#pragma once

#include "CameraEnvironment.h"

namespace rt {
    // ================================ Environment Target Camera Class ================================
    /**
     * @brief Target Environment  Camera class
     * @ingroup moduleCamera
     * @author Fjolla Dedaj, dedajfjolla@gmail.com
     */
    class CCameraEnvironmentTarget : public CCameraEnvironment
    {
    public:
        /**
         * @brief Constructor
         * @param resolution The image resolution
         * @param pos Camera origin (center of projection)
         * @param target The target point
         * @param up Camera up-vector
         */
        DllExport CCameraEnvironmentTarget(Size resolution, const Vec3f& pos, const Vec3f& target, const Vec3f& up)
            : CCameraEnvironment(resolution, pos, normalize(target - pos), up)
            , m_target(target)
        {}
        DllExport virtual ~CCameraEnvironmentTarget(void) = default;

        DllExport void    setPosition(const Vec3f& pos) override {
            CCameraEnvironment::setPosition(pos);
            CCameraEnvironment::setDirection(normalize(m_target - pos));
        }

        /**
         * @brief Sets camera target point
         * @param target Camera target point
         */
        DllExport virtual void    setTarget(const Vec3f& target) {
            m_target = target;
            CCameraEnvironment::setDirection(normalize(m_target - getPosition()));
        }
        /**
         * @brief Returns the camera target point
         * @return The camera target point
         */
        DllExport Vec3f            getTarget(void) const { return m_target; }


    private:
        Vec3f m_target;        ///< Camera target point in WCS
    };
}
