#include "Sampler.h"
#include "macroses.h"

namespace rt {
#ifdef ENABLE_PDP
thread_local size_t CSampler::m_idx = 0;
#endif

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

	// ---------------- Static functions ----------------
	Vec2f CSampler::uniformSampleDisk(const Vec2f& sample) {
		RT_WARNING("This function is not implemented");
		return Vec2f();
	}

	Vec2f CSampler::concentricSampleDisk(const Vec2f& sample) {
		RT_WARNING("This function is not implemented");
		return Vec2f();
	}

	// --------- from PBR book ---------
	// ---------------------------------
	// float xi_1 = sample[0];
	// float xi_2 = sample[1];

	// float theta = acosf(xi_1);
	// float phi = 2 * Pif * xi_2;

	// float x = sinf(theta) * cosf(phi);
	// float y = sinf(theta) * sinf(phi);
	// float z = cosf(theta);
	Vec3f CSampler::uniformSampleHemisphere(const Vec2f& sample)
	{
		float z = sample[0];
		float r = sqrtf(max(0.0f, 1.0f - z * z));
		float phi = 2 * Pif * sample[1];
		float x = r * cosf(phi);
		float y = r * sinf(phi);
		return Vec3f(x, y, z);
	}

	Vec3f CSampler::uniformSampleSphere(const Vec2f& sample) {
		RT_WARNING("This function is not implemented");
		return Vec3f();
	}

	// --------- from PBR book ---------
	Vec3f CSampler::cosineSampleHemisphere(const Vec2f& sample) {
		Vec2f s = concentricSampleDisk(sample);
		float z = sqrtf(max(0.0f, 1.0f - s[0] * s[0] - s[1] * s[1]));
		return Vec3f(s[0], s[1], z);
	}

	// TODO: please compare with the uniformSampleHemisphere()
	Vec3f CSampler::ourSampleHemisphere(const Vec2f& sample, float m) {
		float z = powf(sample[0], 1 / (m + 1));
		float r = sqrtf(max(0.0f, 1.0f - z * z));
		float phi = 2 * Pif * sample[1];
		float x = r * cosf(phi);
		float y = r * sinf(phi);
		return Vec3f(x, y, z);
	}
}
