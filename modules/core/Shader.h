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
		 * @param diffuse The diffuse color
		 */
		DllExport CShader(const Vec3f& color) : m_color(color) {}
		/**
		 * @brief Constructor
		 * @param pDiffuseMap The pointer to the diffuse color texture (type: CV_8UC3)
		 */
		DllExport CShader(const ptr_texture_t pColorMap) : m_pColorMap(pColorMap) {}
		DllExport virtual ~CShader(void) = default;

		
		/**
		 * @brief Sets the diffuse color
		 * @param diffuse The diffuse color
		 */
		DllExport void setColor(const Vec3f& color);
		/**
		 * @brief Sets the diffuse map
		 * @param pDiffuseMap The pointer to the diffuse texture (type: CV_8UC3)
		 */
		DllExport void setColor(const ptr_texture_t pColorMap);
		
		/**
		 * @brief Returns the color value at the intersection point
		 * @param ray The ray hitting the primitive. ray.hit must point to the primitive
		 * @return The color of the hit objesct
		 */
		DllExport Vec3f getColor(const Ray& ray) const;
		
		
		
	private:
		Vec3f			m_color			= Vec3f::all(0);	///< The diffuse color
		
		ptr_texture_t	m_pColorMap 	= nullptr;			//< The main texture (type: CV_8UC3)
		
		//ptr_texture_t	m_pDiffuseMap	= nullptr;			///< The diffuse texture (type: CV_8UC1)
		//ptr_texture_t m_pSpecularMap	= nullptr;		///< The specular texture (type: CV_8UC1)
		//ptr_texture_t m_pReflectionMap	= nullptr;		///< The reflection texture (type: CV_8UC1)
		//ptr_texture_t m_pRefractionMap	= nullptr;		///< The refraction texture (type: CV_8UC1)
		//ptr_texture_t m_pOpacityMap		= nullptr;		///< The opacity texture (type: CV_8UC1)
		//ptr_texture_t m_pBumpMap		= nullptr;		///< The bump texture (type: CV_8UC1)

	};


}

