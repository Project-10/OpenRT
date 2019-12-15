// Solid Cylinder class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "PrimTriangleSmooth.h"

namespace rt {
	class CSolidCylinder : public CSolid {
	public:
		DllExport CSolidCylinder(ptr_shader_t pShader = std::make_shared<CShaderEyelight>(), const Vec3f& org = Vec3f::all(0), float radius = 1, float height = 1, size_t sides = 24, bool smooth = true) : CSolid(org)
		{
			const Vec3f h(0, height, 0);
			Vec3f dir(1, 0, 0);
			Vec3f p0 = org + radius * dir;
			Vec3f n0 = dir;
			Vec3f p1, n1;
			float t0 = 0;
			float t1;
			for (int s = 0; s < sides; s++) {
				t1 = static_cast<float>(s + 1) / sides; // [1/sides; 1]
				float alpha = 2 * Pif * t1;
				dir = Vec3f(cosf(alpha), 0, sinf(alpha));
				p1 = org + radius * dir;
				n1 = dir;
				if (smooth) add(std::make_shared<CSolidQuad>(pShader, p0, p0 + h, p1 + h, p1, Vec2f(t0, 1), Vec2f(t0, 0), Vec2f(t1, 0), Vec2f(t1, 1), n0, n0, n1, n1));
				else		add(std::make_shared<CSolidQuad>(pShader, p0, p0 + h, p1 + h, p1, Vec2f(t0, 1), Vec2f(t0, 0), Vec2f(t1, 0), Vec2f(t1, 1)));
				if (height >= 0) {
					add(std::make_shared<CPrimTriangle>(pShader, org, p0, p1, Vec2f(0.5f, 1), Vec2f(t0, 1), Vec2f(t1, 1)));
					add(std::make_shared<CPrimTriangle>(pShader, org + h, p1 + h, p0 + h, Vec2f(0.5f, 0), Vec2f(t1, 0), Vec2f(t0, 0)));
				} 
				else {
					add(std::make_shared<CPrimTriangle>(pShader, org, p1, p0, Vec2f(0.5f, 1), Vec2f(t1, 1), Vec2f(t0, 1)));
					add(std::make_shared<CPrimTriangle>(pShader, org + h, p0 + h, p1 + h, Vec2f(0.5f, 0), Vec2f(t0, 0), Vec2f(t1, 0)));
				}
				p0 = p1;
				n0 = n1;
				t0 = t1;
			}
		}
		DllExport virtual ~CSolidCylinder(void) = default;
	};
}

