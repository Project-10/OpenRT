#include <macroses.h>
#include "SolidTorus.h"
#include "PrimTriangle.h"

// A helper struct to store and access the torus topology when constructing.
struct torus_data {
    Vec3f t_vertex; // the point
    Vec3f t_normal; // the surface normal
    Vec2f t_uv_coord; // the uv coordinate
};


rt::CSolidTorus::CSolidTorus(const rt::ptr_shader_t &pShader, const Vec3f &origin, float r1, float r2, int nSides,
                             bool smooth) : CSolid(origin) {
    RT_ASSERT_MSG(nSides > 2, "A solid torus can only be modeled using 3 or more sides. Please adjust your input.");
    RT_ASSERT_MSG(r1 > r2,
                  "A solid torus can only be modeled when the cross-section radius is smaller than the outer radius. Please adjust your input.");

    int nSegments = 2*nSides;
    std::vector<torus_data> torus_vertices;
    torus_vertices.reserve((nSegments)*(nSegments + 1) + (nSides + 2));
    for (int i = 0; i <= nSegments; i++) {
        for (int j = 0; j <= nSides + 1; j++) {
            auto data = torus_data();
            auto phi = (float)i * (2 * Pif / (float)nSegments);
            auto theta = (float)j * (2 * Pif / (float)nSides);
            torus_vertices[(nSegments * i) + j].t_vertex = origin + Vec3f(cos(phi) * (r1 + r2 * cos(theta)),
                                                                       sin(phi) * (r1 + r2 * cos(theta)),
                                                                       r2 * sin(theta));
            torus_vertices[(nSegments * i) + j].t_uv_coord = Vec2f((float)i / (float)nSegments, (float)j / (float)nSides);
            torus_vertices[(nSegments * i) + j].t_normal = Vec3f(cos(phi) * cos(theta), sin(theta) * cos(phi), sin(theta));
        }
    }

    for (int i = 0; i < nSegments; i++) {
        for (int j = 0; j < nSides; j++) {
            auto a = (nSegments * i) + j;
            auto b = (nSegments * (i + 1)) + j;
            auto c = (nSegments * i) + (j + 1);
            auto d = (nSegments * (i + 1)) + (j + 1);
            if (smooth) {
                add(std::make_shared<CPrimTriangle>(pShader, torus_vertices[a].t_vertex, torus_vertices[b].t_vertex,
                                                    torus_vertices[c].t_vertex, torus_vertices[a].t_uv_coord,
                                                    torus_vertices[b].t_uv_coord, torus_vertices[c].t_uv_coord,
                                                    torus_vertices[a].t_normal, torus_vertices[b].t_normal,
                                                    torus_vertices[c].t_normal));
                add(std::make_shared<CPrimTriangle>(pShader, torus_vertices[b].t_vertex, torus_vertices[c].t_vertex,
                                                    torus_vertices[d].t_vertex, torus_vertices[b].t_uv_coord,
                                                    torus_vertices[c].t_uv_coord, torus_vertices[d].t_uv_coord,
                                                    torus_vertices[b].t_normal, torus_vertices[c].t_normal,
                                                    torus_vertices[d].t_normal));
            } else {
                add(std::make_shared<CPrimTriangle>(pShader, torus_vertices[a].t_vertex, torus_vertices[b].t_vertex,
                                                    torus_vertices[c].t_vertex, torus_vertices[a].t_uv_coord,
                                                    torus_vertices[b].t_uv_coord, torus_vertices[c].t_uv_coord));
                add(std::make_shared<CPrimTriangle>(pShader, torus_vertices[b].t_vertex, torus_vertices[c].t_vertex,
                                                    torus_vertices[d].t_vertex, torus_vertices[b].t_uv_coord,
                                                    torus_vertices[c].t_uv_coord, torus_vertices[d].t_uv_coord));
            }
        }
    }
}
