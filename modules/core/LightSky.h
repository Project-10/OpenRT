#pragma once

#include "ILight.h"
#include "Sampler3f.h"

namespace rt {
	/**
	 * @brief Sky light sourse class
	 * @details This class implements Ambient Occlusion idea
	 */
	class CLightSky : public ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param pSampler Pointer to the sampler to be used with the area light
		 */
		DllExport CLightSky(Vec3f intensity, float radius = std::numeric_limits<float>::infinity(), std::shared_ptr<CSampler> pSampler = std::make_shared<CSamplerStratified>(4, true, true), bool castShadow = true)
			: ILight(castShadow)
			, m_intensity(intensity)
			, m_radius(radius)
			, m_pSampler(pSampler)
		{}

		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) override
		{
			ray.t = 0;
			Vec3f normal = ray.hit->getNormal(ray);												// normal to the object from which the ray was casted
			ray.dir = CSampler3f::getHemisphereSample(m_pSampler->getNextSample(), normal, 1);	// sample the hemisphere in respect to the object's normal
	
			// ray towards point light position
			ray.hit = nullptr;
			ray.t = m_radius;
			
			float cos_a = ray.dir.dot(normal);													// angle between the object's normal and sample ray
			if (cos_a > 0) return m_intensity / cos_a;
			return std::nullopt;
		}

		DllExport virtual std::optional<Photon> sample_le(void) override{
			return std::nullopt;
		}
		DllExport virtual size_t getNumberOfSamples(void) const override { return m_pSampler->getNumSamples(); }



	private:
		Vec3f m_intensity;
		float m_radius;
		std::shared_ptr<CSampler> m_pSampler;
	};
}
