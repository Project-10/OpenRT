#pragma once

#include "ILight.h"
#include "Sampler.h"

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
			, m_pSampler(pSampler)
			, m_intensity(intensity)
			, m_radius(radius)
		{}

		//namespace {
		// TODO: Put in a utilities and merge with the code in CShaderChrome
		std::pair<Vec3f, Vec3f> getRandomTangents(Vec3f normal)
		{
			std::pair<Vec3f, Vec3f> res;
			float s1 = random::U<float>();
			float s2 = random::U<float>();

			if (fabs(normal.val[0]) > 0.1f)
				res.first = Vec3f(-(s1 * normal.val[1] + s2 * normal.val[2]) / normal.val[0], s1, s2);
			else if (fabs(normal.val[1]) > 0.1f)
				res.first = Vec3f(s1, -(s1 * normal.val[0] + s2 * normal.val[2] / normal.val[1]), s2);
			else
				res.first = Vec3f(s1, s2, -(s1 * normal.val[0] + s2 * normal.val[1]) / normal.val[2]);

			res.second = normal.cross(res.first);
			res.first = normalize(res.first);
			res.second = normalize(res.second);
			return res;
		}
		//}

		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) override
		{
			// TODO: Maybe optimize it using the cosine sampler
			Vec2f sample = m_pSampler->getNextSample();
			ray.t = 0;
			Vec3f normal = ray.hit->getNormal(ray);
			std::pair<Vec3f, Vec3f> tangents = getRandomTangents(normal);

			Vec3f disp = (2 * sample.val[0] - 1) * tangents.first + (2 * sample.val[1] - 1) * tangents.second;

	
			// ray towards point light position
			ray.hit = nullptr;
			ray.dir = normalize(normal + disp);
			ray.t = m_radius;
			
			return m_intensity;
		}

		DllExport virtual size_t getNumberOfSamples(void) const override { return m_pSampler->getNumSamples(); }

	private:
		std::shared_ptr<CSampler> m_pSampler;
		Vec3f m_intensity;
		float m_radius;
	};
}
