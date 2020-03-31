#pragma once

#include "ILight.h"
#include "Sampler.h"

namespace rt {
	/**
	 * @brief Area light sourse class
	 */
	class CLightArea : public ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @details The position and size of the area light source is given by the quadrangular luminous surface.
		 * This surface is defoned by 4 points in space: \b p1, \b p2, \b p3 and \b p4
		 * @param intensity The emission color and strength of the light source
		 * @param p0 The first point defining the quadrangular shape of the light source
		 * @param p1 The second point defining the quadrangular shape of the light source
		 * @param p2 The third point defining the quadrangular shape of the light source
		 * @param p3 The fourth point defining the quadrangular shape of the light source
		 * @param pSampler Pointer to the sampler to be used with the area light
		 */
		DllExport CLightArea(Vec3f intensity, Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3, std::shared_ptr<CSampler> pSampler = std::make_shared<CSamplerStratified>(4, true))
			: ILight(true)
			, m_pSampler(pSampler)
			, m_intensity(intensity)
			, m_p0(p0)
			, m_edge1(p1 - p0)
			, m_edge2(p3 - p0)
		{
			m_normal = m_edge1.cross(m_edge2);
			m_area = norm(m_normal);
			m_normal = normalize(m_normal);
		}

		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) override
		{
			Vec2f sample = m_pSampler->getNextSample();
			Vec3f position = m_p0 + sample.val[0] * m_edge1 + sample.val[1] * m_edge2;
			
			ray.dir = position - ray.org;
			ray.t = norm(ray.dir);
			ray.hit = nullptr;
			ray.dir = normalize(ray.dir);

			float cosN = -ray.dir.dot(m_normal) / ray.t;
			if (cosN <= 0.0f) return std::nullopt;
			float attenuation = m_area * cosN / (ray.t * ray.t);

			return attenuation * m_intensity;
		}

		DllExport virtual void sample_le(Ray& ray){
			Vec2f sample = m_pSampler->getNextSample();
			Ray.org = m_p0 + sample.val[0] * m_edge1 + sample.val[1] * m_edge2;
		}
		
		DllExport virtual size_t getNumberOfSamples(void) const override { return m_pSampler->getNumSamples(); }

		DllExport Vec3f getNormal(const Vec3f& position) const { return m_normal; }


	private:
		std::shared_ptr<CSampler> m_pSampler;
		Vec3f m_intensity;
		Vec3f m_p0;
		Vec3f m_edge1;
		Vec3f m_edge2;
		float m_area;
		Vec3f m_normal;
	};
}
