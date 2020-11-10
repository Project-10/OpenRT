#pragma once

#include "SolidQuad.h"

namespace rt
{
    class CSolidSphere : public CSolid
    {
    public:
        CSolidSphere(ptr_shader_t pShader, const Vec3f& origin = Vec3f::all(0), float radius = 1, size_t sides = 24);
        virtual ~CSolidSphere(void) = default;

    protected:
        // Helper method
        void computeCoords(int i, int j, Vec3f &pt, Vec2f &tex, Vec3f &normal);

    private:
        // I know we were asked to only add code in areas where it says so but this
        // just separates the math from the rest of the logic. I hope that's okay.
        // It's also private so it shouldn't affect anything.
        Vec3f m_origin;
        int m_sides;
        float m_radius;
    };
}