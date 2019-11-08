#include "Sampler.h"

namespace rt {
	thread_local size_t CSampler::m_idx = 0;
	
	Vec2f CSampler::getNextSample(void) {
		if (m_vSamples.empty())
			return Vec2f::all(0.5f);

		int idx = m_idx % m_vSamples.size();
		if (!m_idx || (!idx && m_renewable))
			generate();
		m_idx++;

		return m_vSamples[idx];
	}
}