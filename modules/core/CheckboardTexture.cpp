
#include "Texture.h"
#include "CheckboardTexture.h"


namespace rt {

    Vec3f CCheckboardTexture::get3DTexel(const Vec3f &point) {
        float u = point.val[0];
        float v = point.val[1];
        float w = point.val[2];

        float k = 20;
        auto isRough = true;
        auto xSine = sinf(k * u);
        auto zSine = cosf(k * v);
        auto yCos = sinf(k * w);
        float intensity = (1 +  xSine * yCos * zSine) / 2;

        Vec3f color = Vec3f::all(intensity);
        return color;
    }

    bool CCheckboardTexture::isProcedural() {
        return true;
    }

}
