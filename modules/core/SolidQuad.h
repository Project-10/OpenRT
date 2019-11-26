// Solid Quad class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"

namespace rt {
	class CSolidQuad : public CSolid {
	public:
		DllExport CSolidQuad(ptr_shader_t pShader, Vec3f a, Vec3f b, Vec3f c, Vec3f d)
			: CSolid(0.25f * (a + b + c + d))
		{
			add(std::make_shared<CPrimTriangle>(pShader, a, b, c));
			add(std::make_shared<CPrimTriangle>(pShader, a, c, d));
		}
		DllExport CSolidQuad(ptr_shader_t pShader, Vec3f a, Vec3f b, Vec3f c, Vec3f d, Vec3f na, Vec3f nb, Vec3f nc, Vec3f nd)
			: CSolid(0.25f * (a + b + c + d))
		{
			add(std::make_shared<CPrimTriangleSmooth>(pShader, a, b, c, na, nb, nc));
			add(std::make_shared<CPrimTriangleSmooth>(pShader, a, c, d, na, nc, nd));
		}
		DllExport virtual ~CSolidQuad(void) = default;
	};
}
