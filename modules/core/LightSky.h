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
		DllExport CLightSky(Vec3f intensity, float radius = std::numeric_limits<float>::infinity(), std::shared_ptr<CSampler3f> dSampler = std::make_shared<CSampler3fTangent>())
			: ILight(true)
			, m_intensity(intensity)
			, m_radius(radius)
			,m_dSampler(dSampler)
		{}

		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) override
		{
			ray.t = 0;
			Vec3f normal = ray.hit->getNormal(ray);
			ray.dir = m_dSampler->getNextSample(normal);
	
			// ray towards point light position
			ray.hit = nullptr;
			ray.t = m_radius;
			
			return m_intensity;
		}
		DllExport virtual size_t getNumberOfSamples(void) const override { return m_dSampler->getNumSamples(); }



	private:
		Vec3f m_intensity;
		float m_radius;
		std::shared_ptr<CSampler3f> m_dSampler;
	};
}
