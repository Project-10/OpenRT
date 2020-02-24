#pragma once

#include "IShader.h"
#include "Sampler.h"
#include "Scene.h"
#include "ray.h"

namespace rt {
	//namespace {
		std::pair<Vec3f, Vec3f> getRandomTangents_2(Vec3f normal)
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

	class CShaderAmbientOccluson : public IShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 */
		DllExport CShaderAmbientOccluson(CScene& scene, Vec3f direction, float radius = 3.0f, int nSamples = 8)
			: m_scene(scene)
			, m_direction(direction)
			, m_radius(radius)
		{
			m_pSampler = std::make_shared <CSamplerStratified>(nSamples, true, true);// 
			m_nSamples = m_pSampler->getNumSamples();
		}
		DllExport virtual ~CShaderAmbientOccluson(void) = default;
		DllExport virtual Vec3f shade(const Ray& ray) const override
		{
			float occlusion=0;
			Vec3f normal = ray.hit->getNormal(ray);								
			if (normal.dot(ray.dir) > 0) normal = -normal;						
			const auto tangents = getRandomTangents_2(normal);
			for (size_t s = 0; s < m_nSamples; s++)
			{
				Vec3f n = normal;
				Vec2f sample = m_pSampler->getNextSample();
				Vec3f disp = sample.val[0] * tangents.first + sample.val[1] * tangents.second;
				n = normalize(n + disp);
				Ray E;
				E.org = ray.hitPoint();
				E.dir = n;
				float d = m_scene.rayTraceDepth(E);
				occlusion += d < m_radius ? 1 : 0;
			}
			return Vec3f::all(1)*(1.0f / m_nSamples) * occlusion;

		}
	private:
		CScene& m_scene;
		Vec3f m_direction;
		float m_radius;
		int m_nSamples;
		std::shared_ptr<CSampler>	m_pSampler;
	};
}