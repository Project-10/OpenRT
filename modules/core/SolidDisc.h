// Solid Disc class interface
// Written by Dr. Sergey G. Kosov in 2025 for Project X
#pragma once

#include "Solid.h"

namespace rt {
	// ================================ Quad Solid Class ================================
	/**
	 * @brief The Disc Solid class
	 * @ingroup moduleSolid
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CSolidDisc : public CSolid {
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the solid
		 * @param origin The center pointof the disc
		 * @param normal Normal to the disc
		 * @param radius Radius of the disc
		 * @param innerRadius The disc can also be generalized to an annulus by specifying an inner radius
		 * @param sides The number of sides* 
		 */
		DllExport CSolidDisc(const ptr_shader_t pShader, const Vec3f& origin, const Vec3f& normal, float radius, float innerRadius = 0.0f, size_t sides = 24);
		DllExport virtual ~CSolidDisc(void) = default;
	};
}
