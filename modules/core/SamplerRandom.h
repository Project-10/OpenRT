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
		* @param isRenewable Flag indicating whether the series should be renewed after exhaustion
		*/
		DllExport CSamplerRandom(size_t nSamples, bool isRenewable = true) : CSampler(nSamples, isRenewable) {}
		DllExport virtual ~CSamplerRandom(void) = default;


	protected:
		DllExport virtual void generateSeries(std::vector<Vec2f>& samples) const override;
	};
}