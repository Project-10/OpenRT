#pragma once

#include "IShader.h"
#include "random.h"		// TODO: delete

namespace rt {
	class CShaderMirror : public IShader
	{
	public:
		DllExport CShaderMirror(CScene& scene) : m_scene(scene) {}
		DllExport virtual ~CShaderMirror(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override
		{
			const int nSamples = 64;
			Vec3f res = Vec3f::all(0);
			for (int s = 0; s < nSamples; s++) {
				Vec3f normal = ray.hit->getNormal(ray);									// shading normal
				if (normal.dot(ray.dir) > 0) normal = -normal;							// turn normal to front

				for (int i = 0; i < 3; i++)
					normal.val[i] += random::N<float>(0.0f, 0.3f);

				Vec3f reflect = normalize(ray.dir - 2 * normal.dot(ray.dir) * normal);	// reflection vector

				Ray I(ray.hitPoint(), reflect);
				I.counter = ray.counter + 1;

				res += I.counter >= 2 ? Vec3f::all(0) : /*Vec3f::all(0.05f) + 0.95f */ m_scene.rayTrace(I);
			}
			res = (1.0f / nSamples) * res;
			return res;

		}
		
	private:
		CScene& m_scene;
	};
}

