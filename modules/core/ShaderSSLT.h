#pragma once

#include "ShaderFlat.h"
#include "Scene.h"

namespace rt {
	/**
		 * @brief Subsurface light transport shader
		 */
	class CShaderSSLT : public CShaderFlat {
	private:
		CScene& m_scene;
		const Vec3f exitColor = RGB(0.4f, 0.4f, 0.4f);
		const Vec3f	m_color = Vec3f::all(0.5f);

	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the material
		 * 
		 */
		DllExport CShaderSSLT(CScene& scene, Vec3f color) : m_scene(scene),
			m_color(color)
		{}

		DllExport virtual Vec3f shade(const Ray& ray) const override;
		Vec3f reTrace(const Ray& ray) const;
	};
};