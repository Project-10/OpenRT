#include "ShaderScene.h"
#include "Scene.h"
#include "Ray.h"

namespace rt {
	Vec3f CShaderScene::eval_IR_LS(const Ray& ray) const {
		Vec3f res(0, 0, 0);

		Vec3f n = ray.hit->getShadingNormal(ray);				// shading normal

		Ray shadowRay(ray.hitPoint(n));
		for (auto& pLight : m_scene.getLights()) {
			Vec3f L = Vec3f::all(0);
			const size_t nSamples = pLight->getNumSamples();
			for (size_t s = 0; s < nSamples; s++) {
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
			res += (1.0f / nSamples) * L;
		}
		return res;
	}
}