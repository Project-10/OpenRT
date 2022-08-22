
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
		if (m_pAmbientColorMap)
			if (m_pAmbientColorMap->isProcedural()) return m_pAmbientColorMap->getTexel(ray.hit->getSolidTextureCoords(ray));	// procedural texture
			else									return m_pAmbientColorMap->getTexel(ray.hit->getTextureCoords(ray));		// bitmap texture
		else										return m_ambientColor;														// color		
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
		if (m_pDiffuseColorMap)
			if (m_pDiffuseColorMap->isProcedural()) return m_pDiffuseColorMap->getTexel(ray.hit->getSolidTextureCoords(ray));	// procedural texture
			else									return m_pDiffuseColorMap->getTexel(ray.hit->getTextureCoords(ray));		// bitmap texture
		else										return res;																	// color
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
		if (m_pSpecularLevelMap)
			if (m_pSpecularLevelMap->isProcedural()) return m_pSpecularLevelMap->getTexel(ray.hit->getSolidTextureCoords(ray))[0];	// procedural texture
			else									 return m_pSpecularLevelMap->getTexel(ray.hit->getTextureCoords(ray))[0];		// bitmap texture
		else										 return m_specularLevel;														// color
	}
}
