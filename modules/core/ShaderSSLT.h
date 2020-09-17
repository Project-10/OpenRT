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
		const Vec3f m_exitColor = RGB(0.4f, 0.4f, 0.4f);
		const Vec3f	m_color = Vec3f::all(0.5f);
		float m_opacity;

	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param color The color of the material
		 * 
		 */
		DllExport CShaderSSLT(CScene& scene, Vec3f color, float opacity = 0.5f) : m_scene(scene),
			m_color(color),
			m_opacity(opacity)
		{}

		DllExport Vec3f shade(const Ray& ray) const override;
		Vec3f reTrace(const Ray& ray) const;
	};
};