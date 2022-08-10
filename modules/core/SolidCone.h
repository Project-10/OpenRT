// Solid Cone class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"

namespace rt {
	// ================================ Cone Solid Class ================================
	/**
	 * @brief Cone Solid class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CSolidCone : public CSolid {
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader
		 * @param origin The origin of the cone
		 * @param radius The radius of the cone
		 * @param height The height of the cone
		 * @param height_segments The number of height segments
		 * @param sides The number of sides
		 * @param smooth Flag indicating whether the normals should be smoothed
		 */
		DllExport CSolidCone(ptr_shader_t pShader, const Vec3f& origin = Vec3f::all(0), float radius = 1, float height = 1, size_t height_segments = 1, size_t sides = 24, bool smooth = true);
		DllExport virtual ~CSolidCone(void) = default;
          DllExport bool                                    isSolid(void) const override{return true;}        
	};
}
