// Scene class
// Written by Sergey Kosov in 2019 for Jacobs University
#pragma once

#include "Prim.h"
#include "Texture.h"
#include "ILight.h"
#include "ICamera.h"
#include "Sampler.h"
#ifdef ENABLE_BSP
#include "BSPTree.h"
#endif

namespace rt {
	class CPrimSphere;
	class CPrimPlane;
	class CPrimDisc;
	class CPrimTriangle;
	class CSolid;
	
	// ================================ Scene Class ================================
	/**
	 * @brief Scene class
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CScene
	{
	public:
		/**
		 * @brief Constructor
		 * @param bgColor The default background color
		 */
		DllExport CScene(const Vec3f& bgColor = RGB(0,0,0))
			: m_bgColor(bgColor)
#ifdef ENABLE_BSP	
			, m_pBSPTree(new CBSPTree())
#endif
		{}
		/**
		 * @brief Constructor
		 * @param bgMap The default background texture map
		 */
		DllExport CScene(const ptr_texture_t bgMap)
			: m_bgMap(bgMap)
#ifdef ENABLE_BSP	
			, m_pBSPTree(new CBSPTree())
#endif
		{}
		DllExport CScene(const CScene&) = delete;
		DllExport ~CScene(void) = default;
		DllExport const CScene& operator=(const CScene&) = delete;
	  
		// ------------ TO IMPLEMENT ------------
		/// @todo implement
		DllExport void save(const std::string& fileName) const {}
		/// @todo implement
		DllExport void load(const std::string& fileName) {}
		// ------------ ------------ ------------

		/**
		 * @brief Clears the scene from geometry, lights and cameras (if any)
		 */
		DllExport void					clear(void);

		/**
		 * @brief Creates a primitive sphere
		 * @param scene The reference to the scene
		 * @param origin Position of the center of the sphere
		 * @param radius Radius of the sphere
		 * @param color The color of the object
		 */
		DllExport std::shared_ptr<CPrimSphere> addSphere(const Vec3f& origin = Vec3f::all(0), float radius = 1.0f, const Vec3f& color = Vec3f::all(1));

		/**
		 * @brief Creates a primitive plane
		 * @param scene The reference to the scene
		 * @param origin Point on the plane
		 * @param normal Normal to the plane
		 * @param color The color of the object
		 */
		DllExport std::shared_ptr<CPrimPlane> addPlane(const Vec3f& origin = Vec3f::all(0), const Vec3f& normal = Vec3f(0, 1, 0), const Vec3f& color = Vec3f::all(1));

		/**
		 * @brief Creates a primitive disc
		 * @param scene The reference to the scene
		 * @param origin The center pointof the disc
		 * @param normal Normal to the disc
		 * @param radius Radius of the disc
		 * @param innerRadius The disc can also be generalized to an annulus by specifying an inner radius
		 * @param color The color of the object
		 */
		DllExport std::shared_ptr<CPrimDisc> addDisc(const Vec3f& origin = Vec3f::all(0), const Vec3f& normal = Vec3f(0, 1, 0), float radius = 1.0f, float innerRadius = 0.0f, const Vec3f& color = Vec3f::all(1));

		/**
		 * @brief Creates a primitive triangle
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 * @param ta Texture coordinate for the first vertex
		 * @param tb Texture coordinate for the second vertex
		 * @param tc Texture coordinate for the third vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 * @param color The color of the object
		 */
		DllExport std::shared_ptr<CPrimTriangle> addTriangle(const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec2f& ta = Vec2f::all(0), const Vec2f& tb = Vec2f::all(0), const Vec2f& tc = Vec2f::all(0), std::optional<Vec3f> na = std::nullopt, std::optional<Vec3f> nb = std::nullopt, std::optional<Vec3f> nc = std::nullopt, const Vec3f& color = Vec3f::all(1));

