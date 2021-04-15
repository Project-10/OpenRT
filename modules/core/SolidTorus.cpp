#include "SolidTorus.h"
#include "SolidQuad.h"
#include "macroses.h"


// A helper struct to store and access the torus topology when constructing.
struct torus_data {
    Vec3f t_vertex;     // the point
    Vec3f t_normal;     // the surface normal
    Vec2f t_uv_coord;   // the uv coordinate
};


rt::CSolidTorus::CSolidTorus(const rt::ptr_shader_t &pShader, const Vec3f &origin, float radius1, float radius2, size_t sides, bool smooth) : CSolid(origin) {
    RT_ASSERT_MSG(sides > 2, "A solid torus can only be modeled using 3 or more sides. Please adjust your input.");
    RT_ASSERT_MSG(radius1 > radius2, "A solid torus can only be modeled when the cross-section radius is smaller than the outer radius. Please adjust your input.");

    const int segments = 2 * sides;    // number of segments per 360°

    std::vector<torus_data> torus_vertices((segments) * (segments + 1) + (sides + 2));
    
    for (size_t i = 0; i < segments + 1; i++) {
        for (size_t s = 0; s < sides + 2; s++) {
            float phi   = static_cast<float>(i) * 2 * Pif / segments;
            float theta = static_cast<float>(s) * 2 * Pif / sides;
            
            torus_vertices[(segments * i) + s].t_vertex     = origin + Vec3f(cosf(phi) * (radius1 + radius2 * cosf(theta)), sinf(phi) * (radius1 + radius2 * cosf(theta)), radius2 * sinf(theta));
            torus_vertices[(segments * i) + s].t_uv_coord   = Vec2f((float)i / (float)segments, (float)s / (float)sides);
            torus_vertices[(segments * i) + s].t_normal     = Vec3f(cosf(phi) * cosf(theta), sinf(phi) * cosf(theta), sinf(theta));


        } // sides
    }

    for (size_t i = 0; i < segments; i++) {
        for (size_t s = 0; s < sides; s++) {
            auto a = torus_vertices[(segments * i) + s];
            auto b = torus_vertices[(segments * (i + 1)) + s];
            auto c = torus_vertices[(segments * (i + 1)) + (s + 1)]; 
            auto d = torus_vertices[(segments * i) + (s + 1)];
            if (smooth) 
                add(CSolidQuad(pShader, a.t_vertex, b.t_vertex, c.t_vertex, d.t_vertex,
                                        a.t_uv_coord, b.t_uv_coord, c.t_uv_coord, d.t_uv_coord,
                                        a.t_normal, b.t_normal, c.t_normal, d.t_normal));
            else 
                add(CSolidQuad(pShader, a.t_vertex, b.t_vertex, c.t_vertex, d.t_vertex, 
                                        a.t_uv_coord, b.t_uv_coord, c.t_uv_coord, d.t_uv_coord));
        }
    }
}
