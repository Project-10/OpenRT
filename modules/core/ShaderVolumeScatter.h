// Volume Scatter Shader class
// Written by Sergey Kosov in 2025 for Project X
#pragma once

#include "ShaderScene.h"

namespace rt {
	class CScene;
	// ================================ Flat Shader Class ================================
	/**
	 * @brief Volume Scattering shader class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CShaderVolumeScatter : public CShaderScene {
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the material
		 * @param opacity The opacity of the material
		 */
		DllExport CShaderVolumeScatter(const CScene& scene, const Vec3f& color, ptr_sampler_t pSampler = nullptr, float opacity = 1.0f)
			: CShaderScene(scene, color, pSampler)
		{ setOpacity(opacity); }


		DllExport Vec3f shade(const Ray& ray) const override;
	};
};
