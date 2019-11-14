#pragma once

#include "IShader.h"

namespace rt {
	class CShaderGlass : public IShader {
	public:
		DllExport CShaderGlass(CScene& scene) : m_scene(scene) {}
		DllExport virtual ~CShaderGlass(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override
		{
			const float k = 1.517f;
			
			Vec3f normal = ray.hit->getNormal(ray.hitPoint());						// shading normal
			bool inside = false;
			if (normal.dot(ray.dir) > 0) {
				normal = -normal;													// turn normal to front
				inside = true;
			}
			
			float K = inside ? k : 1.0f / k;
			
			float cos_alpha = -ray.dir.dot(normal);
			float sin_2_alpha = 1.0f - cos_alpha * cos_alpha;
			float k_2_sin_2_alpha = K * K * sin_2_alpha;
			Vec3f refract;
			if (k_2_sin_2_alpha <= 1) {
				float cos_beta    = sqrtf(1.0f - K * K * sin_2_alpha);
				refract = normalize((K * cos_alpha - cos_beta) * normal + K * ray.dir);	// refracted vector
			} else
				refract = normalize(ray.dir - 2 * normal.dot(ray.dir) * normal);		// reflection vector
			
			Ray R(ray.hitPoint(), refract);
			
			R.counter = ray.counter + 1;
			
			return m_scene.rayTrace(R);
		}
		
	private:
		CScene& m_scene;
	};
}

