#include "SolidSphere.h"
#include "PrimTriangle.h"


rt::CSolidSphere::CSolidSphere(rt::ptr_shader_t pShader, const Vec3f &origin, float radius, size_t sides) : CSolid(origin)
{
    //(x, y, z) = (sin(Pi * m/M) cos(2Pi * n/N), sin(Pi * m/M) sin(2Pi * n/N), cos(Pi * m/M))
    m_origin = origin;
    m_radius = radius;
    m_sides = sides;

    for (int i = 0; i < sides; i++)
    {
        for (int j = 0; j < sides; j++)
        {
            if (i == 0 || i == sides - 1)
            {
                Vec3f a = Vec3f(origin.val[0], origin.val[1] + (i == 0 ? radius : -radius), origin.val[2]);
                Vec2f t_a = Vec2f(0, i == 0 ? 1 : 0);
                Vec3f n_a = normalize(origin - a);
                Vec3f b, c, n_b, n_c;
                Vec2f t_b, t_c;
                computeCoords(i + 1, j, b, t_b, n_b);
                computeCoords(i + 1, j + 1, c, t_c, n_c);
                add(std::make_shared<CPrimTriangle>(pShader, a, b, c, t_a, t_b, t_c, n_a, n_b, n_c));
            }
            Vec3f a, b, c, d, n_a, n_b, n_c, n_d;;
            Vec2f t_a, t_b, t_c, t_d;
            computeCoords(i, j, a, t_a, n_a);
            computeCoords(i + 1, j, b, t_b, n_b);
            computeCoords(i, j + 1, c, t_c, n_c);
            computeCoords(i + 1, j + 1, d, t_d, n_d);
            add(std::make_shared<CSolidQuad>(pShader, a, b, d, c, t_a, t_b, t_d, t_c, n_a, n_b, n_d, n_c));
        }
    }
}

void rt::CSolidSphere::computeCoords(int i, int j, Vec3f &pt, Vec2f &tex, Vec3f &normal) {
        tex = Vec2f((float)i / ((float)m_sides + 1.0f),(1.0f - (float)(j + 1)) /(float)m_sides);
        // Convert to spherical coordinates:
        float theta = tex.val[0] * 2.0f * (float)Pi;
        float phi = (tex.val[1] - 0.5f) * (float)Pi;

        float c = cos(phi);

        // Usual formula for a vector in spherical coordinates.
        pt = Vec3f(c * cos(theta), sin(phi), c * sin(theta)) * m_radius;
        normal = normalize(pt - m_origin);
}
