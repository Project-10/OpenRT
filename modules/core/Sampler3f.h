/**
 * @file Sampler3f.h
 * @brief # dimensional samplers
 * @version 0.1
 * @date 2020-03-11
 * 
 */
#pragma once

#include "types.h"
#include "Sampler.h"

namespace rt {
	/**
	 *@brief Samples unit hemisphere using cosine sampling and return samples rotated to a surface normal
	 */	
	class CSampler3f {
	private:
		CSampler3f(void) = delete;
	public:		
		/**
		 * @brief Get the next sample rotated around the normal
		 * @param Normal
		 * @return Sample
		 */
		DllExport static Vec3f getHemisphereSample(const Vec2f& sample, const Vec3f& normal, float m);
	};
}