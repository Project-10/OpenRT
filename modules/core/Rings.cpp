//
//  Rings.cpp
//  Demo_AreaLight
//
//  Created by Mahmoud El Bergui on 18.04.22.
//



#include "Rings.h"
#include"Texture.h"


namespace rt{

Vec3f CRings::getTextel3D(const Vec3f& uvw){
    
    //Getting coordinate info
    float u = uvw.val[0];
    float v = uvw.val[1];
    float w = uvw.val[2];
    
    //Difference between point and center of the shape
    Vec3f lenght = uvw;
    auto factor = 10;
    float norm = sqrt(pow(lenght[2], 2) + pow(lenght[1], 2));
    auto value = factor * norm;

        return (int) floor(value) % 2 == 0 ? Vec3f(0,0,255) : Vec3f(255,255,255);
}

bool CRings::isProcedural(){
    return true;
}
}



