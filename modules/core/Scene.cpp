#include "Scene.h"
#include "Ray.h"
#include "ShaderDiffuse.h"
#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"
#include "PrimDisc.h"
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
	
	std::shared_ptr<CPrimSphere> CScene::addSphere(const Vec3f& origin, float radius, const Vec3f& color) {
		auto shader = std::make_shared<CShaderDiffuse>(*this, color);
		auto prim = std::make_shared<CPrimSphere>(shader, origin, radius);
		add(prim);
		return prim;
	}

	std::shared_ptr<CPrimPlane> CScene::addPlane(const Vec3f& origin, const Vec3f& normal, const Vec3f& color) {
		auto shader = std::make_shared<CShaderDiffuse>(*this, color);
		auto prim = std::make_shared<CPrimPlane>(shader, origin, normal);
		add(prim);
		return prim;
	}

	std::shared_ptr<CPrimDisc> CScene::addDisc(const Vec3f& origin, const Vec3f& normal, float radius, float innerRadius, const Vec3f& color) {
		auto shader = std::make_shared<CShaderDiffuse>(*this, color);
		auto prim = std::make_shared<CPrimDisc>(shader, origin, normal, radius, innerRadius);
		add(prim);
		return prim;
	}

	std::shared_ptr<CPrimTriangle> CScene::addTriangle(const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec2f& ta, const Vec2f& tb, const Vec2f& tc, std::optional<Vec3f> na, std::optional<Vec3f> nb, std::optional<Vec3f> nc, const Vec3f& color) {
		auto shader = std::make_shared<CShaderDiffuse>(*this, color);
		auto prim = std::make_shared<CPrimTriangle>(shader, a, b, c, ta, tb, tc, na, nb, nc);
		add(prim);
		return prim;
	}

	std::shared_ptr<CPrimTriangle> CScene::addTriangle(const Vec3f& origin, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec2f& ta, const Vec2f& tb, const Vec2f& tc, std::optional<Vec3f> na, std::optional<Vec3f> nb, std::optional<Vec3f> nc, const Vec3f& color) {
		auto shader = std::make_shared<CShaderDiffuse>(*this, color);
		auto prim = std::make_shared<CPrimTriangle>(shader, origin, a, b, c, ta, tb, tc, na, nb, nc);
		add(prim);
		return prim;
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

	void CScene::render_tile(Mat& img, ptr_sampler_t pSampler, int y_start, int y_end, int x_start, int x_end) const
	{
		ptr_camera_t activeCamera = getActiveCamera();
		RT_ASSERT_MSG(activeCamera, "Camera is not found. Add at least one camera to the scene.");
		const size_t nSamples = pSampler ? pSampler->getNumSamples() : 1;
#ifdef ENABLE_PDP		
		parallel_for_(Range(y_start, y_end), [&](const Range& range) {
#else		
		const Range range(y_start, y_end);
#endif
		Ray ray;
		for (int y = range.start; y < range.end; y++) {
			Vec3f* pImg = img.ptr<Vec3f>(y);
			for (int x = x_start; x < x_end; x++) 
				for (size_t s = 0; s < nSamples; s++) {
					activeCamera->InitRay(ray, x, y, pSampler ? pSampler->getNextSample(s) : Vec2f::all(0.5f));
					pImg[x] += rayTrace(ray);
				}
		}
#ifdef ENABLE_PDP
		});
#endif
	}

	Mat CScene::render(ptr_sampler_t pSampler, size_t tileSize) const
	{
		ptr_camera_t activeCamera = getActiveCamera();
		RT_ASSERT_MSG(activeCamera, "Camera is not found. Add at least one camera to the scene.");
		Mat img(activeCamera->getResolution(), CV_32FC3, Scalar(0)); 	// image array
		const size_t nSamples = pSampler ? pSampler->getNumSamples() : 1;
		
#ifdef DEBUG_PRINT_INFO
		std::cout << "\nNumber of Primitives: " << m_vpPrims.size() << std::endl;
		std::cout << "Number of light sources: " << m_vpLights.size() << std::endl;
		size_t nSamples = 0;
		for (const auto& pLight : m_vpLights) nSamples += pLight->getNumSamples();
		if (pSampler) nSamples *= pSampler->getNumSamples();
		std::cout << "Rays per Pixel: " << nSamples << std::endl;
#endif
		if (tileSize > 0) {
			const int nTilesX = static_cast<int>((img.cols + tileSize - 1) / tileSize);
			const int nTilesY = static_cast<int>((img.rows + tileSize - 1) / tileSize);
		
			Mat img1;
			for (int y = 0; y < nTilesY; y++)
				for (int x = 0; x < nTilesX; x++) {
				
					render_tile(img, pSampler, 
						static_cast<int>(y * tileSize),
						std::min(static_cast<int>((y + 1) * tileSize), img.rows),
						static_cast<int>(x * tileSize),
						std::min(static_cast<int>((x + 1) * tileSize), img.cols)
					);
				
					img.convertTo(img1, CV_8UC3, 255.0 / nSamples);
					imshow("Render", img1);
					waitKey(1);
				}
		}
		else {
			const Range range(0, img.rows);
#ifdef ENABLE_PDP
			parallel_for_(range, [&](const Range& range) {
#endif
			Ray ray;
			for (int y = range.start; y < range.end; y++) {
				Vec3f* pImg = img.ptr<Vec3f>(y);
				for (int x = 0; x < img.cols; x++) {
					for (size_t s = 0; s < nSamples; s++) {
						activeCamera->InitRay(ray, x, y, pSampler ? pSampler->getNextSample(s) : Vec2f::all(0.5f));
						pImg[x] += rayTrace(ray);
					}
				}
			}
#ifdef ENABLE_PDP
			});
#endif
		}
		
		img.convertTo(img, CV_8UC3, 255.0 / nSamples);
#ifdef ENABLE_CACHE
		imwrite(m_lriFileName, img);
#endif
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
		for (int y = range.start; y < range.end; y++) {
			double* pDepth = depth.ptr<double>(y);
			for (int x = 0; x < depth.cols; x++) {
				size_t nSamples = pSampler ? pSampler->getNumSamples() : 1;
				for (size_t s = 0; s < nSamples; s++) {
					activeCamera->InitRay(ray, x, y, pSampler ? pSampler->getNextSample(s) : Vec2f::all(0.5f));
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

	float CScene::evalOcclusion(const Ray& ray) const
	{
#ifdef SHADOW_TYPE_FAST
		return if_intersect(ray) ? 0.0f : 1.0f;
#elif defined(SHADOW_TYPE_TRANSPARENT)
		Ray r = ray;
			
		float res = 1.0f;	// percentage of light arriving to the surface
		if (intersect(r)) {
			res = 1.0f - r.hit->getShader()->getOpacity(r);
			if ((res >= Epsilon) && (r.counter++ < maxRayCounter)) {
				r.org = r.hitPoint();
				r.t = ray.t - r.t;
				r.hit = nullptr;
				res *= evalOcclusion(r);
			}
		}
		return res;
#elif defined(SHADOW_TYPE_COLORED)
	#error "The COLORED shadow type is not implemented. Please use another shadow model."
#else
	#error "Unknown shadow processing type. Please choose FAST, TRANSPARENT, or COLORED."
#endif
	}

	Vec3f CScene::rayTrace(Ray& ray) const 
	{ 
		if (intersect(ray)) return ray.hit->getShader()->shade(ray);	// intersection -> return color of the hit object
		return m_bgMap ? m_bgMap->getTexel(ray) : m_bgColor;			// No intersection -> return scene background
	}

	double CScene::rayTraceDepth(Ray& ray) const 
	{ 
		return intersect(ray) ? ray.t : std::numeric_limits<double>::infinity();
	}

}
