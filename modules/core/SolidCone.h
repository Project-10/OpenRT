// Solid Cone class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "PrimTriangle.h"

namespace rt {
	class CSolidCone : public CSolid {
	public:
		/**
		 * @brief Default constructor
		 */
		DllExport CSolidCone(void) : CSolidCone(std::make_shared<CShaderEyelight>(), Vec3f::all(0), 1, 1) {}
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader
		 * @param org The origin of the cone
		 * @param radius The radius of the cone
		 * @param height The height of the cone
		 * @param height_segments The number of height segments
		 * @param sides The number of sides
		 * @param smooth Flag indicating whether the normals should be smoothed
		 */
		DllExport CSolidCone(const ptr_shader_t pShader, Vec3f org, float radius, float height, size_t height_segments = 1, size_t sides = 24, bool smooth = true ) : CSolid(org)
		{
			const Vec3f top(0, height, 0);				// The top point
			const Vec3f slope(0, radius / height, 0);
			Vec3f dir0(1, 0, 0);						// Initial direction
			Vec3f p0 = org + radius * dir0;				// Initial point
			Vec3f n0 = normalize(dir0 + slope);			// Initial normnal
			Vec3f dir1, p1, n1;							// Next point and normal
			float t0 = 0;								// Initial texture coordinate
			for (size_t s = 0; s < sides; s++) {
				float t1 = static_cast<float>(s + 1) / sides; // Next texture coordinate: [1/sides; 1]
				float alpha = -2 * Pif * t1;
				dir1 = Vec3f(cosf(alpha), 0, sinf(alpha));
				p1 = org + radius * dir1;
				n1 = normalize(dir1 + slope);

				// Sides: quads
				float h0 = 0;							// The initial height
				for (int h = 0; h < height_segments - 1; h++) {
					float h1 = static_cast<float>(h + 1) / height_segments;		// Next height: [1/height_segments; 1]
					if (smooth)
						add(std::make_shared<CSolidQuad>(pShader,
														 p0 + h0 * (top - radius * dir0),
														 p0 + h1 * (top - radius * dir0),
														 p1 + h1 * (top - radius * dir1),
														 p1 + h0 * (top - radius * dir1),
														 Vec2f(t0, 1 - h0), Vec2f(t0, 1 - h1), Vec2f(t1, 1 - h1), Vec2f(t1, 1 - h0),
														 n0, n0, n1, n1));
					else 
						add(std::make_shared<CSolidQuad>(pShader,
														 p0 + h0 * (top - radius * dir0),
														 p0 + h1 * (top - radius * dir0),
														 p1 + h1 * (top - radius * dir1),
														 p1 + h0 * (top - radius * dir1),
														 Vec2f(t0, 1 - h0), Vec2f(t0, 1 - h1), Vec2f(t1, 1 - h1), Vec2f(t1, 1 - h0)));
					h0 = h1;
				}

				// Top Sides: triangles
				if (height >= 0) {
					if (smooth)
						add(std::make_shared<CPrimTriangle>(pShader,
															org + top,
															p1 + h0 * (top - radius * dir1),
															p0 + h0 * (top - radius * dir0),
															Vec2f(0.5f, 0), Vec2f(t1, 1 - h0), Vec2f(t0, 1 - h0),
															normalize(n0 + n1), n1, n0));
					else
						add(std::make_shared<CPrimTriangle>(pShader,
															org + top,
															p1 + h0 * (top - radius * dir1),
															p0 + h0 * (top - radius * dir0),
															Vec2f(0.5f, 0), Vec2f(t1, 1 - h0), Vec2f(t0, 1 - h0)));
				}
				else {
					if (smooth)
						add(std::make_shared<CPrimTriangle>(pShader,
															org + top,
															p0 + h0 * (top - radius * dir0),
															p1 + h0 * (top - radius * dir1),
															Vec2f(0.5f, 0), Vec2f(t0, 1 - h0), Vec2f(t1, 1 - h0),
															normalize(n0 + n1), n0, n1));
					else
						add(std::make_shared<CPrimTriangle>(pShader,
															org + top,
															p0 + h0 * (top - radius * dir0),
															p1 + h0 * (top - radius * dir1),
															Vec2f(0.5f, 0), Vec2f(t0, 1 - h0), Vec2f(t1, 1 - h0)));
				}

				// Cap
				if (height >= 0)	add(std::make_shared<CPrimTriangle>(pShader, org, p1, p0, Vec2f(0.5f, 1), Vec2f(t1, 1), Vec2f(t0, 1)));
				else				add(std::make_shared<CPrimTriangle>(pShader, org, p0, p1, Vec2f(0.5f, 1), Vec2f(t0, 1), Vec2f(t1, 1)));
				
				
				dir0 = dir1;
				p0 = p1;
				n0 = n1;
				t0 = t1;
			}
		}
		DllExport virtual ~CSolidCone(void) = default;
	};
}
