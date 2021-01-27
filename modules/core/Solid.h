// Base solids class
// Written by Dr. Sergey G. Kosov in 2019 for Project X 
#pragma once

#include "IPrim.h"

namespace rt {
	// ================================ Solid Base Class ================================
	/**
	 * @brief Base Solid class
	 * @details This class represent objects which consist of multiple primitives (obkects derived from IPrim class). 
	 * The main purpose of the class is to allow for convinient transformations of the solid objects
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CSolid {
	public:
		/**
		 * @brief Constructor
		 * @param pPrim Pointer to the primitive
		 * @todo Init the pivot point
		 */
		DllExport CSolid(const ptr_prim_t pPrim) : m_pivot(0, 0, 0), m_vpPrims({pPrim}) {}
		/**
		 * @brief Constructor
		 * @details Loads the primitives from an .obj file and adds them to the scene
		 * @param pShader Pointer to the shader to be use with the parsed object
		 * @param fileName The full path to the .obj file
		 */
		DllExport CSolid(const ptr_shader_t pShader, const std::string& fileName);
		DllExport CSolid(const CSolid&) = default;
		DllExport virtual ~CSolid(void) = default;
		
		DllExport CSolid& operator=(const CSolid&) = delete;
//      DllExport CSolid& operator=(ptr_prim_t);
		
		/**
		 * @brief Applies affine transformation matrix \b t to the solid.
		 * @param t The affine transformatio matrix
		 */
		DllExport void 								transform(const Mat& t);
		/**
		 * @brief Returns the primitives which build the solid
		 * @return The vector with pointers to the primitives which build the solid
		 */
		DllExport const std::vector<ptr_prim_t>&	getPrims(void) const { return m_vpPrims; }
		/**
		 * @brief Sets new pivot point for affine transformations
		 * @param pivot The new pivot point 
		 */
		DllExport void								setPivot(const Vec3f& pivot) { m_pivot = pivot; }
		/**
		 * @brief Returns the solid's pivot point 
		 * @return The solid's pivot point
		 */
		DllExport Vec3f 							getPivot(void) const { return m_pivot; }
		
	protected:
		/**
		 * @brief Constructor
		 * @param org The origin of the object. This point may be the virtual center of mass and will be used as a pivot point for object transformations.
		 */
		CSolid(Vec3f org) : m_pivot(org) {}
		/**
		 * @brief Adds a new primitive to the solid
		 * @param pPrim Pointer to the primitive
		 */
		void add(const ptr_prim_t pPrim) { m_vpPrims.push_back(pPrim); }
		/**
		 * @brief Add a new solid to the solid
		 * @param pSolid The pointer to the solid
		 */
		void add(const ptr_solid_t pSolid) {
			for (const auto& pPrim : pSolid->getPrims())
				m_vpPrims.push_back(pPrim);
		}


	private:
		Vec3f					m_pivot;		///< The pivot point (origin)
		std::vector<ptr_prim_t>	m_vpPrims;		///< Container for the primitives which build the solid
	};
}
