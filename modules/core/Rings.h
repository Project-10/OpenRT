//
//  Rings.hpp
//  Demo_AreaLight
//
//  Created by Mahmoud El Bergui on 18.04.22.
//
#pragma once
#include"Texture.h"
#include"Ray.h"


 namespace rt{

class CRings : public CTexture{
    public:
    DllExport CRings() = default;
    
    
    //Genrate the stripes pattern using 3D coordinates
    DllExport Vec3f getTextel3D(const Vec3f &uvw) override;
    
    DllExport bool isProcedural() override;
};
}
