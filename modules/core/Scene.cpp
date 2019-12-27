#include "Scene.h"
#include "Sampler.h"
#include "macroses.h"

namespace rt {
	Mat CScene::render(std::shared_ptr<CSampler> pSampler) const
	{
		ptr_camera_t activeCamera = getActiveCamera();
		RT_ASSERT_MSG(activeCamera, "Camera is not found. Add at least one camera to the scene.");
		Mat img(activeCamera->getResolution(), CV_32FC3, Scalar(0)); 	// image array
		
#ifdef DEBUG_PRINT_INFO
		std::cout << "\nNumber of Primitives: " << m_vpPrims.size() << std::endl;
		std::cout << "Number of light sources: " << m_vpLights.size() << std::endl;
		size_t nSamples = 0;
		for (const auto& pLight : m_vpLights) nSamples += pLight->getNumberOfSamples();
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
					getActiveCamera()->InitRay(ray, x, y, pSampler ? pSampler->getNextSample() : Vec2f::all(0.5f));
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
								  
	Mat CScene::renderDepth(void) const {
		ptr_camera_t activeCamera = getActiveCamera();
		RT_ASSERT_MSG(activeCamera, "Camera is not found. Add at least one camera to the scene.");
		Mat depth(activeCamera->getResolution(), CV_32FC1, Scalar(0)); 	// image array
		Ray ray;
		for (int y = 0; y < depth.rows; y++) {
			float* pDepth = depth.ptr<float>(y);
			for (int x = 0; x < depth.cols; x++) {
				getActiveCamera()->InitRay(ray, x, y);
				pDepth[x] = rayTraceDepth(ray);
			}
		}

		return depth;
	}
}
