#include "ShaderHemisphere.h"
#include "Scene.h"
#include "Ray.h"


//Vec3f rt::CShaderHemisphere::shade(const Ray& ray) const
//{
//	Vec3f n = ray.hit->getShadingNormal(ray);
//	Vec3f p = ray.hitPoint(n);
//
//	return InvPif * getDiffuseColor(ray).mul(eval_IR_LS(p, n));
//}

Vec3f rt::CShaderHemisphere::shade(const Ray& ray) const
{
	const Vec3f diffuseColor = getDiffuseColor(ray);
	const Vec3f n = ray.hit->getShadingNormal(ray);
	const Vec3f p = ray.hitPoint(n);

	Vec3f L_direct = eval_IR_LS(p, n);
	Vec3f L_indirect = (ray.counter < 5) ? eval_IR_all(p, n, ray.counter) : Vec3f::all(0);

	//// Убираем двойной учёт прямого света
	//L_indirect = Vec3f(
	//	std::max(L_indirect[0] - L_direct[0], 0.0f),
	//	std::max(L_indirect[1] - L_direct[1], 0.0f),
	//	std::max(L_indirect[2] - L_direct[2], 0.0f)
	//);

	Vec3f res = L_direct + 0.3f * L_indirect;

	return InvPif * diffuseColor.mul(res);
}
