#pragma once

#include "IShader.h"
#include "CosineSampler.h"
#include "Scene.h"
#include "ray.h"

namespace rt {
	class CShaderAmbientOccluson : public IShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 * @param direction Direction of ambient light
		 * @param radius size of hamisphere to search for occlusion
		 * @param nSamples Points sampled in hemisphere
		 */
		DllExport CShaderAmbientOccluson(CScene& scene, Vec3f direction, float radius = 0.3f, int nSamples = 40)
			: m_scene(scene)
			, m_direction(normalize(direction))
			, m_radius(radius)
		{
			m_pSampler = std::make_shared <CosineSampler>(nSamples, true);
			m_nSamples = m_pSampler->getNumSamples();
		}
		DllExport virtual ~CShaderAmbientOccluson(void) = default;
			//DllExport virtual Vec3f shade2(const Ray& ray) const override
			//{
			//	//return Vec3f::all(1);
			//	float occlusion=0;
			//	Vec3f normal = ray.hit->getNormal(ray);								
			//	//if (normal.dot(ray.dir) > 0) normal = -normal;						
			//	const auto tangents = getRandomTangents_2(normal);
			//	for (size_t s = 0; s < m_nSamples; s++)
			//	{
			//		Vec3f n = normal;
			//		Vec2f sample = m_pSampler->getNextSample();
			//		Vec3f disp = sample.val[0] * tangents.first + sample.val[1] * tangents.second;
			//		n = normalize(n + disp);
			//		Ray E;
			//		E.org = ray.hitPoint();
			//		E.dir = n;
			//		float d = m_scene.rayTraceHitDistance(E);
			//		//occlusion += d < m_radius ? 1 - n.dot(normal) : 0;
			//		occlusion += d < m_radius ? (1 - n.dot(normal)) : 0; //(1 - n.dot(-m_direction)) *

			//	}
			//	return Vec3f::all(1) * (1.0f - occlusion / m_nSamples) ;// *m_direction.dot(-normal);

			//}

		DllExport virtual Vec3f shade(const Ray& ray) const override
		{
			float occlusion = 0;
			Vec3f normal = ray.hit->getNormal(ray);
			//Axis used to convert samples on a hemisphere with Normal (0,0,1) to surface normal
			Vec3f rotationAxis = m_pSampler->getRotationAxis(normal);	
			for (size_t s = 0; s < m_nSamples; s++)
			{
				auto S = m_pSampler->getNextSample(rotationAxis);
				Ray E;
				E.org = ray.hitPoint();
				E.dir = S.sample;
				float d = m_scene.rayTraceDepth(E);
				//rayTraceDepth returns 0 if depth is INFINITY => no hit
				d = d == 0 ? INFINITY : d;
				occlusion += d < m_radius ? (S.sample.dot(normal))/(1-S.pdf) : 0.0f;
			}
			return Vec3f::all(1) *(1.0f - (occlusion / m_nSamples)) ;
		}
		
	private:
		CScene& m_scene;
		Vec3f m_direction;
		float m_radius;
		int m_nSamples;
		std::shared_ptr<CosineSampler>	m_pSampler;
	};
}