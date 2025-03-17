// Shadow Shader class
// Written by Sergey Kosov in 2022 for Project X
#pragma once

#include "ShaderScene.h"

namespace rt {
	class CScene;
	// ================================ SHadow Shader Class ================================
	/**
	 * @brief Shadow shader class
	 * @details This shader is fully transparent except shadows.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderShadow : public CShaderScene
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free shader
		 * @param color The color of the object
		 */
		DllExport CShaderShadow(const CScene& scene) : CShaderScene(scene, Vec3f::all(0)) {}
		DllExport virtual ~CShaderShadow(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;
	};
}