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
		* @param jitter Flag indicating if the samples shoild be jittered within the corresponding stratae
		*/
		DllExport CSamplerStratified(size_t nSamples, bool jitter = true)
			: CSampler(nSamples)
			, m_jitter(jitter)
		{}
		DllExport virtual ~CSamplerStratified(void) = default;
		DllExport virtual Vec2f	getNextSample(size_t i) const override;

	private:
		const bool m_jitter;		//< Flag indicating if the samples shoild be jittered within the corresponding stratae
	};
}