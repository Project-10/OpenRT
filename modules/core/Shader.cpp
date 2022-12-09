
#include "Shader.h"
#include "Ray.h"
#include "macroses.h"

namespace rt {
	// ============================================== Ambient Color ==============================================
	void CShader::setAmbientColor(const Vec3f& color)
	{
		m_ambientColor = color;
		m_pAmbientColorMap = nullptr;
	}

	void CShader::setAmbientColor(const ptr_texture_t pMap)
	{
		m_pAmbientColorMap = pMap;
	}

	Vec3f CShader::getAmbientColor(const Ray& ray) const
	{
		return m_pAmbientColorMap ? m_pAmbientColorMap->getTexel(ray) : m_ambientColor;
	}

	// ============================================== Diffuse Color ==============================================
	void CShader::setDiffuseColor(const Vec3f& color)
	{
		m_diffuseColor =  color;
		m_pDiffuseColorMap = nullptr;
	}
	
	void CShader::setDiffuseColor(const ptr_texture_t pColorMap)
	{
		m_pDiffuseColorMap = pColorMap;
	}

	Vec3f CShader::getDiffuseColor(const Ray& ray) const
	{
		Vec3f res = m_diffuseColor;
#ifdef DEBUG_MODE
		Vec3f normal = ray.hit->getNormal(ray);			// normal
		bool inside = normal.dot(ray.dir) > 0;			// true if normal points outward the ray origin
		res = inside ? RGB(255, 0, 0) : RGB(0, 0, 255);
#endif
		return m_pDiffuseColorMap ? m_pDiffuseColorMap->getTexel(ray) : res;
	}


	// ============================================== Specular Level ==============================================
	void CShader::setSpecularLevel(float level)
	{
		m_specularLevel = level;
	}

	void CShader::setSpecularLevel(const ptr_texture_t pMap)
	{
		m_pSpecularLevelMap = pMap;
	}

	float CShader::getSpecularLevel(const Ray& ray) const
	{
		return m_pSpecularLevelMap ? m_pSpecularLevelMap->getTexel(ray)[0] : m_specularLevel;
	}

	// ============================================== Bump Map ==============================================
	void CShader::setBumpMap(const ptr_texture_t pBumpMap, float amount) 
	{
		m_bumpAmount = amount;
		//m_pBumpMap = pBumpMap;
		Mat a, b;

		Sobel(*pBumpMap, a, CV_32F, 1, 0, 1);
		Sobel(*pBumpMap, b, CV_32F, 0, 1, 1);

		m_pBumpMap_u = std::make_shared<CTexture>(a);
		m_pBumpMap_v = std::make_shared<CTexture>(b);
	}

	std::optional<std::pair<float, float>> CShader::getBump(const Ray& ray) const
	{
		if (m_pBumpMap_u) {
			Vec2f uv = ray.hit->getTextureCoords(ray);
			float du = m_pBumpMap_u->getTexel(uv)[0];
			float dv = m_pBumpMap_v->getTexel(uv)[0];
			return std::make_pair(du, dv);
		} else return std::nullopt;
		
	}

	//float CShader::getBumpU(const Ray& ray) const
	//{
	//	if (m_pBumpMap_u) return m_pBumpMap_u->getTexel(ray.hit->getTextureCoords(ray))[0];			// bitmap texture		
	//	else			return 0;
	//}

	//float CShader::getBumpV(const Ray& ray) const
	//{
	//	if (m_pBumpMap_v) return m_pBumpMap_v->getTexel(ray.hit->getTextureCoords(ray))[0];			// bitmap texture		
	//	else			return 0;
	//}

}


