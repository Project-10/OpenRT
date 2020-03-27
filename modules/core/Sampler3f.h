/**
 * @file Sampler3f.h
 * @brief # dimensional samplers
 * @version 0.1
 * @date 2020-03-11
 * 
 */
#pragma once
#include "types.h"
#include "random.h"
#include "Sampler.h"
namespace rt {
	/**
	 *@brief Samples unit hemisphere using cosine sampling and return samples rotated to a surface normal
	 */	
	class CSampler3f {
	public :
		DllExport CSampler3f(std::shared_ptr<CSampler> pSampler = std::make_shared<CSamplerRandom>(4, true), float m = 1) : m_pSampler(pSampler), m_m(m) {}
		DllExport ~CSampler3f(void) = default;

		DllExport size_t getNumSamples(void) const { return m_pSampler->getNumSamples(); }
		
		/**
		 * @brief Get the next sample rotated around the normal
		 * @param Normal
		 * @return Sample
		 *
		 */
		DllExport Vec3f getNextSample(Vec3f normal);
		
	
	private:
		std::shared_ptr<CSampler> m_pSampler;
		float m_m;
	};
}