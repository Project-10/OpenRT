
#include "Texture.h"
#include "CircleTexture.h"


namespace rt {

    Vec3f rt::CCircleTexture::get3DTexel(const Vec3f &point) {
        auto length = point - this->solidBoxCenter;
        auto powerFactor = 20;
        auto twoDimDist = sqrt(pow(point[2] - solidBoxCenter[2], 2) + pow(point[1] - solidBoxCenter[1], 2));
        auto value = powerFactor * twoDimDist;
        return (int) floor(value) % 2 != 0 ? Vec3f(0.5, 1, 1) : Vec3f(0, 0.4, 0.3);
    }

    bool CCircleTexture::isProcedural() {
        return true;
    }
}
