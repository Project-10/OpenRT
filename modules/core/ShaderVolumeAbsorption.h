// Volume Absorption Shader class
// Written by Sergey Kosov in 2025 for OpenRT.org
#pragma once

#include "ShaderScene.h"

namespace rt {
	class CScene;
	// ================================ Volume Absorption Shader Class ================================
	/**
	 * @brief Sub-surface light transport shader class
	 * @details The <em>Volume Absorption</em> shader allows light to be absorbed as it passes through the volume. 
	 * Typical usage for this shader would be water and colored glass.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CShaderVolumeAbsorption : public CShaderScene {
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color Color of the volume.
		 * @param density The density of the absorption effect.
		 */
		DllExport CShaderVolumeAbsorption(const CScene& scene, const Vec3f& color, float density = 1.0f)
			: CShaderScene(scene, color)
			, m_density(density)
		{ }

		DllExport Vec3f shade(const Ray& ray) const override;


	private:
		const float m_density;	///< The density of the absorption effect.
	};
};