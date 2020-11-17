#include <fstream>
#include "Scene.h"
#include "Ray.h"
#include "Solid.h"
#include "macroses.h"

namespace rt {
	void CScene::clear(void) 
	{
		m_vpPrims.clear();
		m_vpLights.clear();
		m_vpCameras.clear();
		m_activeCamera = 0;
	}
	
	void CScene::add(const ptr_prim_t pPrim) 
	{ 
		m_vpPrims.push_back(pPrim);
	}

	void CScene::add(const CSolid& solid)
	{
		for (const auto& pPrim : solid.getPrims())
			add(pPrim);
	}

	void CScene::add(const ptr_light_t pLight) 
	{ 
		m_vpLights.push_back(pLight); 
	}

	void CScene::add(const ptr_camera_t pCamera) 
	{
		m_vpCameras.push_back(pCamera);
		m_activeCamera = m_vpCameras.size() - 1;
	}

	void CScene::setActiveCamera(size_t activeCamera) 
	{ 
		if (activeCamera < m_vpCameras.size())
			m_activeCamera = activeCamera;
		else
			RT_WARNING("Camera index (%zu) exseeds the number of cameras in scene (%zu) and was not set.", activeCamera, m_vpCameras.size());
	}

	void CScene::buildAccelStructure(size_t maxDepth, size_t minPrimitives)
	{ 
#ifdef ENABLE_BSP
		m_pBSPTree->build(m_vpPrims, maxDepth, minPrimitives);
#else
		RT_WARNING("BSP support is not enabled");
#endif		
	}

	Mat CScene::render(ptr_sampler_t pSampler, bool splitView) const
	{
	    Mat lastRender;
	    if (splitView)
	    {
#ifdef ENABLE_CACHE
	        lastRender = load(cachePath);
#else
            RT_WARNING("Caching support is not enabled");
#endif
	    }

		ptr_camera_t activeCamera = getActiveCamera();
		RT_ASSERT_MSG(activeCamera, "Camera is not found. Add at least one camera to the scene.");
		Mat img(activeCamera->getResolution(), CV_32FC3, Scalar(0)); 	// image array
		
#ifdef DEBUG_PRINT_INFO
		std::cout << "\nNumber of Primitives: " << m_vpPrims.size() << std::endl;
		std::cout << "Number of light sources: " << m_vpLights.size() << std::endl;
		size_t nSamples = 0;
		for (const auto& pLight : m_vpLights) nSamples += pLight->getNumSamples();
		if (pSampler) nSamples *= pSampler->getNumSamples();
		std::cout << "Rays per Pixel: " << nSamples << std::endl;
#endif
		
#ifdef ENABLE_PDP
		parallel_for_(Range(0, img.rows), [&](const Range& range) {
#else
		const Range range(0, img.rows);
#endif
		Ray ray;
		for (int y = range.start; y < range.end; y++) {
			Vec3f* pImg = img.ptr<Vec3f>(y);
			for (int x = 0; x < img.cols; x++) {
				size_t nSamples = pSampler ? pSampler->getNumSamples() : 1;
				for (size_t s = 0; s < nSamples; s++) {
					activeCamera->InitRay(ray, x, y, pSampler ? pSampler->getNextSample() : Vec2f::all(0.5f));
					pImg[x] += rayTrace(ray);
				}
				pImg[x] = (1.0f / nSamples) * pImg[x];
			}
		}
#ifdef ENABLE_PDP
		});
#endif
		img.convertTo(img, CV_8UC3, 255);
		if (splitView)
		{
#ifdef ENABLE_CACHE
            Mat final_mat(cv::Size(img.size().width+lastRender.size().width, img.size().height > lastRender.size().height ? img.size().height : lastRender.size().height), CV_8UC3);
            img.copyTo(final_mat(cv::Rect(  0, 0, img.size().width, img.size().height)));
            if (lastRender.size().height > 0 || lastRender.size().width > 0)
                lastRender.copyTo(final_mat(cv::Rect(img.size().width, 0, lastRender.size().width, lastRender.size().height)));
		    if (!this->save(cachePath, img))
		        RT_WARNING("OpenRT failed to cache the mat. This might affect your next render.");
		    return final_mat;
#else
            RT_WARNING("Caching support is not enabled");
#endif
        }
		return img;
	}
			
