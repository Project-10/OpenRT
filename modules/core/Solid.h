// Base solids class
// Written by Dr. Sergey G. Kosov in 2019 for Project X 
#pragma once

#include "IPrim.h"

namespace rt {
	class CSolid {
	public:
		DllExport CSolid(void) = default;
		/**
		 * @brief Constructor
		 * @details Loads the primitives from an .obj file and adds them to the scene
		 * @param pShader Pointer to the shader to be use with the parsed object
		 * @param fileName The full path to the .obj file
		 */
		DllExport CSolid(ptr_shader_t pShader, const std::string& fileName);
		DllExport CSolid(const CSolid&) = delete;
		DllExport virtual ~CSolid(void) = default;
		DllExport CSolid& operator=(const CSolid&) = delete;

		DllExport const std::vector<ptr_prim_t>& getPrims(void) const { return m_vpPrims; }

		
	protected:
		DllExport void add(const ptr_prim_t pPrim) { m_vpPrims.push_back(pPrim); }
		DllExport void add(const std::shared_ptr<CSolid> pSolid) {
			for (const auto& pPrim : pSolid->getPrims())
				m_vpPrims.push_back(pPrim);
		}


	private:
		Vec3f					m_pivot;		///<  Pivot point
		std::vector<ptr_prim_t>	m_vpPrims;
	};
}
