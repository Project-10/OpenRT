// Solid Cylinder class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "PrimTriangleSmooth.h"

namespace rt {
	class CSolidCylinder : public CSolid {
	public:
		DllExport CSolidCylinder(void) : CSolidCylinder(std::make_shared<CShaderEyelight>(), Vec3f::all(0), 1, 1) {}
		DllExport CSolidCylinder(ptr_shader_t pShader, Vec3f org, float radius, float height, size_t sides = 24, bool smooth = true) : CSolid(org)
		{
			Vec3f h(0, height, 0);
			Vec3f dir(1, 0, 0);
			Vec3f p0 = org + radius * dir;
			Vec3f n0 = dir;
			Vec3f p1, n1;
			for (size_t i = 0; i < sides; i++) {
				float alpha = (2.0f * (i + 1) * Pif) / sides;
				dir = Vec3f(cosf(alpha), 0, sinf(alpha));
				p1 = org + radius * dir;
				n1 = dir;
				
				if (height > 0) {
					if (smooth)	add(std::make_shared<CSolidQuad>(pShader, p0, p0 + h, p1 + h, p1, n0, n0, n1, n1));
					else 		add(std::make_shared<CSolidQuad>(pShader, p0, p0 + h, p1 + h, p1));
					add(std::make_shared<CPrimTriangle>(pShader, org + h, p1 + h, p0 + h));
					add(std::make_shared<CPrimTriangle>(pShader, org, p0, p1));
				} else {
					if (smooth)	add(std::make_shared<CSolidQuad>(pShader, p0, p1, p1 + h, p0 + h, n0, n1, n1, n0));
					else		add(std::make_shared<CSolidQuad>(pShader, p0, p1, p1 + h, p0 + h));
					add(std::make_shared<CPrimTriangle>(pShader, org + h, p0 + h, p1 + h));
					add(std::make_shared<CPrimTriangle>(pShader, org, p1, p0));
				}
				p0 = p1;
				n0 = n1;
			}
		}
		DllExport virtual ~CSolidCylinder(void) = default;
	};
}

