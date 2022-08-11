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
				if (key == "g") {
					std::string group_name;
					ss >> group_name;
					std::cout << "Reading group " << group_name << std::endl;
				}
				else if (key == "v") {
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
					std::string v, t, n;
					Vec4i V, N, T;
					int i = 0;
					while (getline(ss, line, ' ')) {
						std::stringstream ss1(line);

						getline(ss1, v, '/');
						getline(ss1, t, '/');
						getline(ss1, n, '/');
						
						V.val[i] = v.empty() ? -1 : std::stoi(v) - 1;
						T.val[i] = t.empty() ? -1 : std::stoi(t) - 1;
						N.val[i] = n.empty() ? -1 : std::stoi(n) - 1;

						if (++i == 4) break;
					}
					//std::cout << "Vertex: " << V << std::endl;
					//std::cout << "Texture: " << T << std::endl;
					//std::cout << "Normal: " << N << std::endl;
					
					bool ifTextures = T.val[0] > 0 && T.val[0] < vTextures.size();
					bool ifNormals = N.val[0] > 0 && N.val[0] < vNormals.size();

					if (!ifTextures && !ifNormals) {
						add(std::make_shared<CPrimTriangle>(pShader,*this ,vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]]));
						if (i == 4)
							add(std::make_shared<CPrimTriangle>(pShader,*this, vVertexes[V.val[0]], vVertexes[V.val[2]], vVertexes[V.val[3]]));
					} else if (!ifTextures) {
						add(std::make_shared<CPrimTriangle>(pShader,*this,  vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]],
																	  Vec2f::all(0), Vec2f::all(0), Vec2f::all(0),
																	  vNormals[N.val[0]], vNormals[N.val[1]], vNormals[N.val[2]]));
					} else {
						add(std::make_shared<CPrimTriangle>(pShader,*this ,vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]],
																	 vTextures[T.val[0]], vTextures[T.val[1]], vTextures[T.val[2]],
																	 vNormals[N.val[0]], vNormals[N.val[1]], vNormals[N.val[2]]));

						if (i == 4)
							add(std::make_shared<CPrimTriangle>(pShader,*this ,vVertexes[V.val[0]], vVertexes[V.val[2]], vVertexes[V.val[3]],
																		 vTextures[T.val[0]], vTextures[T.val[2]], vTextures[T.val[3]],
																		 vNormals[N.val[0]], vNormals[N.val[2]], vNormals[N.val[3]]));
					}
	
				}
				else if (key == "#" || key == "") {}
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

