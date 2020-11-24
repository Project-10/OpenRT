#include <macroses.h>
#include "SolidSphere.h"
#include "PrimTriangle.h"


rt::CSolidSphere::CSolidSphere(rt::ptr_shader_t pShader, const Vec3f &origin, float radius, size_t sides) : CSolid(origin)
{
    RT_ASSERT_MSG(sides > 3, "A solid sphere can only be modeled using 4 or more sides. Please adjust your input.");
    m_origin = origin;
    m_radius = radius;
    m_sides = sides;
    size_t height = sides/2;

    // This is quite straight forwards - The function creates 4 points and creates a quad from them
    // It uses UV coordinates to so. Except at the cap where it creates triangles from the "north/south poles"
    // to the points from a layer below.
    for (int i = 0; i < sides; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (j == 0 || j == (height-1))
            {
                Vec3f a, b, c, n_a, n_b, n_c;
                Vec2f t_a, t_b, t_c;
                computeCoords(i, j, a, t_a, n_a);
                computeCoords(i, j == 0 ? j + 1 : j - 1, b, t_b, n_b);
                computeCoords(i + 1, j == 0 ? j + 1 : j - 1, c, t_c, n_c);
                add(std::make_shared<CPrimTriangle>(pShader, a, b, c, t_a, t_b, t_c));
                continue;
            }
            Vec3f a, b, c, d, n_a, n_b, n_c, n_d;;
            Vec2f t_a, t_b, t_c, t_d;
            computeCoords(i, j, a, t_a, n_a);
            computeCoords(i+1, j, b, t_b, n_b);
            computeCoords(i, j+1, c, t_c, n_c);
            computeCoords(i + 1, j + 1, d, t_d, n_d);
            add(std::make_shared<CSolidQuad>(pShader, a, b, d, c, t_a, t_b, t_d, t_c));
        }
    }

}

void rt::CSolidSphere::computeCoords(int i, int j, Vec3f &pt, Vec2f &tex, Vec3f &normal)
{
    tex = Vec2f((float)i / ((float)(m_sides-1) + 1.0f),(1.0f - (float)(j + 1)) /(float)((m_sides/2) - 1));
    // Convert to spherical coordinates:
    float theta = tex.val[0] * 2.0f * Pif;
    float phi = (tex.val[1] - 0.5f) * Pif;

    float c = cos(phi);

    // Usual formula for a vector in spherical coordinates.
    pt = Vec3f(c * cos(theta), sin(phi), c * sin(theta)) * m_radius;
    normal = normalize(pt - m_origin);
}
