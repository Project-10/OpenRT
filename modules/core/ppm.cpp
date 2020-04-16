#include "ppm.h"
#include "utilities.h"
#include "ray.h"
namespace rt{

    Vec3f TkeyHash::shape = 0;

    PPM::PPM(CScene& scene,int nPhotons, int nIt)
    :m_scene(scene)
    ,m_nPhotons(nPhotons)
    ,m_nIterations(nIt)
    {
        TkeyHash::shape = scene.dimension();

        std::cout<<" Size of scene "<<TkeyHash::shape<<std::endl;
    }
    Mat PPM::render(std::shared_ptr<CSampler> pSampler){
        rtPass(pSampler);
        directIllumination();

        for (int i = 0; i < m_nIterations; i ++){
            Mat_<float> m_features(0, 3);
            m_photons.clear();
            pmPass(m_features);
            indirectIllumination(m_features);
            Mat imgi = getImage(pSampler ? pSampler->getNumSamples() : 1);
            imwrite("ppm/" + std::to_string(i) + ".png",imgi);
            std::cout<<"Done : "<<i<<std::endl;
        }
        
        // saveRT(m_hitpoints,"rtPass0.xyz",mn,mx);
        // Mat imgd = getImage(pSampler ? pSampler->getNumSamples() : 1);
	    // imwrite("cornell_box_ppm_direct.png",imgd);

        // savePM(m_photons,"pmPass.xyz",mn,mx);
        Mat img = getImage(pSampler ? pSampler->getNumSamples() : 1);
        saveRT(m_hitpoints,"rtPass.xyz",mn,mx);
        return img;
    }
    void PPM::indirectIllumination(Mat_<float> &features){
        //collect illumination for allhitpoints
        flann::GenericIndex<cv::flann::L2<float> > index(features, cvflann::KDTreeIndexParams());
        #ifdef ENABLE_PPL
        concurrency::parallel_for_each(begin(m_hitpoints), end(m_hitpoints), [&](Hitpoint &hp)
        #else            
        for(auto &hp : m_hitpoints)
        #endif
        {
            std::vector<int> ind(max_elmem,-1);
            std::vector<float> d(max_elmem);
            Mat query =  (Mat_<float>(1, 3) << hp.hit[0], hp.hit[1],hp.hit[2]);
            index.radiusSearch(query, ind, d, hp.radius, cvflann::SearchParams(max_elmem));
            int M = 0;
            Vec3f radiance = Vec3f::all(0);
            for (int i = 0; i < ind.size(); i++) {
                if (ind[i] < 0) break;
                Photon photon(features.row(ind[i]));
                auto res = m_photons.equal_range(photon);
                for (auto it = res.first; it != res.second; ++it){
                    if(hp.normal.dot(it->normal) < 0.01f){ //only contributions from the same surface
                        radiance +=  it->radiance*hp.brdf;
                        M ++;
                    }
                }
            }
            hp.radius *= sqrtf( (hp.nPhotons + m_alpha*M) / (hp.nPhotons + M));
            hp.color = (hp.color +  radiance)*( (hp.nPhotons + m_alpha*M) / (hp.nPhotons + M));//hp.brdf*
            hp.nPhotons += m_alpha*M;
            m_nEmmited += M;

        }
        #ifdef ENABLE_PPL
		);
        #endif
    }


    void PPM::directIllumination(void){
        #ifdef ENABLE_PPL
        concurrency::parallel_for_each(begin(m_hitpoints), end(m_hitpoints), [&](Hitpoint &hp)
        #else            
        for(auto &hp : m_hitpoints)
        #endif
        {
            Ray D;
            D.org = hp.hit;
            D.hit = hp.prim;
            D.dir = hp.dir;
            D.t = 0;
            hp.colorDirect = hp.prim->getShader()->shade(D);
        }
        #ifdef ENABLE_PPL
		);
        #endif
    }

    void PPM::pmPass(Mat_<float> &m_features){
        for (auto& pLight : m_scene.getLights()) {
            for(int ii = 0; ii < m_nPhotons; ii++)
            {
                Photon p = pLight->sample_le();
                for(int i = 0; i < m_nReflections; i++){ //FIXME # iterationd
                    Ray ray(p.org,p.dir);
                    auto pt = getVisiblePoint(ray,-1);
                    if(pt.has_value()){
                        Hitpoint ht = pt.value();
                        p.hit = ht.hit;
                        p.prim = ht.prim;
                        Vec3f dir = ht.prim->getShader()->shadePhoton(p);
                        p.radiance *= m_attenuation;
                        mn = comp(mn,p.radiance,0);
                        mx = comp(mx,p.radiance,1);
                            m_photons.insert(Photon(p));
                            Mat pt = (Mat_<float>(1, 3) << p.hit[0], p.hit[1],p.hit[2]);
                            m_features.push_back(pt);
                        //initialise photon for next round
                        p.radiance *= ht.brdf;
                        p.org = ht.hit;
                        p.dir = dir;
                    }else{
                        break; //ray has left scene, stop recursive lookup
                    }
                }
            }
        }
        //find light intesities
        //distribute #photons to all the lights
        //sample points from each light source

    }
    
    Mat PPM::getImage(int nSamples){
        ptr_camera_t activeCamera = m_scene.getActiveCamera();
        RT_ASSERT_MSG(activeCamera, "ERROR : Camera not Found");
		Mat img(activeCamera->getResolution(), CV_32FC3, Scalar(0)); 	// image array
        for (auto &hp : m_hitpoints){
            Vec3f *px = img.ptr<Vec3f>(hp.px.x,hp.px.y);
            // *px += (hp.color/nSamples*hp.nPhotons);
            *px += hp.colorDirect +  hp.color/(Pif*hp.radius*hp.radius*m_nEmmited);
        }
        minMaxLoc(img,&mn,&mx);
        img.convertTo(img, CV_8UC3,255);
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
                        ht.brdf=ray.brdf;
                        m_hitpoints.push_back(ht);
                        //TODO Keep track of samples per px, e.g we cant div by nSamples if some rays went outside the scene (may put noise towards the ends of the scene )
                    }
                    
                }

            }
        }
        std::cout<<"-- count --"<<m_hitpoints.size()<<std::endl;
        

    }

    std::optional<Hitpoint> PPM::getVisiblePoint(Ray &ray,int max){
        if(m_scene.pathTrace(ray)){
            //Ray hits an object, create hitpoint
            Hitpoint ht;
            ht.hit = ray.hitPoint();
            ht.normal = ray.hit->getNormal(ray);
            ht.dir = ray.dir;
            ht.prim = ray.hit;
            ht.brdf = ray.brdf; //TODO Set a value her
            //Check if surface is reflective/refractive
            auto I = ray.hit->getShader()->interaction(ray);
            if(I){
                //Trace ray to find diffuse surface
                if(I.value().counter < max){//TODO use Russian Roulette
                    //continue RT until a non specular surface is found, otherwise use the last contact point (is ray goes out of bounds)
                    return (getVisiblePoint(I.value())).value_or(ht);
                }
            }
            return ht;

        }
        return std::nullopt;

    }

}