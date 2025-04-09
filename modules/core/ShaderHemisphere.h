#pragma once

#include "ShaderScene.h"
#include "Sampler.h"

namespace rt {
	class CScene;

	class CShaderHemisphere : public CShaderScene
	{
	public:
		DllExport CShaderHemisphere(const CScene& scene, const Vec3f& color, ptr_sampler_t pSampler = nullptr) 
			: CShaderScene(scene, color, pSampler)
		{ }
		DllExport virtual ~CShaderHemisphere(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;

		float brdf(const Vec3f& ray, const Vec3f& dir_light) const;
	};
}