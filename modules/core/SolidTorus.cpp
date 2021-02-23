#include <macroses.h>
#include "SolidTorus.h"
#include "PrimTriangle.h"

rt::CSolidTorus::CSolidTorus(const rt::ptr_shader_t &pShader, const Vec3f &origin, float r1, float r2, int nSides,
                             bool smooth) : CSolid(origin) {
    RT_ASSERT_MSG(nSides > 2, "A solid torus can only be modeled using 3 or more sides. Please adjust your input.");
    RT_ASSERT_MSG(r1 > r2,
                  "A solid torus can only be modeled when the cross-section radius is smaller than the outer radius. Please adjust your input.");

    std::vector<torus_data> torus_vertices;
    torus_vertices.reserve((nSides) * (nSides + 2));
    for (int i = 0; i < nSides; i++) {
        for (int j = 0; j <= nSides + 1; j++) {
            auto data = torus_data();
            auto phi = (float)i * (2 * Pif / (float)nSides);
            auto theta = (float)j * (2 * Pif / (float)nSides);
            torus_vertices[(nSides * j) + i].t_vertex = origin + Vec3f(cos(phi) * (r1 + r2 * cos(theta)),
                                                                       sin(phi) * (r1 + r2 * cos(theta)),
                                                                       r2 * sin(theta));
            torus_vertices[(nSides * j) + i].t_uv_coord = Vec2f(j / nSides, i / nSides);
            torus_vertices[(nSides * j) + i].t_normal = Vec3f(cos(phi) * cos(theta), sin(theta) * cos(phi), sin(theta));
        }
    }

    for (int i = 0; i < nSides; i++) {
        for (int j = 0; j < nSides; j++) {
            auto a = (nSides * j) + i;
            auto b = (nSides * (j + 1)) + i;
            auto c = (nSides * j) + (i + 1);
            auto d = (nSides * (j + 1)) + (i + 1);
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
