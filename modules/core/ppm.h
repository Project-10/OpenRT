#pragma once
#include "Shader.h"
#include "Scene.h"
#include "ray.h"
#include "Sampler.h"
#include <unordered_set>
namespace rt{

    struct VisiblePoint{
        Vec3f   hit     = 0;            //x,y,z coords of the visible point
        Vec3f   normal  = 0;            //Normal at hit
        Vec3f   dir     = 0;            //ray direction
        float   brdf    = 1;            //brdf index
        Point2i px      = Point2i(0, 0);//pixel coords
        Vec3f   pxWqt   = 1;            //Weight of the pixel
        float   radius  = 1.5f;         //current photon radius
        int     nPhotons = 1;           //Accumulated Photon count
        Vec3f   color   = Vec3f::all(0);        //Accumulated reflected radiance at visible point
        Vec3f   colorDirect = Vec3f::all(0);    //direct radiance at visible poin

        std::shared_ptr<const IPrim>	prim		= nullptr;
        VisiblePoint() = default;

    };

    struct Photon{
        Vec3f   hit;      //x,y,z coords of the hitpoint
        Vec3f   org;
        Vec3f   normal;   //Normal at hit
        Vec3f   dir;      //ray direction
        Vec3f   radiance = Vec3f::all(0);    //Radiance added to hit point
        float   brdf     = 1;
        std::shared_ptr<const IPrim> prim = nullptr;
        Photon() = default;
        bool operator==(const Photon &r) const{ 
            return (hit[0] == r.hit[0]  && hit[1]  == r.hit[1]  && hit[2] == r.hit[2] );
        }
        Photon(cv::Mat1f pt):hit(pt.at<float>(0),pt.at<float>(1),pt.at<float>(2)){}

    };

    struct TkeyHash{
        /*Hash function to access elements in the photon map*/
        static Vec3f shape;
        std::hash<float> fhash;
        std::size_t  operator()(const Photon &p) const{
            return fhash(p.hit[0] + (shape[0] + 1)*(p.hit[1] + (shape[1] + 1)*p.hit[2]));
        }
    };
    class PPM
    {

    public:
        DllExport PPM(CScene& scene,int nPhotons = 100000, int nIt = 1000,float alpha = 0.7f);
        DllExport ~PPM() = default;
        DllExport Mat render(std::shared_ptr<CSampler> pSampler = nullptr);
    protected :
        DllExport std::optional<VisiblePoint> getVisiblePoint(Ray &,int mx = 9);
        DllExport void  rayTracingStep(std::shared_ptr<CSampler> = nullptr);
        DllExport void  photonTracingStep(Mat_<float> &features);
        DllExport void  radianceEstimationStep(Mat_<float> &features);
        DllExport void  directIllumination(void);
        DllExport Mat   getImage(int = 1);
    private:
        float   m_radius;
        int     m_nPhotons;
        int     m_nReflections  = 4;
        int     m_nIterations;
        float   m_alpha;
        float   m_attenuation   = 0.5f;// light attenuation REVIEW might not be necesary
        float   m_nEmmited      = 0;
        CScene  &m_scene;
        Vec3f   bounds;
        float   m_halfPi        = Pif/2.0f;
        double  mn              = 1000;
        double  mx              = -1000;
        const   int max_elmem   = 2000; //The maximum number of photons returned in the radius search
        std::vector<VisiblePoint> m_visiblePoints;
        std::unordered_set<Photon,TkeyHash> m_photonMap;
        std::vector<int> m_POI; //Points of Interest :Used to track the color changes over a few pixels

    };

}

