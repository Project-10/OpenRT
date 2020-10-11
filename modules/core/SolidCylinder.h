// Solid Cylinder class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "PrimTriangle.h"

namespace rt {
	class CSolidCylinder : public CSolid {
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader
		 * @param org The origin of the cylinder
		 * @param radius The radius of the cylinder
		 * @param height The height of the cylinder
		 * @param height_segments The number of height segments
		 * @param sides The number of sides
		 * @param smooth Flag indicating whether the normals should be smoothed
		 */
		DllExport CSolidCylinder(ptr_shader_t pShader = std::make_shared<CShaderEyelight>(), const Vec3f& org = Vec3f::all(0), float radius = 1, float height = 1, size_t height_segments = 1, size_t sides = 24, bool smooth = true) : CSolid(org)
		{
			const Vec3f top(0, height, 0);		// The top point
			Vec3f dir(1, 0, 0);					// Initial direction
			Vec3f p0 = org + radius * dir;		// Initial point
			Vec3f n0 = dir;						// Initial normal
			Vec3f p1, n1;						// Next point and normal
			float t0 = 0;						// Initial texture coordinate
			for (int s = 0; s < sides; s++) {
				float t1 = static_cast<float>(s + 1) / sides; // Next texture coordinate: [1/sides; 1]
				float alpha = -2 * Pif * t1;
				dir = Vec3f(cosf(alpha), 0, sinf(alpha));
				p1 = org + radius * dir;
				n1 = dir;
				
				// Sides
				float h0 = 0;					// Initial height
				for (int h = 0; h < height_segments; h++) {
					float h1 = static_cast<float>(h + 1) / height_segments;	// Next height: [1/height_segments; 1]
					if (smooth)	add(std::make_shared<CSolidQuad>(pShader, p0 + h0 * top, p0 + h1 * top, p1 + h1 * top, p1 + h0 * top, Vec2f(t0, 1 - h0), Vec2f(t0, 1 - h1), Vec2f(t1, 1 - h1), Vec2f(t1, 1 - h0), n0, n0, n1, n1));
					else		add(std::make_shared<CSolidQuad>(pShader, p0 + h0 * top, p0 + h1 * top, p1 + h1 * top, p1 + h0 * top, Vec2f(t0, 1 - h0), Vec2f(t0, 1 - h1), Vec2f(t1, 1 - h1), Vec2f(t1, 1 - h0)));
					h0 = h1;
				} // h
				
				// Caps
				if (height >= 0) {
					add(std::make_shared<CPrimTriangle>(pShader, org, p0, p1, Vec2f(0.5f, 1), Vec2f(t0, 1), Vec2f(t1, 1)));
					add(std::make_shared<CPrimTriangle>(pShader, org + top, p1 + top, p0 + top, Vec2f(0.5f, 0), Vec2f(t1, 0), Vec2f(t0, 0)));
				} 
				else {
					add(std::make_shared<CPrimTriangle>(pShader, org, p1, p0, Vec2f(0.5f, 1), Vec2f(t1, 1), Vec2f(t0, 1)));
					add(std::make_shared<CPrimTriangle>(pShader, org + top, p0 + top, p1 + top, Vec2f(0.5f, 0), Vec2f(t0, 0), Vec2f(t1, 0)));
				}
				p0 = p1;
				n0 = n1;
				t0 = t1;
			}
		}
		DllExport virtual ~CSolidCylinder(void) = default;
	};
}

