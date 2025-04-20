// Random Sampler class
// Written by Sergey Kosov in 2019 for Project X
#pragma once

#include "Sampler.h"

namespace rt {
	// ================================ Random Sampler Class ================================
	/**
	* @brief Random Sampler class
	* @details Generates random samples uniformly covering a region [0; 1) x [0; 1)
	* @author Sergey G. Kosov, sergey.kosov@project-10.de
	*/
	class CSamplerRandom : public CSampler {
	public:
		/**
		* @brief Constructor
		* @param nSamples Square root of number of samples in one series
		*/
		DllExport CSamplerRandom(size_t nSamples) : CSampler(nSamples) {}
		DllExport virtual ~CSamplerRandom(void) = default;
		DllExport virtual Vec2f	getNextSample(size_t i) const override;
	};
}