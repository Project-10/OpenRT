#include "SolidDisc.h"
#include "SolidQuad.h"
#include "PrimTriangle.h"
#include "mathutils.h"

rt::CSolidDisc::CSolidDisc(const ptr_shader_t pShader, const Vec3f& origin, const Vec3f& normal, float radius, float innerRadius, size_t sides) : CSolid(origin)
{
	const float dPhi = 2 * Pif / sides;	// delta phi - the angle step
	const Vec3f axis1 = tangent(normal);		// Choose an arbitrary vector for one axis
	const Vec3f axis2 = normal.cross(axis1);
	
	Vec3f P0 = origin + radius * axis1;			// Initial outter point: phi = 0
	Vec3f p0 = origin + innerRadius * axis1;	// Initial inner point: phi = 0
	float T0 = 0;								// Initial texture coordinate
	for (size_t s = 1; s <= sides; s++) {
		float phi	= -(s * dPhi);
		Vec3f P1	= origin + radius * (axis1 * cosf(phi) + axis2 * sinf(phi));
		float T1	= static_cast<float>(s) / sides;

		if (innerRadius < Epsilon) {
			add(std::make_shared<CPrimTriangle>(pShader, origin, origin, P1, P0, Vec2f((T0 + T1) / 2, 1), Vec2f(T1, 0), Vec2f(T0, 0)));
		} else {
			Vec3f p1 = origin + innerRadius * (axis1 * cosf(phi) + axis2 * sinf(phi));
			add(CSolidQuad(pShader, origin, p0, p1, P1, P0, Vec2f(T0, 1), Vec2f(T1, 1), Vec2f(T1, 0), Vec2f(T0, 0)));
			p0 = p1;
		}

		P0 = P1;
		T0 = T1;
	}
}
