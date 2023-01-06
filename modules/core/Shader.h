// Shader intermediate class
// Written by Sergey Kosov in 2021 for Jacobs University
#pragma once

#include "IShader.h"
#include "Texture.h"

namespace rt {
	// ================================ Shader Class ================================
	/**
	 * @brief Shader intermediate class for storing textures
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CShader : public IShader
	{
	public:
		/**
		 * @brief Default constructor
		 */
		DllExport CShader(void) = default;
		/**
		 * @brief Consructor
		 * @param color The diffuse color
		 */
		DllExport CShader(const Vec3f& color) : m_diffuseColor(color), m_ambientColor(color) {}
		/**
		 * @brief Constructor
		 * @param pColorMap The pointer to the diffuse color texture (type: CV_8UC3)
		 */
		DllExport CShader(const ptr_texture_t pColorMap) : m_pDiffuseColorMap(pColorMap), m_pAmbientColorMap(pColorMap) {}
		DllExport virtual ~CShader(void) = default;

		/**
		 * @brief Sets the ambient color
		 * @param color The ambient color
		 */
		DllExport void	setAmbientColor(const Vec3f& color);
		/**
		 * @brief Sets the ambient color map
		 * @param pMap The pointer to the ambient texture
		 */
		DllExport void	setAmbientColor(const ptr_texture_t pMap);
		/**
		 * @brief Sets the diffuse color
		 * @param color The color color
		 */
		DllExport void	setDiffuseColor(const Vec3f& color);
		/**
		 * @brief Sets the diffuse map
		 * @param pColorMap The pointer to the diffuse texture
		 */
		DllExport void	setDiffuseColor(const ptr_texture_t pColorMap);
		/**
		 * @brief Sets the specular level value
		 * @param level The specular level value
		 */
		DllExport void	setSpecularLevel(float level);
		/**
		 * @brief Sets the specular level map
		 * @param pSpecularLevel The specular level map
		 */
		DllExport void	setSpecularLevel(const ptr_texture_t pSpecularLevel);
		/**
		 * @brief Sets the opacity
		 * @param opacity The opacity. Number between 0 and 1
		 */
		DllExport void	setOpacity(float opacity);
		/**
		 * @brief Sets the opacity map
		 * @param pOpacityMap The opacity map
		 */
		DllExport void	setOpacity(const ptr_texture_t pOpacityMap);


		/**
		 * @brief Returns the ambient color value at the intersection point
		 * @param ray The ray hitting the primitive. ray.hit must point to the primitive
		 * @return The ambient color of the hit objesct
		 */
		DllExport Vec3f	getAmbientColor(const Ray& ray) const;
		/**
		 * @brief Returns the diffuse color value at the intersection point
		 * @param ray The ray hitting the primitive. ray.hit must point to the primitive
		 * @return The diffuse color of the hit objesct
		 */
		DllExport Vec3f	getDiffuseColor(const Ray& ray) const;
		/**
		 * @brief Returns the specular level value at the intersection point
		 * @param ray The ray hitting the primitive. ray.hit must point to the primitive
		 * @return The specular level value at the intersection point
		 */
		DllExport float getSpecularLevel(const Ray& ray) const;
		/**
		 * @brief Returns the opacity
		 * @return The opacity value
		 */
		DllExport float	getOpacity(const Ray& ray) const;
		
		
	private:
		Vec3f			m_ambientColor		= Vec3f::all(0);	///< The ambient color
		Vec3f			m_diffuseColor		= Vec3f::all(0);	///< The diffuse color
		float			m_specularLevel		= 0;				///< The specular level
		float			m_opacity			= 1;				///< The opacity
		
		ptr_texture_t	m_pAmbientColorMap	= nullptr;			///< The ambient color map
		ptr_texture_t	m_pDiffuseColorMap 	= nullptr;			///< The diffuse color map (main texture)
		ptr_texture_t	m_pSpecularLevelMap	= nullptr;			///< The specular level map
		ptr_texture_t	m_pOpacityMap		= nullptr;			///< The opacity map
		
		// --- MAPS (amount + map) ---
		// Ambient color (usually equal to diffuse color)
		// Diffuse color
		// Specular color
		// Specular level
		// Glossiness
		// Self-Illumination
		// Opacity
		// Filter color
		// Bump
		// Reflection
		// Refraction
		// Displacement

	};


}

