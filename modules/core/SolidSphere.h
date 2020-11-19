#pragma once

#include "SolidQuad.h"

namespace rt
{
    class CSolidSphere : public CSolid
    {
    public:
        DllExport explicit CSolidSphere(ptr_shader_t pShader, const Vec3f& origin = Vec3f::all(0), float radius = 1, size_t sides = 24);
        DllExport ~CSolidSphere() override = default;

    protected:
        // Helper method
        void computeCoords(int i, int j, Vec3f &pt, Vec2f &tex, Vec3f &normal);

    private:
        Vec3f m_origin;
        int m_sides;
        float m_radius;
    };
}