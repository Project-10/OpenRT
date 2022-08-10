// Solid Quad class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"

namespace rt {
	// ================================ Quad Solid Class ================================
	/**
	 * @brief Quadrilateral Solid class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CSolidQuad : public CSolid {
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the solid
		 * @param origin The center of the quadrilateral
		 * @param normal The normal of the quadrilateral
		 * @param right The right vector of the quadrilateral
		 * @param r The size of the quadrilateral
		 */
		DllExport CSolidQuad(const ptr_shader_t pShader, const Vec3f& origin = Vec3f::all(0), const Vec3f& normal = Vec3f(0, 1, 0), const Vec3f& right = Vec3f(1, 0, 0), float r = 1);
		/**
		 * @brief Constructor for building solids
		 * @param pShader Pointer to the shader to be applied for the solid
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 * @param d Position of the forth vertex
		 * @param ta Texture coordinate for the first vertex
		 * @param tb Texture coordinate for the second vertex
		 * @param tc Texture coordinate for the third vertex
		 * @param td Texture coordinate for the fourth vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 * @param nd Normal at vertex d
		 */
		DllExport CSolidQuad(const ptr_shader_t pShader,  CSolid* solid,
			const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& d, 
			const Vec2f& ta = Vec2f(0, 0), const Vec2f& tb = Vec2f(1, 0), const Vec2f& tc = Vec2f(1, 1), const Vec2f& td = Vec2f(0, 1), 
			std::optional<Vec3f> na = std::nullopt, std::optional<Vec3f> nb = std::nullopt, std::optional<Vec3f> nc = std::nullopt, std::optional<Vec3f> nd = std::nullopt);
		DllExport virtual ~CSolidQuad(void) = default;
          DllExport virtual bool                                    isSolid(void) const override{return true;}
     
     private:
          CSolid* m_solid;
	};
}
