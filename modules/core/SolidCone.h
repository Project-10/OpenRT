// Solid Cone class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "PrimTriangleSmooth.h"

namespace rt {
	class CSolidCone : public CSolid {
	public:
		DllExport CSolidCone(void) : CSolidCone(std::make_shared<CShaderEyelight>(), Vec3f::all(0), 1, 1) {}
		DllExport CSolidCone(ptr_shader_t pShader, Vec3f org, float radius, float height, size_t sides = 24, bool smooth = true ) : CSolid(org)
		{
			Vec3f h(0, radius / height, 0);
			Vec3f dir(1, 0, 0);
			Vec3f p0 = org + radius * dir;
			Vec3f n0 = normalize(dir + h);
			Vec3f p1, n1;
			for (size_t i = 0; i < sides; i++) {
				float alpha = (2.0f * (i + 1) * Pif) / sides;
				dir = Vec3f(cosf(alpha), 0, sinf(alpha));
				p1 = org + radius * dir;
				n1 = normalize(dir + h);

				if (height > 0) {
					if (smooth) add(std::make_shared<CPrimTriangleSmooth>(pShader, org + Vec3f(0, height, 0), p1, p0, normalize(n0 + n1), n1, n0));
					else add(std::make_shared<CPrimTriangle>(pShader, org + Vec3f(0, height, 0), p1, p0));
					add(std::make_shared<CPrimTriangle>(pShader, org, p0, p1));
				} else {
					if (smooth) add(std::make_shared<CPrimTriangleSmooth>(pShader, org + Vec3f(0, height, 0), p0, p1, normalize(n0 + n1), n0, n1));
					else add(std::make_shared<CPrimTriangle>(pShader, org + Vec3f(0, height, 0), p0, p1));
					
					add(std::make_shared<CPrimTriangle>(pShader, org, p1, p0));
				}
				p0 = p1;
				n0 = n1;
			}
		}
		DllExport virtual ~CSolidCone(void) = default;
	};
}
