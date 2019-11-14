#pragma once

#include "IShader.h"

namespace rt {
	class CShaderMirror : public IShader
	{
	public:
		DllExport CShaderMirror(CScene& scene) : m_scene(scene) {}
		DllExport virtual ~CShaderMirror(void) = default;
		
		DllExport virtual Vec3f shade(const Ray& ray) const override
		{
			Vec3f normal = ray.hit->getNormal(ray.hitPoint());						// shading normal
			if (normal.dot(ray.dir) > 0) normal = -normal;							// turn normal to front
			Vec3f reflect = normalize(ray.dir - 2 * normal.dot(ray.dir) * normal);	// reflection vector

			Ray I(ray.hitPoint(), reflect);
			I.counter = ray.counter + 1;

			return m_scene.rayTrace(I);
		}
		
	private:
		CScene& m_scene;
	};
}

