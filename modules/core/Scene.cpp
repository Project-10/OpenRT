#include "Scene.h"
#include "Ray.h"
#include "Solid.h"
#include "macroses.h"
#include "random.h"
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
		
#ifdef ENABLE_PDP
		parallel_for_(Range(0, img.rows), [&](const Range& range) {
#else
		const Range range(0, img.rows);
#endif
			Ray ray;
			size_t nSamples = pSampler ? pSampler->getNumSamples() : 1;
			for (int y = range.start; y < range.end; y++) {
				Vec3f* pImg = img.ptr<Vec3f>(y);
				for (int x = 0; x < img.cols; x++) {
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
#ifdef ENABLE_CACHE
		imwrite(m_lriFileName, img);
#endif
		return img;
	}
		
	Mat CScene::render(ptr_sampler_t pSampler, double noiseThreshold, int maxSamples) const
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


#ifdef ENABLE_PDP
		parallel_for_(Range(0, img.rows), [&](const Range& range) {
#else
		const Range range(0, img.rows);
#endif
		Ray ray;
		size_t nSamples = pSampler ? pSampler->getNumSamples() : 0;
		for (int y = range.start; y < range.end; y++) {
			Vec3f* pImg = img.ptr<Vec3f>(y);
			for (int x = 0; x < img.cols; x++) {
				//std::cout << "pixel: " << y << " " << x << std::endl;
				int totalSamples = 0;
				for (size_t s = 0; s < nSamples; s++) {
					activeCamera->InitRay(ray, x, y, pSampler ? pSampler->getNextSample() : Vec2f::all(0.5f));
					pImg[x] += rayTrace(ray);
				}
				if (nSamples > 0) pImg[x] = (1.0f / nSamples) * pImg[x];
				Vec3f adaptiveColor = rayTraceAdaptive(ray, x, y, noiseThreshold, maxSamples, totalSamples);
				pImg[x] = pImg[x] * (double)nSamples + adaptiveColor * totalSamples;
				pImg[x] *= 1.0 / (nSamples + totalSamples);
				//pImg[x] = totalSamples / maxSamples * RGB(1, 1, 1);
			}
		}
#ifdef ENABLE_PDP
	});
#endif

		img.convertTo(img, CV_8UC3, 255);
		return img;
	};

	Vec3f CScene::rayTraceAdaptive(Ray ray, int x, int y, double noiseThreshold, int maxSamples, int& totalsamples) const {
		ptr_camera_t activeCamera = getActiveCamera();
		std::function<Vec3f(double, double, double, double, std::vector<Vec3f>&, int, int, int&)> sample =
			[&, this](double x0, double y0, double xmax, double ymax, std::vector<Vec3f>& grid, 
				int quadrant, int depth, int& totalsamples) -> Vec3f {
			if (quadrant == 0) {
				activeCamera->InitRay(ray, x, y, Vec2f(x0, ymax));
				grid[0] = rayTrace(ray);
				activeCamera->InitRay(ray, x, y, Vec2f(xmax, ymax));
				grid[1] = rayTrace(ray);
				activeCamera->InitRay(ray, x, y, Vec2f(x0, y0));
				grid[2] = rayTrace(ray);
				activeCamera->InitRay(ray, x, y, Vec2f(xmax, y0));
				grid[3] = rayTrace(ray);
			}
			else if (quadrant == 1) {
				activeCamera->InitRay(ray, x, y, Vec2f(xmax, ymax));
				grid[1] = rayTrace(ray);
				activeCamera->InitRay(ray, x, y, Vec2f(x0, y0));
				grid[2] = rayTrace(ray);
			}
			else if (quadrant == 2) {
				activeCamera->InitRay(ray, x, y, Vec2f(xmax, y0));
				grid[3] = rayTrace(ray);
			}
			else if (quadrant == 3) {
				activeCamera->InitRay(ray, x, y, Vec2f(x0, y0));
				grid[2] = rayTrace(ray);
			}
			else if (quadrant == 4) {
				activeCamera->InitRay(ray, x, y, Vec2f(x0, ymax));
				grid[0] = rayTrace(ray);
			}
			Vec3f P = (grid[0] + grid[1] + grid[2] + grid[3]) / 4.f;
			if (depth < 1) {
				totalsamples++;
				return P;
			}
			double rx = (x0 + xmax) / 2;
			double ry = (y0 + ymax) / 2;
			activeCamera->InitRay(ray, x, y, Vec2f(rx, ry));
			Vec3f Center = rayTrace(ray);
			double error = norm(Center, P);

			if (error <= noiseThreshold) {
				totalsamples++;
				return P;
			}
			depth--;
			
			P = Vec3f::all(0.f);
			std::vector<Vec3f> c { grid[0], Vec3f::all(-1),  Vec3f::all(-1),  Center };
			P += sample(x0, ry, rx, ymax, c, 1, depth, totalsamples);
			c = { c[1], grid[1],  Center, Vec3f::all(-1) };
			P += sample(rx, ry, xmax, ymax, c, 2, depth, totalsamples);
			c = { Center, c[3],  Vec3f::all(-1),  grid[3] };
			P += sample(rx, y0, xmax, ry, c, 3, depth, totalsamples);
			c = { Vec3f::all(-1), Center,  grid[2],  c[2] };
			P += sample(x0, y0, rx, ry, c, 4, depth, totalsamples);
			P /= 4.f;
			totalsamples++;
			return P;
		};
		int maxdepth = log(maxSamples) / log(4);
		std::vector<Vec3f> grid{ Vec3f::all(-1) ,  Vec3f::all(-1) ,  Vec3f::all(-1) ,  Vec3f::all(-1) };
		return sample(0.f, 0.f, 1.f, 1.f, grid, 0, maxdepth, totalsamples);
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
		for (int y = range.start; y < range.end; y++) {
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

	Mat CScene::getLastRenderedImage(void) const
	{
#ifdef ENABLE_CACHE
		Mat res = imread(m_lriFileName, IMREAD_COLOR);   // Read the file
		RT_IF_WARNING(res.empty(), "Failed to read last saved image: image not found.");
		return res;
#else
		RT_WARNING("Caching support is not enabled");
		return Mat();
#endif
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

}
