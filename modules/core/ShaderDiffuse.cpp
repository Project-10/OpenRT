#include "ShaderDiffuse.h"
#include "BRDFLambertian.h"
#include "BRDFOrenNayar.h"

// Constructor
rt::CShaderDiffuse::CShaderDiffuse(const CScene& scene, const Vec3f& color, float sigma) : CNewShader(scene, color)
{
	if (sigma < Epsilon) addBSDF(std::make_unique<CBRDFLambertian>());
	else addBSDF(std::make_shared<CBRDFOrenNayar>(sigma));
}
	
// Constructor
rt::CShaderDiffuse::CShaderDiffuse(const CScene& scene, const ptr_texture_t pTexture, float sigma) : CNewShader(scene, pTexture)
{
	if (sigma < Epsilon) addBSDF(std::make_unique<CBRDFLambertian>());
	else addBSDF(std::make_shared<CBRDFOrenNayar>(sigma));
}

//	Vec3f CShaderDiffuse::shade(const Ray& ray) const
//	{
//		Vec3f res(0, 0, 0);
//
//		Vec3f diffuseColor = getDiffuseColor(ray);
//		float opacity = getOpacity(ray);
//
//		Vec3f faceNormal = ray.hit->getNormal(ray);							// face normal
//		Vec3f shadingNormal = ray.hit->getShadingNormal(ray);				// shading normal
//
//		auto du = getBump(ray);
//		if (du) {
//			auto  dp = ray.hit->dp(ray.hitPoint());
//			Vec3f dpdu = dp.first;
//			Vec3f dpdv = dp.second;
//
//			shadingNormal += getBumpAmount() * (du.value().first * dpdv.cross(shadingNormal) - du.value().second * dpdu.cross(shadingNormal));
//			shadingNormal = normalize(shadingNormal);
//		}
//
//		bool inside = false;
//		if (faceNormal.dot(ray.dir) > 0) {
//			shadingNormal = -shadingNormal;								// turn shading normal to front
//			inside = true;
//		}
//
//#ifdef DEBUG_MODE
//		res = inside ? RGB(255, 0, 0) : RGB(0, 0, 255);
//#endif
//		// ------ opacity ------
//		if (opacity < 1) {
//			Ray R(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
//			res += (1.0f - opacity) * R.reTrace(getScene());
//		}
//
//		// Gathering incoming light (incident radiance)
//		Vec3f outgoing_radiance = eval_IR_LS(ray, [this](const Ray& ray, const Vec3f& w_i) {
//			const Vec3f w_o = -ray.dir;							// direction to camera
//			const Vec3f n = ray.hit->getShadingNormal(ray);		// shading normal
//
//			// transfer to the local coordinate system (LSC)
//			Vec3f t = tangent(n);
//			Vec3f s = n.cross(t);
//			Matx33f M(
//				t[0], t[1], t[2],
//				s[0], s[1], s[2],
//				n[0], n[1], n[2]
//			);
//
//			// Transform the w_x vectors from WCS to LCS
//			Vec3f wi = M * w_i;
//			Vec3f wo = M * w_o;
//
//			return m_pBxDF->f(wo, wi) * getDiffuseColor(ray);
//		});
//		
//		res += opacity * outgoing_radiance;
//
//		return res;
//	}
