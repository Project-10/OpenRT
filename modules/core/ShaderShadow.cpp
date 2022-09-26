#include "ShaderShadow.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderShadow::shade(const Ray& ray) const
	{
		// Traverse ray behind the geometry to make it fully transparent
		Ray R(ray.hitPoint(), ray.dir, ray.ndc, ray.counter);	// traverse ray
		Vec3f res = R.reTrace(m_scene);
		
		// Gathering shadows
		Vec3f shadingNormal = ray.hit->getShadingNormal(ray);
		
		Ray I(ray.hitPoint(shadingNormal));				// shadow ray
		Vec3f L_possible = Vec3f::all(0);
		Vec3f L_actual = Vec3f::all(0);
		for (auto& pLight : m_scene.getLights()) {
			const size_t nSamples = pLight->getNumSamples();
			const float avg = 1.0f / nSamples;
			for (size_t s = 0; s < nSamples; s++) {
				// get direction to light, and intensity
				I.hit = ray.hit;	// TODO: double check
				auto radiance = pLight->illuminate(I);
				if (radiance) {
					float cosLightNormal = I.dir.dot(shadingNormal);
					if (cosLightNormal > 0) {
						Vec3f L = avg * cosLightNormal * radiance.value();
						L_possible += L;
						if (!pLight->shadow() || !m_scene.if_intersect(I))
							L_actual += L;
					}
				}
			} // s
		} // pLight

		for (int i = 0; i < 3; i++) 
			if (L_possible[i] > 0)
				res[i] *= L_actual[i] / L_possible[i];

		return res;
	}
}