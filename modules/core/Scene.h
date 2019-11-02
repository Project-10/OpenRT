#pragma once

#include "ILight.h"
#include "Prim.h"
#include "CameraPerspective.h"

namespace rt {
	/**
	 * @brief Scene class
	 */
	class CScene
	{
	public:
		/**
		 * @brief Constructor
		 * @param camera The reference to the camera
		 * @todo Background may be image
		 */
		DllExport CScene(Vec3f bgColor = RGB(0,0,0))
			: m_bgColor(bgColor)
			, m_activeCamera(0)
		{}
		DllExport ~CScene(void) = default;
	  
		// ------------ TO IMPLEMENT ------------
		DllExport void save(const std::string& fileName) const {}
		DllExport void load(const std::string& fileName) {}
		DllExport void reset(void) {}
		// ------------ ------------ ------------

		/**
		 * @brief Adds a new primitive to the scene
		 * @param prim Pointer to the primitive
		 */
		DllExport void add(const std::shared_ptr<IPrim> pPrim) { m_vpPrims.push_back(pPrim); }
		/**
		 * @brief Adds a new light to the scene
		 * @param pLight Pointer to the light
		 */
		DllExport void add(const std::shared_ptr<ILight> pLight) { m_vpLights.push_back(pLight); }
		/**
		 * @brief Adds a new camera to the scene and makes it to ba active
		 * @param pCamera Pointer to the camera
		 */
		DllExport void add(const std::shared_ptr<ICamera> pCamera) { 
			m_vpCameras.push_back(pCamera); 
			m_activeCamera = m_vpCameras.size() - 1; 
		}
		/**
		 * @brief Sets the active camera
		 * @param activeCamera The new active camera index
		 */
		DllExport void setActiveCamera(size_t activeCamera) { if (activeCamera < m_vpCameras.size()) m_activeCamera = activeCamera; }
		/**
		 *@brief Returns the active camera
		 *@retuen The active camera index
		*/
		DllExport std::shared_ptr<ICamera> getActiveCamera(void) const { return m_vpCameras.empty() ? nullptr : m_vpCameras.at(m_activeCamera); }

		/*
		 * @brief Checks intersection of ray \b ray with all contained objects
		 * @param ray The ray
		 * @retval true If ray \b ray intersects any object
		 * @retval false otherwise
		 */
		DllExport bool intersect(Ray& ray) const
		{
			bool hit = false;
			for (auto& pPrim : m_vpPrims)
				hit |= pPrim->intersect(ray);
			return hit;
		}

		/**
		 * find occluder
		 */
		DllExport bool occluded(Ray& ray)
		{
			// --- PUT YOUR CODE HERE ---
			return false;
		}

		/**
		 * @brief Traces the given ray and shade it
		 * @param ray The ray
		 * @return The color of the shaded ray
		 */
		DllExport Vec3f rayTrace(Ray& ray) const
		{
			return intersect(ray) ? ray.hit->getShader()->shade(ray) : m_bgColor;
		}


	private:
		Vec3f									m_bgColor;    	///< background color
		std::vector<std::shared_ptr<IPrim>> 	m_vpPrims;		///< Primitives
		std::vector<std::shared_ptr<ILight>>	m_vpLights;		///< Lights
		std::vector<std::shared_ptr<ICamera>>	m_vpCameras;	///< Cameras
		size_t									m_activeCamera;	///< The index of the active camera
	};
}
