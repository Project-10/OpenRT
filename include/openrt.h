#pragma once

#include "core/Scene.h"

#include "core/CameraPerspective.h"

#include "core/PrimSphere.h"
#include "core/PrimPlane.h"
#include "core/PrimTriangle.h"

#include "core/ShaderFlat.h"
#include "core/ShaderEyelight.h"
#include "core/ShaderPhong.h"

#include "core/LightPoint.h"
#include "core/LightArea.h"

/**
Main page documentation
*/

namespace rt {
	Mat RenderFrame(CScene& scene)
	{
		Mat img(scene.getActiveCamera()->getResolution(), CV_32FC3); 	// image array
		
#ifdef ENABLE_PPL
		concurrency::parallel_for(0, img.rows, [&](int y) {
			Ray ray;
#else
		Ray ray;
		for (int y = 0; y < img.rows; y++) {
#endif
			Vec3f *pImg = img.ptr<Vec3f>(y);
			for (int x = 0; x < img.cols; x++) {
				scene.getActiveCamera()->InitRay(x, y, ray);
				pImg[x] = scene.rayTrace(ray);
			}
		}
#ifdef ENABLE_PPL
		);
#endif
		
		img.convertTo(img, CV_8UC3, 255);
		return img;
	}
}
