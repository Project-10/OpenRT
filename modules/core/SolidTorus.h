#include "Solid.h"


namespace rt {

    // Helper struct to store and process the torus topology information

    // ================================ Cone Solid Class ================================
    /**
     * @brief Torus Solid class
     * @ingroup moduleSolid
     */
    class CSolidTorus : public CSolid {
    public:
        /**
        * @brief Constructor
        * @param pShader Pointer to the shader
        * @param origin The origin of the torus
        * @param radius1 The major radius of the torus
        * @param radius2 The minor (cross sectional) radius of the torus
        * @param sides The number of sides
        * @param smooth Flag indicating whether the normals should be smoothed
        */
        DllExport CSolidTorus(const ptr_shader_t &pShader, const Vec3f &origin, float radius1, float radius2, size_t sides, bool smooth = true);

        DllExport virtual ~CSolidTorus(void) = default;
    };
}
