#include "Solid.h"
#include "PrimTriangle.h"
#include "Transform.h"
#include <fstream> 
#include <utility>

namespace rt {
	// Constructor
	CSolid::CSolid(ptr_shader_t pShader, const std::string& fileName) : m_pivot(Vec3f::all(0))
	{
		std::ifstream file(fileName);

		if (file.is_open()) {
			std::cout << "Parsing OBJFile : " << fileName << std::endl;

			std::vector<Vec3f> vVertexes;
			std::vector<Vec3f> vNormals;
			std::vector<Vec2f> vTextures;

			std::string line;
			std::string key;

			int nFaces = 0;
			for (;;) {
				if (!getline(file, line)) break;
				std::stringstream ss(line);
				getline(ss, key, ' ');	// get key;
				if (key == "v") {
					Vec3f v;
					for (int i = 0; i < 3; i++) ss >> v.val[i];
					// std::cout << "Vertex: " << v << std::endl;
					vVertexes.push_back(v);
				}
				else if (key == "vt") {
					Vec2f vt;
					for (int i = 0; i < 2; i++) ss >> vt.val[i];
					vt[1] = 1 - vt[1];
					vTextures.push_back(vt);
				}
				else if (key == "vn") {
					Vec3f vn;
					for (int i = 0; i < 3; i++) ss >> vn.val[i];
					vNormals.push_back(vn);
				}
				else if (key == "f") {
					nFaces++;
					//if (nFaces > 10000) continue;
					int v, n, t;
					Vec4i V, N, T;
					int i = 0;
					auto tmp = line;
					while (getline(ss, line, ' ')) {
						sscanf(line.c_str(), "%d/%d/%d", &v, &t, &n);
						V.val[i] = v - 1;
						T.val[i] = t - 1;
						N.val[i] = n - 1;
						if (++i == 4) break;
					}
					//std::cout << "Face: " << V << std::endl;
					//std::cout << "Normal: " << N << std::endl;
					//add(std::make_shared<CPrimTriangle>(pShader, vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]]));
					//add(std::make_shared<CPrimTriangleSmooth>(pShader,  vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]],
					//													vNormals[N.val[0]], vNormals[N.val[1]], vNormals[N.val[2]]));
					

					add(std::make_shared<CPrimTriangle>(pShader, vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]],
																 vTextures[T.val[0]], vTextures[T.val[1]], vTextures[T.val[2]],
																 vNormals[N.val[0]], vNormals[N.val[1]], vNormals[N.val[2]]));			

					if (i == 4)
						add(std::make_shared<CPrimTriangle>(pShader, vVertexes[V.val[0]], vVertexes[V.val[2]], vVertexes[V.val[3]],
																	 vTextures[T.val[0]], vTextures[T.val[2]], vTextures[T.val[3]],
																	 vNormals[N.val[0]], vNormals[N.val[2]], vNormals[N.val[3]]));
	
				}
				else if (line == "#") {}
				else {
					std::cout << "Unknown key [" << key << "] met in the OBJ file" << std::endl;
				}
			}

			file.close();
			std::cout << "Finished Parsing" << std::endl;
		}
		else
			std::cout << "ERROR: Can't open OBJFile " << fileName << std::endl;
	}

	void CSolid::transform(const Mat& t)
	{
		CTransform tr;
		Mat T1 = tr.translate(-m_pivot).get();
		Mat T2 = tr.translate(m_pivot).get();
		
		// Apply transformation
		for (auto& pPrim : m_vpPrims) pPrim->transform(t * T1);
		for (auto& pPrim : m_vpPrims) pPrim->transform(T2);
		
		// Update pivot point
		for (int i = 0; i < 3; i++)
			m_pivot.val[i] += t.at<float>(i, 3);
	}

	void CSolid::flipNormal(void)
	{
		for(auto pPrim : m_vpPrims) pPrim->flipNormal();
	}
}

