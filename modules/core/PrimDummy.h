#include <utility>

#include "IPrim.h"

namespace rt {
    class CPrimDummy : public IPrim {
    public:
        /**
    * @brief Constructor
    * @param pShader Pointer to the shader to be applied for the prim
    * @param origin Point on the plane
    * @param normal Normal to the plane
    */
        DllExport CPrimDummy(ptr_shader_t shader, const Vec3f& normal, const Vec2f& texture)
                : IPrim(std::move(shader)), m_normal(normal), m_texture_coords(texture)
        {
        }
        DllExport virtual ~CPrimDummy(void) = default;

        DllExport virtual bool 			intersect(Ray& ray) const override;
        DllExport virtual bool 			if_intersect(const Ray& ray) const override;
        DllExport virtual void 			transform(const Mat& T) override;
        DllExport Vec3f			getOrigin(void) const override;
        DllExport Vec3f 		getNormal(const Ray&) const override { return m_normal; }
        DllExport virtual Vec2f			getTextureCoords(const Ray& ray) const override { return m_texture_coords; };
        DllExport virtual CBoundingBox	getBoundingBox(void) const override;

    private:
        Vec3f m_normal;
        Vec2f m_texture_coords;
    };
}