		/**
		 * @brief Creates a primitive triangle
		 * @param origin The pivot point (origin) of the triangle (or solid)
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 * @param ta Texture coordinate for the first vertex
		 * @param tb Texture coordinate for the second vertex
		 * @param tc Texture coordinate for the third vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 * @param color The color of the object
		 */
		DllExport std::shared_ptr<CPrimTriangle> addTriangle(const Vec3f& origin, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec2f& ta = Vec2f::all(0), const Vec2f& tb = Vec2f::all(0), const Vec2f& tc = Vec2f::all(0), std::optional<Vec3f> na = std::nullopt, std::optional<Vec3f> nb = std::nullopt, std::optional<Vec3f> nc = std::nullopt, const Vec3f& color = Vec3f::all(1));
		
		/**
		 * @brief Adds a new primitive to the scene
		 * @param pPrim Pointer to the primitive
		 */
		DllExport void					add(const ptr_prim_t pPrim);
		/**
		 * @brief Add a new solid to the scene
		 * @param solid The reference to the solid
		 */
		DllExport void					add(const CSolid& solid);
		/**
		 * @brief Adds a new light to the scene
		 * @param pLight Pointer to the light
		 */
		DllExport void					add(const ptr_light_t pLight);
		/**
		 * @brief Adds a new camera to the scene and makes it to ba active
		 * @param pCamera Pointer to the camera
		 */
		DllExport void					add(const ptr_camera_t pCamera);
		/**
		 * @brief Sets the active camera
		 * @param activeCamera The new active camera index
		 */
		DllExport void					setActiveCamera(size_t activeCamera);
		/**
		 * @brief (Re-) Build the BSP tree for the current geometry present in scene
		 * @details This function takes into accound all the primitives in scene and builds the BSP tree with the root node in \b m_pBSPTree variable.
		 * If the geometry in the scene was updated the BSP tree should be re-built
		 * @param maxDepth The maximum allowed depth of the tree.
		 * Increasing the depth of the tree may speed-up rendering, but increse the memory consumption.
		 * @param minPrimitives The minimum number of primitives in a leaf-node.
		 * This parameters should be alway above 1.
		 */
		DllExport void					buildAccelStructure(size_t maxDepth = 20, size_t minPrimitives = 3);
		/**
		 * @brief Renders the view from the active camera
		 * @param pSampler Pointer to the sampler to be used for anti-aliasing.
		 * @param tileSize Size of the tile for rendering. If set to 0, the entire image is rendered at once.
		 *                 Usually, tileSize is a power of two (e.g., 32, 64, 128). The typical value is 32.
		 *                 Rendering with tiles allows the user to see intermediate results, but is generally slower than rendering the entire image at once.
		 * @returns The rendered image (type: CV_8UC3)
		 */
		DllExport Mat					render(ptr_sampler_t pSampler = nullptr, size_t tileSize = 0) const;
		/**
		 * @brief Renders a specific tile of the image.
		 * @details This function is used to render a specific tile of the image. It processes the pixel values within the specified tile boundaries (y_start to y_end and x_start to x_end).
		 * Rendering in tiles allows the user to see intermediate results during the rendering process but generally takes longer than rendering the entire image at once.
		 * @param img Reference to the image being rendered.
		 * @param pSampler Pointer to the sampler to be used for anti-aliasing.
		 * @param y_start Starting Y-coordinate of the tile.
		 * @param y_end Ending Y-coordinate of the tile.
		 * @param x_start Starting X-coordinate of the tile.
		 * @param x_end Ending X-coordinate of the tile.
		 */
		void							render_tile(Mat& img, ptr_sampler_t pSampler, int y_start, int y_end, int x_start, int x_end) const;

		/**
		 * @brief Renders the depth-map from the active camera
		 * @param pSampler Pointer to the sampler to be used for anti-aliasing.
		 * @returns The rendered image (type: CV_64FC1)
		 */
		DllExport Mat					renderDepth(ptr_sampler_t pSampler = nullptr) const;
		/**
		 * @brief Loads the last rendered image from cache.
		 * @note This method can only be used if ENABLE_CACHE is on. It also uses the m_cachePath as a default location.
		 * @return The last cached render.
		 */
		DllExport Mat					getLastRenderedImage(void) const;

