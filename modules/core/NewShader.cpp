#include "NewShader.h"
#include "Ray.h"
#include "Scene.h"
#include "IBxDF.h"
#include "mathutils.h"
#include "random.h"

namespace {
	Matx33f World2LocalMatix(const Vec3f& n, const Vec3f& aux = Vec3f(1.0f, .0f, .0f)) {
		Vec3f t = normalize(tangent(n, aux));
		Vec3f s = t.cross(n);

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
	
	Vec3f faceNormal = ray.hit->getNormal(ray);					// face normal
	Vec3f n = ray.hit->getShadingNormal(ray);					// shading normal in WLC
	bool inside = false;
	if (faceNormal.dot(ray.dir) > 0) {
		//n = -n;													// turn normal to front
		inside = true;
	}
	
	// Bump Mapping
	auto du = getBump(ray);
	if (du) {
		auto  dp = ray.hit->dp(ray.hitPoint());
		Vec3f dpdu = dp.first;
		Vec3f dpdv = dp.second;

		n += getBumpAmount() * (du.value().first * dpdv.cross(n) - du.value().second * dpdu.cross(n));
		n = normalize(n);
	}
	
	const Vec3f		p	= ray.hitPoint(n);						// The hit point to be shaded (the positive hitpoint)
	const Matx33f	M	= World2LocalMatix(n, -woW);			// WCS to LCS matrix
	const Vec3f		wo	= M * woW;								// view direction to camera in LCS

	// TODO: If there are textures, the same calculation of the texture coordinates are done 4 times here
	Vec3f ambientColor	= getAmbientColor(ray);
	Vec3f diffuseColor	= getDiffuseColor(ray);
	Vec3f specularColor	= getSpecularColor(ray);
	float opacity		= getOpacity(ray);

	Vec3f res(0, 0, 0);

	// ------ ambient ------
	res += getScene().getAmbientColor().mul(ambientColor);

	// Diffuse light: calculate the Incident Radiance
	if ((m_type & (BxDFType::diffuse | BxDFType::specular)) != BxDFType::unset) {
		res += eval_IR_LS(p, n, [this, M, wo, diffuseColor, specularColor](const Vec3f& wiW) {
		
			Vec3f wi = M * wiW;			// Transform the wiW vector from WCS to LCS

			// This lambda-function shoud return a float onstead of color. We return color just because we use 
			// the Phong and Blinn specular shaders, which are not phisically correct shaders.	
			Vec3f res(0, 0, 0);
			for (const auto& bxdfPair : this->m_vpBxDFs) {
				Vec3f color = bxdfPair.second->MatchesFlags(BxDFType::specular) ? specularColor : diffuseColor;
				res += bxdfPair.first * bxdfPair.second->f(wo, wi) * color;
			}
			return  res;

		});
	}
	
	// Re-Tracing components
	if ((m_type & (BxDFType::reflection | BxDFType::transmission)) != BxDFType::unset) 
		for (const auto& bxdfPair : this->m_vpBxDFs) {
			const size_t nSamples = bxdfPair.second->getNumSamples();
			if (!nSamples) continue;
			size_t nContributions = 0;
			thread_local Vec3f wi;
			Vec3f aux(0, 0, 0);
			for (size_t s = 0; s < nSamples; s++) {
				float weight = bxdfPair.first * bxdfPair.second->Sample_f(wo, wi, s);
				if (weight > Epsilon) {
					Vec3f org = p;	// positive hitpoint
					if (bxdfPair.second->MatchesFlags(BxDFType::transmission) && wi[2] < 0)
						org = ray.hitPoint(-n);	// negative hitpoint - below surface
					Ray newRay(org, M.t() * wi, ray.ndc, ray.counter);
					aux += weight * newRay.reTrace(getScene());
					nContributions++;
				}
			}
			if (nContributions)
				res += (1.0f / nContributions) * aux;
		}

	// ------ opacity ------
	if (opacity < 1 - Epsilon) {
		Ray newRay(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
		res = opacity * res + (1.0f - opacity) * newRay.reTrace(getScene());
	}
	
	return res;
}

void rt::CNewShader::addBSDF(const ptr_BxDF_t pBxDF, float scale)
{
	m_vpBxDFs.push_back(std::make_pair(scale, pBxDF));
	m_type |= pBxDF->getType();
}


// TODO: Rework getScene() 
// TODO: Rework getSampler()

Vec3f rt::CNewShader::eval_IR_LS(const Vec3f& point, const Vec3f& normal, brdf_function brdf) const {
	Vec3f res(0, 0, 0);
	
	for (auto& pLight : getScene().getLights()) {
		Vec3f L = Vec3f::all(0);
		const size_t nSamples = pLight->getNumSamples();
		for (size_t s = 0; s < nSamples; s++) {
			Ray shadowRay;
			auto radiance = pLight->illuminate(shadowRay, point, normal, s);
			if (radiance) {
				// Check shadow (light sourse is occluded)
				float k_occlusion = pLight->shadow() ? getScene().evalOcclusion(shadowRay) : 1.0f;
				if (k_occlusion < Epsilon) continue;

				float cosLightNormal = shadowRay.dir.dot(normal);
				if (cosLightNormal > 0)
					L += cosLightNormal * k_occlusion * brdf(shadowRay.dir).mul(radiance.value());
			}
		}
		res += (1.0f / nSamples) * L;
	}
	return res;
}

