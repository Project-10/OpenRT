// Solid Quad class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "PrimTriangle.h"

namespace rt {
	class CSolidQuad : public CSolid {
	public:
		DllExport CSolidQuad(ptr_shader_t pShader, Vec3f a, Vec3f b, Vec3f c, Vec3f d) {
			add(std::make_shared<CPrimTriangle>(pShader, a, b, c));
			add(std::make_shared<CPrimTriangle>(pShader, a, c, d));
		}
		DllExport virtual ~CSolidQuad(void) = default;
	};
}
