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
			const Vec3f h(0, height, 0);
			const Vec3f slope(0, radius / height, 0);
			Vec3f dir(1, 0, 0);
			Vec3f p0 = org + radius * dir;
			Vec3f n0 = normalize(dir + slope);
			Vec3f p1, n1;
			float t0 = 0;
			float t1;
			for (size_t s = 0; s < sides; s++) {
				t1 = static_cast<float>(s + 1) / sides; // [1/sides; 1]
				float alpha = 2 * Pif * t1;
				dir = Vec3f(cosf(alpha), 0, sinf(alpha));
				p1 = org + radius * dir;
				n1 = normalize(dir + slope);

				if (height >= 0) {
					if (smooth) add(std::make_shared<CPrimTriangleSmooth>(pShader, org + h, p1, p0, Vec2f(0.5f, 0), Vec2f(t1, 1), Vec2f(t0, 1), normalize(n0 + n1), n1, n0));
					else		add(std::make_shared<CPrimTriangle>(pShader, org + h, p1, p0, Vec2f(0.5f, 0), Vec2f(t1, 1), Vec2f(t0, 1)));
					add(std::make_shared<CPrimTriangle>(pShader, org, p0, p1, Vec2f(0.5f, 1), Vec2f(t0, 1), Vec2f(t1, 1)));
				}
				else {
					if (smooth) add(std::make_shared<CPrimTriangleSmooth>(pShader, org + h, p0, p1, Vec2f(0.5f, 0), Vec2f(t0, 1), Vec2f(t1, 1), normalize(n0 + n1), n0, n1));
					else		add(std::make_shared<CPrimTriangle>(pShader, org + h, p0, p1, Vec2f(0.5f, 0), Vec2f(t0, 1), Vec2f(t1, 1)));
					add(std::make_shared<CPrimTriangle>(pShader, org, p1, p0, Vec2f(0.5f, 1), Vec2f(t1, 1), Vec2f(t0, 1)));
				}


/*				if (height > 0) {
					if (smooth) add(std::make_shared<CPrimTriangleSmooth>(pShader, org + Vec3f(0, height, 0), p1, p0, normalize(n0 + n1), n1, n0));
					else add(std::make_shared<CPrimTriangle>(pShader, org + Vec3f(0, height, 0), p1, p0));
					add(std::make_shared<CPrimTriangle>(pShader, org, p0, p1, Vec2f(0.5f, 1), Vec2f(t0, 1), Vec2f(t1, 1)));
				} else {
					if (smooth) add(std::make_shared<CPrimTriangleSmooth>(pShader, org + Vec3f(0, height, 0), p0, p1, normalize(n0 + n1), n0, n1));
					else add(std::make_shared<CPrimTriangle>(pShader, org + Vec3f(0, height, 0), p0, p1));
					add(std::make_shared<CPrimTriangle>(pShader, org, p1, p0, Vec2f(0.5f, 1), Vec2f(t1, 1), Vec2f(t0, 1)));
				}*/



				p0 = p1;
				n0 = n1;
				t0 = t1;
			}
		}
		DllExport virtual ~CSolidCone(void) = default;
	};
}
