#include "Solid.h"


namespace rt {

    // Helper struct to store and process the torus topology information

    // ================================ Cone Solid Class ================================
    /**
     * @brief Torus Solid class
     * @ingroup modulePrimitive
     */
    class CSolidTorus : public CSolid {
    public:
        /**
        * @brief Constructor
        * @param pShader Pointer to the shader
        * @param origin The origin of the torus
        * @param r1 The outer radius of the torus
        * @param r2 The inner (cross sectional) radius of the torus
        * @param sides The number of sides
        * @param smooth Flag indicating whether the normals should be smoothed
        */
        DllExport CSolidTorus(const ptr_shader_t &pShader, const Vec3f &origin, float r1, float r2, int nSides,
                              bool smooth = true);

        DllExport virtual ~CSolidTorus(void) = default;

    private:

        /**
        * @struct torus_data
        * @brief A helper struct to store and access the torus topology when constructing.
        * @var torus_data:t_vertex
        */
        struct torus_data {
            Vec3f t_vertex; // the point
            Vec3f t_normal; // the surface normal
            Vec2f t_uv_coord; // the uv coordinate
        };
    };
}
