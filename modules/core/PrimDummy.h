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
        DllExport CPrimDummy(const ptr_shader_t& pShader, const Vec3f& normal, const Vec2f& textureCoord)
                : IPrim(pShader)
                , m_normal(normal)
                , m_textureCoord(textureCoord)
        {
            normalize(m_normal);
        }
        DllExport ~CPrimDummy() override = default;

        DllExport bool 			intersect(Ray& ray) const override;
        DllExport bool 			if_intersect(const Ray& ray) const override;
        DllExport void 			transform(const Mat& T) override;
        DllExport Vec3f			getOrigin() const override;
        DllExport Vec3f 		getNormal(const Ray&) const override;
        DllExport Vec2f			getTextureCoords(const Ray& ray) const override;
        DllExport CBoundingBox	getBoundingBox() const override;

    private:
        Vec3f m_normal;
        Vec2f m_textureCoord;
    };
}

