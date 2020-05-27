#pragma once

#include "IShader.h"
#include "ray.h"
#include "Texture.h"

namespace rt {
	/**
	 * @brief Flat shader class
	 */
	class CShaderFlat : public IShader
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free and light-source-free shader
		 * @param color The color of the object
		 */
		DllExport CShaderFlat(const Vec3f& color) : m_color(color) {}
		DllExport CShaderFlat(const ptr_texture_t pTexture = nullptr) : m_pTexture(pTexture) {}
		DllExport virtual ~CShaderFlat(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override
		{
			return m_pTexture ? m_pTexture->getTexel(ray.hit->getTextureCoords(ray)) : m_color;
		}

		DllExport virtual std::optional<Ray> interaction(Ray &ray) override {return std::nullopt;}
		DllExport virtual Vec3f shadePhoton(Photon& p) override {return m_color;}


	private:
		const Vec3f 		m_color		= Vec3f::all(0.5f);
		const ptr_texture_t m_pTexture	= nullptr;
	};
}
