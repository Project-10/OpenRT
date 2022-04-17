
#include "Texture.h"
#include "Ray.h"
#include "SolidBox.h"

namespace rt {
    class CCircleTexture : public CTexture {
    public:
        DllExport CCircleTexture() = default;

        DllExport Vec3f get3DTexel(const Vec3f &point) override;

        DllExport bool isProcedural() override;

        void setSolidBox(Vec3f solidBoxC) {
            this->solidBoxCenter = solidBoxC;
        }

    private:
        Vec3f solidBoxCenter;

    };
}
