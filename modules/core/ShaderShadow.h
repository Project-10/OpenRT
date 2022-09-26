// Shadow Shader class
// Written by Sergey Kosov in 2022 for Project X
#pragma once

#include "Shader.h"

namespace rt {
	class CScene;
	// ================================ SHadow Shader Class ================================
	/**
	 * @brief Shadow shader class
	 * @details This shader is fully transparent except shadows.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderShadow : public CShader
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free shader
		 * @param color The color of the object
		 */
		DllExport CShaderShadow(const CScene& scene) : CShader(), m_scene(scene) {}
		DllExport virtual ~CShaderShadow(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;


	private:		
		const CScene& m_scene;		///< Reference to the scene object
	};
}