#include "Scene.h"
#include "ray.h"
#include "Solid.h"
#include "macroses.h"

//#include "Sampler.h"
//#include "macroses.h"

namespace rt {
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

	void CScene::buildAccelStructure(void) 
	{ 
#ifdef ENABLE_BSP
		m_pBSPTree = std::make_unique<BSPTree>(m_vpPrims); 
#else 
		RT_WARNING("BSP support is not enabled");
#endif		
	}

	Mat CScene::render(ptr_sampler_t pSampler) const
	{
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
		
#ifdef ENABLE_PPL
		concurrency::parallel_for(0, img.rows, [&](int y) {
			Ray ray;
#else
		Ray ray;
		for (int y = 0; y < img.rows; y++) {
			//printf("%.2f%%\n", static_cast<float>(100 * y)/img.rows);
#endif
			Vec3f* pImg = img.ptr<Vec3f>(y);
			for (int x = 0; x < img.cols; x++) {
				size_t nSamples = pSampler ? pSampler->getNumSamples() : 1;
				for (size_t s = 0; s < nSamples; s++) {
					activeCamera->InitRay(ray, x, y, pSampler ? pSampler->getNextSample() : Vec2f::all(0.5f));
					pImg[x] += rayTrace(ray);
				}
				pImg[x] = (1.0f / nSamples) * pImg[x] ;
			}
		}
#ifdef ENABLE_PPL
		);
#endif
		img.convertTo(img, CV_8UC3, 255);
		return img;
	}
			
	Mat CScene::renderDepth(ptr_sampler_t pSampler) const 
	{
		ptr_camera_t activeCamera = getActiveCamera();
		RT_ASSERT_MSG(activeCamera, "Camera is not found. Add at least one camera to the scene.");
		Mat depth(activeCamera->getResolution(), CV_64FC1, Scalar(0)); 	// depth-image array

#ifdef ENABLE_PPL
		concurrency::parallel_for(0, depth.rows, [&](int y) {
			Ray ray;
#else
		Ray ray;
		for (int y = 0; y < depth.rows; y++) {
#endif
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
#ifdef ENABLE_PPL
		);
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

	bool CScene::if_intersect(const Ray& ray)
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
	
}
