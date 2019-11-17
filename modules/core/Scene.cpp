#include "Scene.h"

#include "ShaderEyelight.h"
#include "Shader.h"
#include "PrimTriangleSmooth.h"

#include "Sampler.h"

#include <fstream> 

namespace rt {
	void CScene::parseOBJ(const std::string& fileName, std::shared_ptr<IShader> pShader)
	{
		std::ifstream file(fileName);

		if (file.is_open()) {
			std::cout << "Parsing OBJFile : " << fileName << std::endl;

			std::vector<Vec3f> vVertexes;
			std::vector<Vec3f> vNormals;
			std::vector<Vec2f> vTextures;

			std::string line;

			for (;;) {
				if (!getline(file, line)) break;
				std::stringstream ss(line);
				getline(ss, line, ' ');
				if (line == "v") {
					Vec3f v;
					for (int i = 0; i < 3; i++) ss >> v.val[i];
					// std::cout << "Vertex: " << v << std::endl;
					vVertexes.push_back(2 * v);
				}
				else if (line == "vt") {
					Vec2f vt;
					for (int i = 0; i < 2; i++) ss >> vt.val[i];
					vTextures.push_back(vt);
				}
				else if (line == "vn") {
					Vec3f vn;
					for (int i = 0; i < 3; i++) ss >> vn.val[i];
					vNormals.push_back(vn);
				}
				else if (line == "f") {
					int v, n, t;
					Vec3i V, N, T;
					for (int i = 0; i < 3; i++) {
						getline(ss, line, ' ');
						sscanf(line.c_str(), "%d/%d/%d", &v, &t, &n);
						V.val[i] = v - 1;
						T.val[i] = t - 1;
						N.val[i] = n - 1;
					}
					// std::cout << "Face: " << V << std::endl;
					//std::cout << "Normal: " << N << std::endl;
					add(std::make_shared<CPrimTriangle>(pShader, vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]]));
					//add(std::make_shared<CPrimTriangleSmooth>(pShader,  vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]],
					//													vNormals[N.val[0]], vNormals[N.val[1]], vNormals[N.val[2]]));
					//add(std::make_shared<CPrimTriangleSmoothTextured>(vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]],
					//	vNormals[N.val[0]], vNormals[N.val[1]], vNormals[N.val[2]],
					//	vTextures[T.val[0]], vTextures[T.val[1]], vTextures[T.val[2]], pShader));
				}
				else {
					std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
				}
			}

			file.close();
			std::cout << "Finished Parsing" << std::endl;
		}
		else
			std::cout << "ERROR: Can't open OBJFile" << std::endl;
	}


	Mat CScene::render(void) const {
		Mat img(getActiveCamera()->getResolution(), CV_32FC3, Scalar(0)); 	// image array
		
		CSamplerStratified sampler(2, false);
	
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
