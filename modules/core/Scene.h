#pragma once

#include "ILight.h"
#include "IPrim.h"
#include "Solid.h"
#include "CameraPerspective.h"
#include "BSPTree.h"
#include "Sampler.h"
#include "IShader.h"

namespace rt {
	/**
	 * @brief Scene class
	 */
	class CScene
	{
	public:
		/**
		 * @brief Constructor
		 * @param bgColor The default bachground color
		 * @todo Background may be image
		 */
		DllExport CScene(Vec3f bgColor = RGB(0,0,0))
			: m_bgColor(bgColor)
		{}
		DllExport ~CScene(void) = default;
	  
		// ------------ TO IMPLEMENT ------------
		DllExport void save(const std::string& fileName) const {}
		DllExport void load(const std::string& fileName) {}
		DllExport void clear(void) {}
		// ------------ ------------ ------------

		/**
		 * @brief Adds a new primitive to the scene
		 * @param pPrim Pointer to the primitive
		 */
		DllExport void add(const ptr_prim_t pPrim) { m_vpPrims.push_back(pPrim); }
		/**
		 * @brief Add a new solid to the scene
		 * @param solid The reference to the solid
		 */
		DllExport void add(const CSolid& solid) {
			for (const auto& pPrim : solid.getPrims()) add(pPrim);
		}
		/**
		 * @brief Adds a new light to the scene
		 * @param pLight Pointer to the light
		 */
		DllExport void add(const std::shared_ptr<ILight> pLight) { m_vpLights.push_back(pLight); }
		/**
		 * @brief Adds Sky Light
		 * @param pLight Pointer to the light
		 */
		DllExport void add(const ptr_shader_t pShaderAO) { m_vpAOs.push_back(pShaderAO); }
		/**
		 * @brief Adds a new camera to the scene and makes it to ba active
		 * @param pCamera Pointer to the camera
		 */
		DllExport void add(const ptr_camera_t pCamera) {
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
		 *@return The active camera index
		*/
		DllExport ptr_camera_t getActiveCamera(void) const { return m_vpCameras.empty() ? nullptr : m_vpCameras.at(m_activeCamera); }
		/**
		 * @brief Returns the container with all scene light objects
		 * @return The vector with pointers to the scene lights
		*/
		const std::vector<std::shared_ptr<ILight>> getLights(void) const { return m_vpLights; }
		/**
		 * @brief Build the BSP tree for the current scene
		 * @details This function takes into accound all the primitives in scene and builds the BSP tree with the root node in \b m_pBSPTree variable
		 */
		void buildAccelStructure(void)
		{
			CBoundingBox box = calcBounds();
			std::cout << "Scene bounds are : " << box.m_min << " " << box.m_max << std::endl;
			m_pBSPTree = std::make_unique<BSPTree>(box, m_vpPrims);
		}
		/**
		 * @brief Find occluder
		 * @param ray The ray
		 * @retval true If point \b ray.org is occluded
		 * @retval false otherwise
		 */
		DllExport bool occluded(const Ray& ray)
		{
#ifdef ENABLE_BSP
			return m_pBSPTree->intersect(lvalue_cast(Ray(ray)));
#else
			for (auto& pPrim : m_vpPrims)
				if (pPrim->if_intersect(ray)) return true;
			return false;
#endif
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

		DllExport float ambientOcclusion(Ray& ray) const
		{
			Vec3f ao  = 0;
			for (auto pShderAO : m_vpAOs) {
				ao += pShderAO->shade(ray);
			}
			ao = m_vpAOs.empty() ? Vec3f::all(1) : ao;
			return ao[0];
			
		}

		DllExport float rayTraceDepth(Ray& ray) const
		{
			return intersect(ray) ? ray.t : 0;
		}
		/**
		 * @brief Renders the view from the active camera
		 * @returns The rendered image
		 */
		DllExport Mat render(std::shared_ptr<CSampler> pSampler = nullptr) const;
		DllExport Mat renderDepth(void) const;
		DllExport Vec3f dimension(void){return m_bBox.m_max - m_bBox.m_max;}
		DllExport bool pathTrace(Ray& ray){return intersect(ray);}
	
	private:
		/**
		 * @brief Calculates and return the bounding box, containing the whole scene
		 * @return The bounding box, containing the whole scene
		 */
		CBoundingBox calcBounds(void)
		{
			for (auto pPrim : m_vpPrims)
				m_bBox.extend(pPrim->calcBounds());
			return m_bBox;
		}
		/*
		 * @brief Checks intersection of ray \b ray with all contained objects
		 * @param ray The ray
		 * @retval true If ray \b ray intersects any object
		 * @retval false otherwise
		 */
		DllExport bool intersect(Ray& ray) const
		{
#ifdef ENABLE_BSP
			return m_pBSPTree->intersect(ray);
#else
			bool hit = false;
			for (auto& pPrim : m_vpPrims)
				hit |= pPrim->intersect(ray);
			return hit;
#endif
		}
		
		
	private:
		const Vec3f								m_bgColor;    			///< background color
		std::vector<ptr_prim_t> 				m_vpPrims;				///< Primitives
		std::vector<std::shared_ptr<ILight>>	m_vpLights;				///< Lights
		std::vector<ptr_camera_t>				m_vpCameras;			///< Cameras
		size_t									m_activeCamera	= 0;	///< The index of the active camera
		std::unique_ptr<BSPTree>				m_pBSPTree		= nullptr;
		std::vector<ptr_shader_t>				m_vpAOs;
		CBoundingBox							m_bBox;					//Scene Bounding box
	};
}
