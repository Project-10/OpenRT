#pragma once

#include "Shader.h"
#include "Sampler.h"

namespace rt {
	class CScene;
	class CShaderScene : public CShader {
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the object
		 * @param pSampler Pointer to the sampler to be used for sampling the hemisphere around the shading point
		 */
		CShaderScene(const CScene& scene, const Vec3f& color, ptr_sampler_t pSampler = nullptr)
			: CShader(color)
			, m_scene(scene)
			, m_pSampler(pSampler)
		{ }
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param pTexture Pointer to the texture
		 * @param pSampler Pointer to the sampler to be used for sampling the hemisphere around the shading point
		 */
		CShaderScene(const CScene& scene, const ptr_texture_t pTexture, ptr_sampler_t pSampler = nullptr)
			: CShader(pTexture)
			, m_scene(scene)
			, m_pSampler(pSampler)
		{ }
	
		/**
		 */
		const CScene& getScene(void) const { return m_scene; }
		
		/**
		 */
		ptr_sampler_t getSampler(void) const { return m_pSampler; }
	

	protected:
		Vec3f eval_IR_LS(const Ray& ray) const;
		Vec3f eval_IR_all(const Ray& ray) const;


	private:
		const CScene&	m_scene;		///< Reference to the scene object
		ptr_sampler_t	m_pSampler;		///< Pointer to the sampler to be used for sampling the hemisphere around the shading point
	};
}