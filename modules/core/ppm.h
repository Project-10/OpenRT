#pragma once
#include "Shader.h"
#include "Scene.h"
#include "ray.h"
#include "Sampler.h"

namespace rt{

    struct Hitpoint{
        Vec3f hit = 0;      //x,y,z coords of the hitpoint
        Vec3f normal = 0;   //Normal at hit
        Vec3f dir = 0;      //ray direction
        int  brdf = 1;      //brdf index
        Point2i px = 0;       //pixel coords
        Vec3f pxWqt = 1;    //Weight of the pixel
        float radius = 2.0f;   //current photon radius
        int nPhotons = 0;   //Accumulated Photon count
        Vec3f color = 0;    //Accumulated reflected flux at hitpoint
        std::shared_ptr<const IPrim>	prim		= nullptr;
        Hitpoint() = default;
        Hitpoint(const Hitpoint& b){
            hit = b.hit;
            normal = b.normal;
            dir = b.dir;
            brdf = b.brdf;
            px = b.px;
            pxWqt = b.pxWqt;
            radius = b.radius;
            nPhotons = b.nPhotons;
            color = b.color;
            prim = b.prim;
        };
        // ~Hitpoint() = default;
        
    };

    struct Photon{
        Vec3f hit;      //x,y,z coords of the hitpoint
        Vec3f normal;   //Normal at hit
        Vec3f dir;      //ray direction
        Vec3f radiance;    //Radiance added to hit point
    };

    class PPM
    {

    public:
        DllExport PPM(CScene& scene,int nPhotons = 100, int nIt = 10);
        DllExport ~PPM() = default;
        DllExport Mat render(std::shared_ptr<CSampler> pSampler = nullptr);
    protected :
        DllExport std::optional<Hitpoint> getVisiblePoint(Ray &);
        DllExport void rtPass(std::shared_ptr<CSampler> = nullptr);
        DllExport void directIllumination(void);
        DllExport void pmPass();
        DllExport void indirectIllumination(void);
        DllExport Mat getImage(int = 1);
    private:
        float m_radius;
        int m_nPhotons;
        int m_nIterations;
        CScene &m_scene;
        Vec3f bounds;
        std::vector<Hitpoint> m_hitpoints;
        double mn = 1000,mx = 0;
    };

}

