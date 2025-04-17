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
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
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
		 * @param amount The power of the texture (applies only on the texture)
		 */
		DllExport void	setAmbientColor(const ptr_texture_t pMap, float amount = 1.0f);
		/**
		 * @brief Sets the diffuse color
		 * @param color The color color
		 */
		DllExport void	setDiffuseColor(const Vec3f& color);
		/**
		 * @brief Sets the diffuse map
		 * @param pColorMap The pointer to the diffuse texture
		 * @param amount The power of the texture (applies only on the texture)
		 */
		DllExport void	setDiffuseColor(const ptr_texture_t pColorMap, float amount = 1.0f);
		/**
		 * @brief Sets the specular color
		 * @param color The specular color
		 */
		DllExport void	setSpecularColor(const Vec3f& color);
		/**
		 * @brief Sets the specular level map
		 * @param pSpecularLevel The specular level map
		 * @param amount The power of the ambient texture (applies only on the texture)
		 */
		DllExport void	setSpecularColor(const ptr_texture_t pSpecularLevel, float amount = 1.0f);
		/**
		* @brief Sets the bump map
		* @param pBumpMap The bump map
		* @param amount The power of bump
		*/
		DllExport void setBumpMap(const ptr_texture_t pBumpMap, float amount = 0.3f);
		/**
		 * @brief Sets the opacity
		 * @param opacity The opacity. Number between 0 and 1
		 */
		DllExport void	setOpacity(float opacity);
		/**
		 * @brief Sets the opacity map
		 * @param pOpacityMap The opacity map
		 * @param amount The power of the ambient texture (applies only on the texture)
		 */
		DllExport void	setOpacity(const ptr_texture_t pOpacityMap, float amount = 1.0f);


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
		 * @brief Returns the specular color value at the intersection point
		 * @param ray The ray hitting the primitive. ray.hit must point to the primitive
		 * @return The specular color value at the intersection point
		 */
		DllExport Vec3f getSpecularColor(const Ray& ray) const;
		/**
		* @brief Returns the bump map value at the intersection point
		* @param ray The ray hitting the primitive. ray.hit must point to the primitive
		* @return The bump map value at the intersection point
		*/
		DllExport std::optional<std::pair<float, float>> getBump(const Ray& ray) const;
		/**
		* @brief Returns the amount of bump
		* @return The amount of bump
		*/
		DllExport float getBumpAmount(void) const { return m_bumpAmount; }
		//DllExport float getBumpU(const Ray& ray) const;
		//DllExport float getBumpV(const Ray& ray) const;


		DllExport virtual float	getOpacity(const Ray& ray) const override final;
		
		
	private:
		Vec3f			m_ambientColor		= RGB(150, 150, 150);	///< The ambient color (initializes from diffuse)
		Vec3f			m_diffuseColor		= RGB(150, 150, 150);	///< The diffuse color
		Vec3f			m_specularColor		= RGB(255, 255, 255);	///< The specular color
		
		float			m_ambientAmount		= 1.0f;				///< The scale factor for ambient texture (applies only to the texture)
		float			m_diffuseAmount		= 1.0f;				///< The scale factor for diffuse texture (mixes with the diffuse color)
		float			m_specularAmount	= 1.0f;				///< The scale factor for the specular texture
		float			m_specularLevel		= 0;				///< The specular level (parameter of the reflectiove BRDFs)
		float			m_opacity			= 1.0f;				///< The opacity
		float			m_bumpAmount		= 0.3f;				///< The power of bump map
		float			m_opacityAmount		= 1.0f;				///< The scale factor for opacity map

		ptr_texture_t	m_pAmbientColorMap	= nullptr;			///< The ambient color map (initializes from diffuse)
		ptr_texture_t	m_pDiffuseColorMap 	= nullptr;			///< The diffuse color map (main texture)
		ptr_texture_t	m_pSpecularColorMap	= nullptr;			///< The specular color map
		//ptr_texture_t	m_pBumpMap			= nullptr;			///< The bump map
		ptr_texture_t	m_pBumpMap_u 		= nullptr;
		ptr_texture_t	m_pBumpMap_v 		= nullptr;
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

