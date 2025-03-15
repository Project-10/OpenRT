#include "ShaderSSLT.h"
#include "Scene.h"
#include "Ray.h"

namespace rt
{
	// Constructor
	CShaderSSLT::CShaderSSLT(const CScene& scene, const Vec3f& color, float opacity) : CShader(color), m_scene(scene)
	{
		setOpacity(opacity);
	}

	Vec3f CShaderSSLT::shade(const Ray& ray) const
	{
		Vec3f diffuseColor = getDiffuseColor(ray);
		float opacity = getOpacity(ray);
		
		Vec3f n = ray.hit->getShadingNormal(ray);				// shading normal
		
		// Gathering incoming light (incident radiance)
		Vec3f incident_radiance(0, 0, 0);
		Ray shadowRay(ray.hitPoint(n));
		for (auto& pLight : m_scene.getLights()) {
			Vec3f L = Vec3f::all(0);
			const size_t nSamples = pLight->getNumSamples();
			for (size_t s = 0; s < nSamples; s++) {
				// get direction to light, and intensity
				shadowRay.hit = ray.hit;	// Needed for the skylight
				auto radiance = pLight->illuminate(shadowRay);
				if (radiance) {
					// Check shadow (light sourse is occluded)
					float k_occlusion = pLight->shadow() ? m_scene.evalOcclusion(shadowRay) : 1.0f;
					if (k_occlusion < Epsilon) continue;

					float cosLightNormal = shadowRay.dir.dot(n);
					if (cosLightNormal > 0)
						L += cosLightNormal * k_occlusion * radiance.value();
				}
			}
			incident_radiance += (1.0f / nSamples) * L;
		}

		Ray R(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);
		Vec3f res = R.reTrace(m_scene);
		
		if (ray.dir.dot(n) < 0) { // entering the surface
			const double k = 0.35;
			const double f = k * R.t; // linear
			//const double f = k * R.t * R.t;
			const double alpha = MIN(1, f);
			return alpha * diffuseColor.mul(incident_radiance) + (1 - alpha) * res;
		}
		else return res;
		//
		//return opacity * diffuseColor + (1.0f - opacity) * res;

		opacity  = 1.0f; // for debugging
		res = opacity * diffuseColor.mul(incident_radiance);

		return res;
	}
}