	public:
		/**
		 * @brief Returns the container with all scene light source objects
		 * @note This method is to be used only in OpenRT shaders
		 * @return The vector with pointers to the scene light sources
		 */
		const std::vector<ptr_light_t>	getLights(void) const { return m_vpLights; }
		/**
		 * @brief Returns the ambient
		 */
		Vec3f							getAmbientColor(void) const { return m_ambientColor; }
		/**
		 * @brief Checks intersection between ray \b ray and the geometry present in scene
		 * @details This function calls \b CPrim::intersect() method for all scene's primitives. If valid intersecton(s) is(are) found, the argument \b ray is updated:
		 * Ray::t will be set to the distance to the closest intersection point and Ray::hit will point to the closest primitive intersected by the ray.
		 * @note This method is to be used only in OpenRT shaders
		 * @param[in,out] ray The ray (Ref. @ref Ray for details)
		 * @retval true If ray \b ray intersects any object
		 * @retval false otherwise
		 */
		bool							intersect(Ray& ray) const;
		/**
		 * @brief Evaluates the degree of occlusion from the light source
		 * @param ray The shadow ray (Ref. @ref Ray for details). Usually a ray originating at a shading point of an object and pointing to a light source
		 * @retval A coefficient (between 0 and 1) indicating the percentage of light coming to the object's point. 1 - means that 100% of light reaching the surface, 0 - total occlusion.
		 */
		float							evalOcclusion(const Ray& ray) const;
		/**
		 * @brief Traces the given ray and shades it
		 * @note This method is to be used only in OpenRT shaders
		 * @param ray The ray (Ref. @ref Ray for details)
		 * @return The color value of the shaded ray
		 */
		Vec3f							rayTrace(Ray& ray) const;
		/**
		 * @brief Traces the given ray and finds the intersection to the closest object
		 * @note This method is to be used only in OpenRT shaders
		 * @param ray The ray (Ref. @ref Ray for details)
		 * @return The distance bitween ray.org and the intersection to the nearest object
		 */
		double							rayTraceDepth(Ray& ray) const;

	
	private:
		/**
		 * @brief Returns the active camera
		 * @retval ptr_camera_t The pointer to active camera 
		 * @retval nullptr If there are no cameras added yet into the scene
		 */
		ptr_camera_t					getActiveCamera(void) const { return m_vpCameras.empty() ? nullptr : m_vpCameras.at(m_activeCamera); }
		/**
		 * @brief Checks intersection between ray \b ray and the geometry present in scene
		 * @details In contrast to the intersect() method, this method does not modify argument \b ray and returns once the first intersection found. Thus this method
		 * is faster then intersect() and may be used to check occlusions.
		 * @note This method is to be used only in OpenRT shaders
		 * @param ray The ray (Ref. @ref Ray for details)
		 * @retval true If point \b ray.org is occluded
		 * @retval false otherwise
		 */
		bool							if_intersect(const Ray& ray) const;

		
	private:
		const Vec3f					m_bgColor		= Vec3f::all(0);		///< background color
		const Vec3f					m_ambientColor	= Vec3f::all(1);		///< ambient color
		const ptr_texture_t			m_bgMap			= nullptr;				///< background texture map
		std::vector<ptr_prim_t>		m_vpPrims;								///< Primitives
		std::vector<ptr_light_t>	m_vpLights;								///< Lights
		std::vector<ptr_camera_t>	m_vpCameras;							///< Cameras
		size_t						m_activeCamera	= 0;					///< The index of the active camera
#ifdef ENABLE_BSP
		std::unique_ptr<CBSPTree>	m_pBSPTree		= nullptr;				///< Pointer to the acceleration structure
#endif
#ifdef ENABLE_CACHE
		const std::string			m_lriFileName	= "last_render.png";	///< Last rendered image filename
#endif
	};
}
