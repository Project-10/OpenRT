// Solid Box class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"

namespace rt {
	// ================================ Box Solid Class ================================
	/**
	 * @brief Box Solid class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CSolidBox : public CSolid {
	public:
		/**
		 * @brief Constructor of a cube
		 * @param pShader Pointer to the shader to be applied for the solid
		 * @param origin The center of the box
		 * @param r The size of the cube
		 */
		DllExport CSolidBox(const ptr_shader_t pShader, const Vec3f& origin = Vec3f::all(0), float r = 1);
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the solid
		 * @param origin The center of the box
		 * @param width The width of the box
		 * @param height The height of the box
		 * @param depth The depth of the box
		 */
		DllExport CSolidBox(const ptr_shader_t pShader, const Vec3f& origin, float width, float height, float depth);
		DllExport virtual ~CSolidBox(void) = default;
          DllExport bool                                    isSolid(void) const override{return true;}
        
		
	};
}
