#pragma once

#include "ShaderScene.h"

namespace rt {
	class CScene;
	// ================================ Flat Shader Class ================================
	/**
	 * @brief Sub-surface light transport shader class
	 * @details The <em>Subsurface Scattering</em> shader is used to add simple subsurface multiple 
	 * scattering, for materials such as skin, wax, marble, milk and others. For these materials, 
	 * rather than light being reflect directly off the surface, it will penetrate the surface and 
	 * bounce around internally before getting absorbed or leaving the surface at a nearby point.
	 * 
	 * How far the color scatters on average can be configured per RGB color channel. For example, 
	 * for skin, red colors scatter further, which gives distinctive red-colored shadows, and a soft 
	 * appearance.
	 * @ingroup moduleShader
	 * @author Ezana T. Geressu, e.geressu@jacobs-university.de
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CShaderSubsurfaceScattering : public CShaderScene {
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the material
		 */
		DllExport CShaderSubsurfaceScattering(const CScene& scene, const Vec3f& color, ptr_sampler_t pSampler = nullptr)
			: CShaderScene(scene, color, pSampler)
		{}

		DllExport Vec3f shade(const Ray& ray) const override;
	};
};
