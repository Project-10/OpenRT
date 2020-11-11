// StratifiedSampler class
// Written by Sergey Kosov in 2019 for Project X
#pragma once

#include "Sampler.h"

namespace rt {
	// ================================ Stratified Sampler Class ================================
	/**
	 * @brief Stratified Sampler class
	 * @note This class is not thread-safe
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CSamplerStratified : public CSampler {
	public:
		/**
		* @brief Constructor
		* @param nSamples Square root of number of samples in one series
		* @param isRenewable Flag indicating whether the series should be renewed after exhaustion
		* @param jitter Flag indicating if the samples shoild be jittered within the corresponding stratae
		*/
		DllExport CSamplerStratified(size_t nSamples, bool isRenewable = true, bool jitter = true)
			: CSampler(nSamples, isRenewable)
			, m_jitter(jitter)
		{}
		DllExport virtual ~CSamplerStratified(void) = default;


	protected:
		DllExport virtual void generateSeries(std::vector<Vec2f>& samples) const override;


	private:
		const bool m_jitter;		//< Flag indicating if the samples shoild be jittered within the corresponding stratae
	};
}