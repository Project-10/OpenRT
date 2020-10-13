#include "SolidQuad.h"
#include "PrimTriangle.h"
#include "PrimTriangle.h"

namespace rt {
	// Constructor
	CSolidQuad::CSolidQuad(const ptr_shader_t pShader, const Vec3f& origin, const Vec3f& normal, const Vec3f& dx, float r) : CSolid(origin)
	{
		Vec3f dy = normal.cross(dx);
		
		Vec3f a = origin - r * dx - r * dy;
		Vec3f b = origin + r * dx - r * dy;
		Vec3f c = origin + r * dx + r * dy;
		Vec3f d = origin - r * dx + r * dy;

		Vec2f ta(0, 0);
		Vec2f tb(1, 0);
		Vec2f tc(1, 1);
		Vec2f td(0, 1);

		add(std::make_shared<CPrimTriangle>(pShader, a, b, c, ta, tb, tc));
		add(std::make_shared<CPrimTriangle>(pShader, a, c, d, ta, tc, td));
	}

	// Constructor
	CSolidQuad::CSolidQuad(const ptr_shader_t pShader, 
		const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& d, 
		const Vec2f& ta, const Vec2f& tb, const Vec2f& tc, const Vec2f& td, 
		std::optional<Vec3f> na, std::optional<Vec3f> nb, std::optional<Vec3f> nc, std::optional<Vec3f> nd
	) : CSolid(0.25f * (a + b + c + d))
	{
		add(std::make_shared<CPrimTriangle>(pShader, a, b, c, ta, tb, tc, na, nb, nc));
		add(std::make_shared<CPrimTriangle>(pShader, a, c, d, ta, tc, td, na, nc, nd));
	}
}
