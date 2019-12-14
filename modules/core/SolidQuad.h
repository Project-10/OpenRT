// Solid Quad class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"

namespace rt {
	class CSolidQuad : public CSolid {
	public:
		DllExport CSolidQuad(ptr_shader_t pShader, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& d, const Vec2f& ta = Vec2f::all(0), const Vec2f& tb = Vec2f::all(0), const Vec2f& tc = Vec2f::all(0), const Vec2f& td = Vec2f::all(0))
			: CSolid(0.25f * (a + b + c + d))
		{
			add(std::make_shared<CPrimTriangle>(pShader, a, b, c, ta, tb, tc));
			add(std::make_shared<CPrimTriangle>(pShader, a, c, d, ta, tc, td));
		}
		DllExport CSolidQuad(ptr_shader_t pShader, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& d, const Vec3f& na, const Vec3f& nb, const Vec3f& nc, const Vec3f& nd)
			: CSolid(0.25f * (a + b + c + d))
		{
			add(std::make_shared<CPrimTriangleSmooth>(pShader, a, b, c, na, nb, nc));
			add(std::make_shared<CPrimTriangleSmooth>(pShader, a, c, d, na, nc, nd));
		}
		DllExport CSolidQuad(ptr_shader_t pShader, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& d, const Vec2f& ta, const Vec2f& tb, const Vec2f& tc, const Vec2f& td, const Vec3f& na, const Vec3f& nb, const Vec3f& nc, const Vec3f& nd)
			: CSolid(0.25f * (a + b + c + d))
		{
			add(std::make_shared<CPrimTriangleSmooth>(pShader, a, b, c, ta, tb, tc, na, nb, nc));
			add(std::make_shared<CPrimTriangleSmooth>(pShader, a, c, d, ta, tc, td, na, nc, nd));
		}
		DllExport virtual ~CSolidQuad(void) = default;
	};
}
