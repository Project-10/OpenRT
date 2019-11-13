#include "Sampler.h"
#include "macroses.h"

namespace rt {
	thread_local size_t CSampler::m_idx = 0;
	
	// Constructor
	CSampler::CSampler(size_t nSamples, bool isRenewable)
		: m_vSamples(nSamples* nSamples)
		, m_renewable(isRenewable)
	{
		m_idx = 0;
	}

	// Destructor
	CSampler::~CSampler(void) {
		RT_ASSERT(m_idx == 0);
	}

	Vec2f CSampler::getNextSample(void) {
		if (m_vSamples.empty())
			return Vec2f::all(0.5f);

		if (m_idx == 0 && m_needGeneration) {
			m_needGeneration = m_renewable;
			generate();
		}

		Vec2f res = m_vSamples[m_idx];
		
		if (m_idx < m_vSamples.size() - 1) 	m_idx++;
		else 								m_idx = 0;

		return res;
	}
}