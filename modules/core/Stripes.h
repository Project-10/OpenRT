#pragma once


#include"Texture.h"
#include"Ray.h"


 namespace rt{

class CStripes : public CTexture{
    public:
    DllExport CStripes() = default;
    
    
    //Genrate the stripes pattern using 3D coordinates
    DllExport Vec3f getTextel3D(const Vec3f &uvw) override;
    
    DllExport bool isProcedural() override;
};
}
