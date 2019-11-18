#include "Scene.h"

#include "PrimTriangleSmooth.h"

#include "Sampler.h"

namespace rt {
	Mat CScene::render(void) const {
		Mat img(getActiveCamera()->getResolution(), CV_32FC3, Scalar(0)); 	// image array
		
		CSamplerStratified sampler(4, false);
	
#ifdef ENABLE_PPL
		concurrency::parallel_for(0, img.rows, [&](int y) {
			Ray ray;
#else
		Ray ray;
		for (int y = 0; y < img.rows; y++) {
#endif
			Vec3f *pImg = img.ptr<Vec3f>(y);
			for (int x = 0; x < img.cols; x++) {
				for (int s = 0; s < sampler.getNumSamples(); s++) {
					Vec2f sample = sampler.getNextSample();
					getActiveCamera()->InitRay(ray, x, y, sample);
					pImg[x] += rayTrace(ray);
				}
				pImg[x] = (1.0f / sampler.getNumSamples()) * pImg[x] ;
			}
		}
#ifdef ENABLE_PPL
		);
#endif
		
		img.convertTo(img, CV_8UC3, 255);
		return img;
	}
}
