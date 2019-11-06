#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"

#include <fstream> 

namespace rt {
	void CScene::parseOBJ(const std::string& fileName)
	{
		std::ifstream file(fileName);

		if (file.is_open()) {
			std::cout << "Parsing OBJFile : " << fileName << std::endl;

			std::shared_ptr<IShader> pShader = std::make_shared<CShaderPhong>(*this, RGB(1, 1, 1), 0.5f, 0.5f, 0.5f, 40);
			std::vector<Vec3f> vVertexes;
			
			std::string line;

			for (;;) {
				if (!getline(file, line)) break;
				std::stringstream ss(line);
				getline(ss, line, ' ');
				if (line == "v") {
					Vec3f v;
					for (int i = 0; i < 3; i++) ss >> v.val[i];
					// std::cout << "Vertex: " << v << std::endl;
					vVertexes.emplace_back(25 * v);
				}
				else if (line == "f") {
					Vec3i f;
					for (int i = 0; i < 3; i++) ss >> f.val[i];
					// std::cout << "Face: " << f << std::endl;
					add(std::make_shared<CPrimTriangle>(pShader, vVertexes[f.val[0] - 1], vVertexes[f.val[1] - 1], vVertexes[f.val[2] - 1]));
				}
				else {
					std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
				}
			}

			file.close();
			std::cout << "Finished Parsing" << std::endl;
		} else
			std::cout << "ERROR: Can't open OBJFile" << std::endl;
	}
}
