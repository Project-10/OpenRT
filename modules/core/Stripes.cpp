

#include "Stripes.h"
#include"Texture.h"

namespace rt{

Vec3f CStripes::getTextel3D(const Vec3f& uvw){
    
    float u = uvw.val[0];
    float v = uvw.val[1];
    float w = uvw.val[2];

    float periods= 5;
    auto xSine = sinf(periods * u);
    auto zSine = cosf(periods * v);
    auto yCos = sinf(periods * w);
    float intensity = (1 + xSine) / 2;
    
    std::cout << intensity << std::endl;

//    Vec3f color = Vec3f(intensity , intensity , 1);
//    return color;
    
    return (intensity > 0.5) ? Vec3f(0,0,255) : Vec3f(255, 255 ,255);

}

bool CStripes::isProcedural(){
    return true;
}
}


