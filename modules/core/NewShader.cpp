#include "NewShader.h"
#include "Ray.h"
#include "Scene.h"
#include "IBxDF.h"
#include "mathutils.h"
#include "random.h"

namespace {
	Matx33f World2LocalMatix(const Vec3f& n) {
		Vec3f t = tangent(n);
		Vec3f s = n.cross(t);
		return Matx33f(
			s[0], s[1], s[2],
			t[0], t[1], t[2],
			n[0], n[1], n[2]
		);
	}
}

Vec3f rt::CNewShader::shade(const Ray& ray) const
{
	const Vec3f		woW = -ray.dir;								// view direction to camera in WCS
	Vec3f			n	= ray.hit->getShadingNormal(ray);		// shading normal in WLC
	
	// Bump Mapping
	auto du = getBump(ray);
	if (du) {
		auto  dp = ray.hit->dp(ray.hitPoint());
		Vec3f dpdu = dp.first;
		Vec3f dpdv = dp.second;

		n += getBumpAmount() * (du.value().first * dpdv.cross(n) - du.value().second * dpdu.cross(n));
		n = normalize(n);
	}
	
	const Vec3f		p	= ray.hitPoint(n);						// The hit point to be shaded
	const Matx33f	M	= World2LocalMatix(n);					// WCS to LCS matrix
	const Vec3f		wo	= M * woW;								// view direction to camera in LCS

	// TODO: If there are textures, the same calculation of the texture coordinates are done 4 times here
	Vec3f ambientColor	= getAmbientColor(ray);
	Vec3f diffuseColor	= getDiffuseColor(ray);
	float ks			= getSpecularLevel(ray);
	float opacity		= getOpacity(ray);

	// TODO: Debug Mode
	// TODO: Opacity

	Vec3f res(0, 0, 0);
	
	// Ambient light is not a part of integration
	res += getScene().getAmbientColor().mul(ambientColor);

	// Diffuse light: calculate the Incident Radiance
	Vec3f ir = eval_IR_LS(p, n, [this, M, wo, ks](const Vec3f& wiW) {
		
		Vec3f wi = M * wiW;			// Transform the wiW vector from WCS to LCS
	
		float res = 0;
		for (const auto& bxdfPair : this->m_vpBxDFs) {
			float k = bxdfPair.second->MatchesFlags(BxDFType::specular) ? ks : 1.0f;
			res += k * bxdfPair.first * bxdfPair.second->f(wo, wi);
		}
		return  res;

	});
	res += ir.mul(diffuseColor);
	
	// Re-Tracing components
	for (const auto& bxdfPair : this->m_vpBxDFs) {
		thread_local Vec3f wi;
		float weight = bxdfPair.first * bxdfPair.second->Sample_f(wo, wi);

		Ray newRay(p, M.t() * wi, ray.ndc, ray.counter);
		res += weight * newRay.reTrace(getScene());
	}

	return res;
}

void rt::CNewShader::add(const ptr_BxDF_t pBxDF, float scale)
{
	m_vpBxDFs.push_back(std::make_pair(scale, pBxDF));
}


// TODO: Rework getScene() 
// TODO: Test with sky light

Vec3f rt::CNewShader::eval_IR_LS(const Vec3f& point, const Vec3f& normal, brdf_function brdf) const {
	Vec3f res(0, 0, 0);

	Ray shadowRay(point);
	for (auto& pLight : getScene().getLights()) {
		Vec3f L = Vec3f::all(0);
		const size_t nSamples = pLight->getNumSamples();
		for (size_t s = 0; s < nSamples; s++) {
			//shadowRay.hit = ray.hit;	// Needed for the skylight
			auto radiance = pLight->illuminate(shadowRay);
			if (radiance) {
				// Check shadow (light sourse is occluded)
				float k_occlusion = pLight->shadow() ? getScene().evalOcclusion(shadowRay) : 1.0f;
				if (k_occlusion < Epsilon) continue;

				float cosLightNormal = shadowRay.dir.dot(normal);
				if (cosLightNormal > 0)
					L += cosLightNormal * k_occlusion * brdf(shadowRay.dir) * radiance.value();
			}
		}
		res += (1.0f / nSamples) * L;
	}
	return res;
}
