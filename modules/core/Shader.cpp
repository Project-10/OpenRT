
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

	void CShader::setAmbientColor(const ptr_texture_t pMap, float amount)
	{
		m_pAmbientColorMap = pMap;
		m_ambientAmount = amount;
	}

	Vec3f CShader::getAmbientColor(const Ray& ray) const
	{
		return m_pAmbientColorMap ? m_ambientAmount * m_pAmbientColorMap->getTexel(ray) : m_ambientColor;
	}

	// ============================================== Diffuse Color ==============================================
	void CShader::setDiffuseColor(const Vec3f& color)
	{
		m_diffuseColor =  color;
		m_pDiffuseColorMap = nullptr;
	}
	
	void CShader::setDiffuseColor(const ptr_texture_t pMap, float amount)
	{
		m_pDiffuseColorMap = pMap;
		m_diffuseAmount = amount;
	}

	Vec3f CShader::getDiffuseColor(const Ray& ray) const
	{
		Vec3f res = m_diffuseColor;
#ifdef DEBUG_MODE
		Vec3f normal = ray.hit->getNormal(ray);			// normal
		bool inside = normal.dot(ray.dir) > 0;			// true if normal points outward the ray origin
		res = inside ? RGB(255, 0, 0) : RGB(0, 0, 255);
#endif
		if (m_pDiffuseColorMap) {
			res = m_diffuseAmount < 1.0f 
				? m_diffuseAmount * m_pDiffuseColorMap->getTexel(ray) + (1.0f - m_diffuseAmount) * res
				: m_pDiffuseColorMap->getTexel(ray);
		}
		return res;
	}


	// ============================================== Specular Color ==============================================
	void CShader::setSpecularColor(const Vec3f& color)
	{
		m_specularColor = color;
	}

	void CShader::setSpecularColor(const ptr_texture_t pMap, float amount)
	{
		m_pSpecularColorMap = pMap;
		m_specularAmount = amount;
	}

	Vec3f CShader::getSpecularColor(const Ray& ray) const
	{
		return m_pSpecularColorMap ? m_specularAmount * m_pSpecularColorMap->getTexel(ray) : m_specularColor;
	}

	// ============================================= Reflection Color =============================================
	void CShader::setReflectColor(const Vec3f& color) {
		m_reflectColor = color;
	}

	void CShader::setReflectColor(const ptr_texture_t pColorMap, float amount) {
		m_pReflectColorMap = pColorMap;
		m_reflectAmount = amount;
	}

	Vec3f CShader::getReflectColor(const Ray& ray) const
	{
		return m_pReflectColorMap ? m_reflectAmount * m_pReflectColorMap->getTexel(ray) : m_reflectColor;
	}

	// ============================================== Bump Map ==============================================
	void CShader::setBumpMap(const ptr_texture_t pBumpMap, float amount) 
	{
		m_bumpAmount = amount;
		//m_pBumpMap = pBumpMap;
		Mat a, b;

		Sobel(*pBumpMap, a, CV_32F, 1, 0, 3);
		Sobel(*pBumpMap, b, CV_32F, 0, 1, 3);

		m_pBumpMap_u = std::make_shared<CTexture>(a);
		m_pBumpMap_v = std::make_shared<CTexture>(b);
	}

	std::optional<std::pair<float, float>> CShader::getBump(const Ray& ray) const
	{
		if (m_pBumpMap_u) {
			float du = m_pBumpMap_u->getTexel(ray)[0];
			float dv = m_pBumpMap_v->getTexel(ray)[0];
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

	// ================================================= Opacity =================================================
	void CShader::setOpacity(float opacity) 
	{ 
		m_opacity = MAX(0, MIN(1, opacity)); 
	}

	void CShader::setOpacity(const ptr_texture_t pMap, float amount)
	{
		m_pOpacityMap = pMap;
		m_opacityAmount = amount;
	}

	float CShader::getOpacity(const Ray& ray) const
	{ 
		return m_pOpacityMap ? m_pOpacityMap->getTexel(ray)[0] : m_opacity;
	}
}


