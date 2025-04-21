#include "ShaderScene.h"
#include "IBxDF.h"

#pragma once

namespace rt {
	using brdf_function = std::function<Vec3f(const Vec3f&)>;
	class Scene;

	class CNewShader : public CShaderScene
	{
	public:
		DllExport CNewShader(const CScene& scene, const Vec3f& color)
			: CShaderScene(scene, color)
		{ }
		DllExport CNewShader(const CScene& scene, const ptr_texture_t pTexture)
			: CShaderScene(scene, pTexture)
		{ }
		DllExport virtual ~CNewShader(void) = default;

		DllExport virtual Vec3f shade(const Ray& ray) const override;

		// Rename and add the type of the BRDF to be added here.
		DllExport void			addBSDF(const ptr_BxDF_t pBxDF, float scale = 1.0f);

	
	protected:
		Vec3f eval_IR_LS(const Vec3f& point, const Vec3f& normal, brdf_function brdf) const;


	private:
		std::vector<std::pair<float, ptr_BxDF_t>>	m_vpBxDFs;
		BxDFType									m_type = BxDFType::unset;
	};
}