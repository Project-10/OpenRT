#pragma once

#include "Shader.h"

namespace rt {
	class CScene;
	class CShaderScene : public CShader {
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 */
		CShaderScene(const CScene& scene, const Vec3f& color)
			: CShader(color)
			, m_scene(scene)
		{}
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 */
		CShaderScene(const CScene& scene, const ptr_texture_t pTexture)
			: CShader(pTexture)
			, m_scene(scene)
		{}
	
		/**
		 */
		const CScene& getScene(void) const { return m_scene; }
	
	protected:
		Vec3f eval_IR_LS(const Ray& ray) const;

	private:
		const CScene& m_scene;		///< Reference to the scene object
	};
}