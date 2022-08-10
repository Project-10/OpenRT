#pragma once

#include "Solid.h"

namespace rt
{
    // ================================ Sphere Solid Class ================================
    /**
     * @brief Cone Solid class
     * @ingroup modulePrimitive
     * @author Otmane Sabir, O.Sabir@jacobs-university.de
     */
    class CSolidSphere : public CSolid
    {
    public:
        /**
        * @brief Constructor
        * @param pShader Pointer to the shader
        * @param origin The origin of the sphere
        * @param radius The radius of the sphere
        * @param sides The number of sides
        * @param smooth Flag indicating whether the normals should be smoothed
        */
        DllExport explicit CSolidSphere(ptr_shader_t pShader, const Vec3f& origin = Vec3f::all(0), float radius = 1, size_t sides = 24, bool smooth = true);
        DllExport ~CSolidSphere() override = default;
        DllExport bool                                    isSolid(void) const override{return true;}

    };
}
