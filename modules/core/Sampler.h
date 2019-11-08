// Sampler interface class
// Written by Sergey Kosov in 2019 for Project X
#pragma once

#include "types.h"
#include "random.h"	// TODO: delete

namespace rt {
	class CSampler {
	public:
		DllExport CSampler(size_t nSamples, bool isRenewable)
			: m_vSamples(nSamples* nSamples)
			, m_renewable(isRenewable)
		{}
		DllExport CSampler(const CSampler&) = delete;
		DllExport virtual ~CSampler(void) = default;
		DllExport const CSampler& operator=(const CSampler&) = delete;
		
		DllExport virtual Vec2f getNextSample(void);
		DllExport size_t		getNumSamples(void) const { return m_vSamples.size(); }
		
	
	protected:
		virtual void generate(void) = 0;

	
	protected:
		std::vector<Vec2f> 	m_vSamples;
	
		
	private:
		const bool					m_renewable;
		thread_local static size_t	m_idx;
	};

	class CSamplerRandom : public CSampler {
	public:
		DllExport CSamplerRandom(size_t nSamples, bool isRenewable) : CSampler(nSamples, isRenewable) {}
		DllExport virtual ~CSamplerRandom(void) = default;
	
	protected:
		virtual void generate(void) override
		{
			for (auto& sample : m_vSamples)
				for (int i = 0; i < 2; i++)
					sample.val[i] = random::U<float>();
		}
	};

	
	class CSamplerStratified : public CSampler {
	public:
		DllExport CSamplerStratified(size_t nSamples, bool isRenewable = false, bool jitter = false)
			: CSampler(nSamples, isRenewable)
			, m_jitter(jitter)
		{}
		DllExport virtual ~CSamplerStratified(void) = default;
	
		
	protected:
		virtual void generate(void) override
		{
			size_t nSamples = sqrt(m_vSamples.size());
			float delta = 1.0f / nSamples;
			
			int s = 0;
			for (size_t y = 0; y < nSamples; y++)
				for (size_t x = 0; x < nSamples; x++) {
					float fx = static_cast<float>(x) + (m_jitter ? random::U<float>() : 0.5f);
					float fy = static_cast<float>(y) + (m_jitter ? random::U<float>() : 0.5f);
					m_vSamples[s] = delta * Vec2f(fx, fy);
					s++;
				}
		}
		
	private:
		bool m_jitter;
	};
}
