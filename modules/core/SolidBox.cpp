#include "SolidBox.h"
#include "SolidQuad.h"

namespace rt {
	// Constructor
	CSolidBox::CSolidBox(const ptr_shader_t pShader, const Vec3f& origin, float r) 
		: CSolidBox(pShader, origin, r * 2, r * 2, r * 2)
	{}
	
	// Contructor
	CSolidBox::CSolidBox(const ptr_shader_t pShader, const Vec3f& origin, float width, float height, float depth) : CSolid(origin)
	{
		width /= 2; height /= 2; depth /= 2;

		add(CSolidQuad(pShader, origin + Vec3f(width, -height, -depth), origin + Vec3f(width, height, -depth), origin + Vec3f(width, height, depth), origin + Vec3f(width, -height, depth), Vec2f(1, 1), Vec2f(1, 0), Vec2f(0, 0), Vec2f(0, 1)));
		add(CSolidQuad(pShader, origin + Vec3f(-width, -height, -depth), origin + Vec3f(-width, -height, depth), origin + Vec3f(-width, height, depth), origin + Vec3f(-width, height, -depth), Vec2f(0, 1), Vec2f(1, 1), Vec2f(1, 0), Vec2f(0, 0)));

		add(CSolidQuad(pShader, origin + Vec3f(-width, height, -depth), origin + Vec3f(-width, height, depth), origin + Vec3f(width, height, depth), origin + Vec3f(width, height, -depth), Vec2f(0, 0), Vec2f(0, 1), Vec2f(1, 1), Vec2f(1, 0)));
		add(CSolidQuad(pShader, origin + Vec3f(-width, -height, -depth), origin + Vec3f(width, -height, -depth), origin + Vec3f(width, -height, depth), origin + Vec3f(-width, -height, depth), Vec2f(1, 0), Vec2f(0, 0), Vec2f(0, 1), Vec2f(1, 1)));

		add(CSolidQuad(pShader, origin + Vec3f(-width, -height, depth), origin + Vec3f(width, -height, depth), origin + Vec3f(width, height, depth), origin + Vec3f(-width, height, depth), Vec2f(0, 1), Vec2f(1, 1), Vec2f(1, 0), Vec2f(0, 0)));
		add(CSolidQuad(pShader, origin + Vec3f(-width, -height, -depth), origin + Vec3f(-width, height, -depth), origin + Vec3f(width, height, -depth), origin + Vec3f(width, -height, -depth), Vec2f(1, 1), Vec2f(1, 0), Vec2f(0, 0), Vec2f(0, 1)));
	}
}
