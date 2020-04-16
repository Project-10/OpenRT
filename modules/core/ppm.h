#pragma once
#include "Shader.h"
#include "Scene.h"
#include "ray.h"
#include "Sampler.h"
#include <unordered_set>
namespace rt{

    struct Hitpoint{
        Vec3f hit = 0;      //x,y,z coords of the hitpoint
        Vec3f normal = 0;   //Normal at hit
        Vec3f dir = 0;      //ray direction
        float  brdf = 1;      //brdf index
        Point2i px = 0;       //pixel coords
        Vec3f pxWqt = 1;    //Weight of the pixel
        float radius = 4.0f;   //current photon radius
        int nPhotons = 1;   //Accumulated Photon count
        Vec3f color = Vec3f::all(0);    //Accumulated reflected flux at hitpoint
        Vec3f colorDirect = Vec3f::all(0);    //Accumulated reflected flux at hitpoint

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
        }
        // ~Hitpoint() = default;
    };

    struct Photon{
        Vec3f hit;      //x,y,z coords of the hitpoint
        Vec3f org;
        Vec3f normal;   //Normal at hit
        Vec3f dir;      //ray direction
        std::shared_ptr<const IPrim>	prim		= nullptr;
        Vec3f radiance = Vec3f::all(0);    //Radiance added to hit point
        float brdf = 1;
        Photon() = default;
        Photon(const Photon& b){
            hit = b.hit;
            radiance = b.radiance;
        }
        bool operator==(const Photon &r) const{ 
            return (hit[0] == r.hit[0]  && hit[1]  == r.hit[1]  && hit[2] == r.hit[2] );
        }
        Photon(cv::Mat1f pt):hit(pt.at<float>(0),pt.at<float>(1),pt.at<float>(2)){}

    };

    struct TkeyHash{
        // std::vector<float> shape = {556.0f, 548.8f, 559.2f}; //FIXME Not hard coded scene size here!
        static Vec3f shape;
        std::hash<float> fhash;
        std::size_t  operator()(const Photon &p) const{
            return fhash(p.hit[0] + (shape[0] + 1)*(p.hit[1] + (shape[1] + 1)*p.hit[2]));
        }
    };
    class PPM
    {

    public:
        DllExport PPM(CScene& scene,int nPhotons = 150000, int nIt = 1000);
        DllExport ~PPM() = default;
        DllExport Mat render(std::shared_ptr<CSampler> pSampler = nullptr);
    protected :
        DllExport std::optional<Hitpoint> getVisiblePoint(Ray &,int mx = 9);
        DllExport void rtPass(std::shared_ptr<CSampler> = nullptr);
        DllExport void directIllumination(void);
        DllExport void pmPass(Mat_<float> &features);
        DllExport void indirectIllumination(Mat_<float> &features);
        DllExport Mat getImage(int = 1);
    private:
        float m_radius;
        int m_nPhotons;
        int m_nReflections = 3;
        int m_nIterations;
        float m_alpha = 0.7f;
        float m_attenuation = 0.7;//0.7
        float m_nEmmited = 0;
        CScene &m_scene;
        Vec3f bounds;
        std::vector<Hitpoint> m_hitpoints;
        // std::vector<Photon> m_photons;
        std::unordered_set<Photon,TkeyHash> m_photons;
        double mn = 1000,mx = -1000;
        const int max_elmem = 2000;

    };

}

