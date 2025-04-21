#include "ShaderHemisphere.h"
#include "Scene.h"
#include "Ray.h"


float rt::CShaderHemisphere::brdf(const Vec3f& wo, const Vec3f& wi) const
{
	constexpr float kd = 1.0f;
	constexpr float ks = 0.0f;
	constexpr float ke = 40.0f;

	float res = 0;
	
	//if (kd > 0) {	// diffuse component
	//	const Vec3f diffuseColor = getDiffuseColor(ray);
	//	const float opacity = getOpacity(ray);
	//
	//	res += kd * opacity * InvPif;						// TODO: Why opacity here? It need to shoot one more ray ?
	//}

	//if (ks > 0) {	// specular component
	//	// TODO: I am not happy that we need to calculate this 2 times
	//	Vec3f n = ray.hit->getShadingNormal(ray);				// shading normal
	//	float cosLightNormal  = dir_light.dot(n);				// cos Aplha
	//
	//	Ray reflected = ray.reflected(n);						// reflection of the ray from camera 
	//	float cosLightReflect = dir_light.dot(reflected.dir);	// cos Beta

	//	res += ks * (ke + 2) / (2 * Pif) * powf(cosLightReflect, ke) / cosLightNormal;
	//}

	return res;
}


Vec3f rt::CShaderHemisphere::shade(const Ray& ray) const
{
	return getDiffuseColor(ray).mul(eval_IR_LS(ray));
	//return eval_IR_LS(ray, [this](const Vec3f& woW, const Vec3f& wiW) { return this->brdf(woW, wiW); });
}

//Vec3f rt::CShaderHemisphere::shade(const Ray& ray) const
//{
//	const Vec3f diffuseColor = getDiffuseColor(ray);
//
//	Vec3f L_direct = eval_IR_LS(ray);
//	Vec3f L_indirect = (ray.counter < 5) ? eval_IR_all(ray) : Vec3f::all(0);
//
//	//// Убираем двойной учёт прямого света
//	//L_indirect = Vec3f(
//	//	std::max(L_indirect[0] - L_direct[0], 0.0f),
//	//	std::max(L_indirect[1] - L_direct[1], 0.0f),
//	//	std::max(L_indirect[2] - L_direct[2], 0.0f)
//	//);
//
//	Vec3f res = L_direct + 0.3f * L_indirect;
//
//	return diffuseColor.mul(res);
//}