	Mat CScene::renderDepth(ptr_sampler_t pSampler) const 
	{
		ptr_camera_t activeCamera = getActiveCamera();
		RT_ASSERT_MSG(activeCamera, "Camera is not found. Add at least one camera to the scene.");
		Mat depth(activeCamera->getResolution(), CV_64FC1, Scalar(0)); 	// depth-image array

#ifdef ENABLE_PDP
		parallel_for_(Range(0, depth.rows), [&](const Range& range) {
#else
		const Range range(0, depth.rows);
#endif
		Ray ray;
		for (int y = 0; y < depth.rows; y++) {
			double* pDepth = depth.ptr<double>(y);
			for (int x = 0; x < depth.cols; x++) {
				size_t nSamples = pSampler ? pSampler->getNumSamples() : 1;
				for (size_t s = 0; s < nSamples; s++) {
					activeCamera->InitRay(ray, x, y, pSampler ? pSampler->getNextSample() : Vec2f::all(0.5f));
					pDepth[x] += rayTraceDepth(ray);
				}
				pDepth[x] = (1.0f / nSamples) * pDepth[x];
			}
		}
#ifdef ENABLE_PDP
			});
#endif
		return depth;
	}

	// -------------------------------------- Service Methods --------------------------------------
	bool CScene::intersect(Ray& ray) const
	{
#ifdef ENABLE_BSP
		return m_pBSPTree->intersect(ray);
#else
		bool hit = false;
		for (auto& pPrim : m_vpPrims)
			hit |= pPrim->intersect(ray);
		return hit;
#endif
	}

	bool CScene::if_intersect(const Ray& ray) const 
	{
#ifdef ENABLE_BSP
		return m_pBSPTree->intersect(lvalue_cast(Ray(ray)));
#else
		for (auto& pPrim : m_vpPrims)
			if (pPrim->if_intersect(ray)) return true;
		return false;
#endif
	}

	Vec3f CScene::rayTrace(Ray& ray) const 
	{ 
		return intersect(ray) ? ray.hit->getShader()->shade(ray) : m_bgColor; 
	}

	double CScene::rayTraceDepth(Ray& ray) const 
	{ 
		return intersect(ray) ? ray.t : std::numeric_limits<double>::infinity();
	}

    bool CScene::save(const std::string &fileName, const Mat& image) const {
        std::ofstream ofs(fileName, std::ios::binary);
        if(!ofs.is_open()){
            return false;
        }
        if(image.empty()){
            int s = 0;
            ofs.write((const char*)(&s), sizeof(int));
            return true;
        }
        int type = image.type();
        ofs.write((const char*)(&image.rows), sizeof(int));
        ofs.write((const char*)(&image.cols), sizeof(int));
        ofs.write((const char*)(&type), sizeof(int));
        ofs.write((const char*)(image.data), image.elemSize() * image.total());

        return true;
    }

    Mat CScene::load(const std::string &fileName) const {
        std::ifstream ifs(fileName, std::ios::binary);
        Mat image;
        if(!ifs.is_open()){
            return image;
        }

        int rows, cols, type;
        ifs.read((char*)(&rows), sizeof(int));
        if(rows==0){
            return image;
        }
        ifs.read((char*)(&cols), sizeof(int));
        ifs.read((char*)(&type), sizeof(int));

        image.release();
        image.create(rows, cols, type);
        ifs.read((char*)(image.data), image.elemSize() * image.total());
        return image;
    }

}

