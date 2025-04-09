// Shader intermediate class
// Written by Sergey Kosov in 2024 for Project X
#pragma once

#include "ShaderScene.h"
#include "Sampler.h"

namespace rt {
	class CScene;

	class CShaderGlobal : public CShaderScene
	{
	public:
		DllExport CShaderGlobal(const CScene& scene, const Vec3f& color, ptr_sampler_t pSampler = nullptr)
			: CShaderScene(scene, color, pSampler)
		{ }
		DllExport virtual ~CShaderGlobal(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;
	};
}