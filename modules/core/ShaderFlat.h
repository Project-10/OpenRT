// Flat Shader class
// Written by Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "IShader.h"

namespace rt {
	// ================================ Flat Shader Class ================================
	/**
	 * @brief Special "flat" shader class
	 * @details This shader does not take scene in account. Therefore it is independenta from light sources and cameras.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShaderFlat : public IShader
	{
	public:
		/**
		 * @brief Constructor
		 * @details This is a texture-free and light-source-free shader
		 * @param color Color of the surface
		 * @param castShadow Flag indicating if the object casts shadow
		 * @note The \b castShadow parameter has no effect if the Shadow Processing mode switched to FAST
		 */
		DllExport CShaderFlat(const Vec3f& color, bool castShadow = true) 
			: m_color(color)
			, m_castShadow(castShadow)
		{}
		/**
		 * @brief Constructor
		 * @details This is a light-source-free shader
		 * @param pTexture Pointer to the texture
		 */
		//DllExport CShaderFlat(const ptr_texture_t pTexture) : CShader(pTexture) {}
		DllExport virtual ~CShaderFlat(void) = default;

		/**
		 * @brief Sets a new color of the surface
		 * @param color Color of the surface
		 */
		DllExport void	setColor(const Vec3f& color) { m_color = color; }

		DllExport Vec3f shade(const Ray& ray) const override final;
		DllExport float getOpacity(const Ray& ray) const override final;


	private:
		Vec3f	m_color;		///< Color of the surface
		bool	m_castShadow;	///< Flag indicating if the object casts shadow
	};
}
