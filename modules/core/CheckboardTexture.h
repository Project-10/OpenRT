
#include "Texture.h"
#include "Ray.h"

namespace rt {
    class CCheckboardTexture : public CTexture {
    public:
        DllExport CCheckboardTexture() = default;

        // Dervives from CTexture and tries to implement it its own version for
        // a checkboard pattern.
        DllExport Vec3f get3DTexel(const Vec3f &point) override;

        // Will always return true because it's a procedur. texture.
        DllExport bool isProcedural() override;

    };

}
