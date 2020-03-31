#include "ppm.h"
#include "utilities.h"
#include "ray.h"
namespace rt{

    PPM::PPM(CScene& scene,int nPhotons, int nIt)
    :m_scene(scene)
    ,m_nPhotons(nPhotons)
    ,m_nIterations(nIt)
    {
        bounds = scene.dimension();
    }
    Mat PPM::render(std::shared_ptr<CSampler> pSampler){
        rtPass(pSampler);
        directIllumination();
        Mat img = getImage(pSampler ? pSampler->getNumSamples() : 1);
        savePCL(m_hitpoints,"rtPass.xyz",mn,mx);
        return img;
    }

    void PPM::directIllumination(void){

        for (auto &hp : m_hitpoints){
            Ray D;
            D.org = hp.hit;
            D.hit = hp.prim;
            D.dir = hp.dir;
            D.t = 0;
            hp.color = hp.prim->getShader()->shade(D);
        }
    }

    void PPM::pmPass(){
        //find light intesities
        //distribute #photons to all the lights
        //sample points from each light source

    }
    void PPM::indirectIllumination(void){
        //collect illumination for allhitpoints
    }

    Mat PPM::getImage(int nSamples){
        ptr_camera_t activeCamera = m_scene.getActiveCamera();
        RT_ASSERT_MSG(activeCamera, "ERROR : Camera not Found");
		Mat img(activeCamera->getResolution(), CV_32FC3, Scalar(0)); 	// image array
        for (auto &hp : m_hitpoints){
            Vec3f *px = img.ptr<Vec3f>(hp.px.x,hp.px.y);
            *px += (hp.color/nSamples);
        }
        minMaxLoc(img,&mn,&mx);
        img.convertTo(img, CV_8UC3, 255);
        return img;
    }

    void PPM::rtPass(std::shared_ptr<CSampler> pSampler){
        ptr_camera_t activeCamera = m_scene.getActiveCamera();
        RT_ASSERT_MSG(activeCamera, "ERROR : Camera not Found");
        Size2i res = activeCamera->getResolution();
        Ray ray;
        for (int i = 0; i < res.width; i++){
            for (int j = 0; j < res.height; j++){
                size_t nSamples = pSampler ? pSampler->getNumSamples() : 1;
				for (size_t s = 0; s < nSamples; s++) {
                    m_scene.getActiveCamera()->InitRay(ray, i, j, pSampler ? pSampler->getNextSample() : Vec2f::all(0.5f));
                    auto pt = getVisiblePoint(ray);
                    if(pt.has_value()){
                        Hitpoint ht = pt.value();
                        ht.px = Point2i(j,i);
                        m_hitpoints.push_back(ht);
                        //TODO Keep track of samples per px, e.g we cant div by nSamples if some rays went outside the scene (may put noise towards the ends of the scene )
                    }
                    
                }

            }
        }
        std::cout<<"-- count --"<<m_hitpoints.size()<<std::endl;
        

    }

    std::optional<Hitpoint> PPM::getVisiblePoint(Ray &ray){
        if(m_scene.pathTrace(ray)){
            //Ray hits an object, create hitpoint
            Hitpoint ht;
            ht.hit = ray.hitPoint();
            ht.normal = ray.hit->getNormal(ray);
            ht.dir = ray.dir;
            ht.prim = ray.hit;
            ht.brdf = 1; //TODO Set a value her
            //Check if surface is reflective/refractive
            auto I = ray.hit->getShader()->interaction(ray);
            if(I){
                //Trace ray to find diffuse surface
                if(I.value().counter < 5){//TODO use Russian Roulette
                    //continue RT until a non specular surface is found, otherwise use the last contact point (is ray goes out of bounds)
                    return (getVisiblePoint(I.value())).value_or(ht);
                }
            }else{
                return ht;
            }
        }
        return std::nullopt;

    }

}