#include "BRDFChrome.h"
#include "random.h"

namespace {
	inline Vec3f Reflect(const Vec3f& wo, const Vec3f& n) {
		return -wo + 2 * wo.dot(n) * n;
	}
}

// Constructor
rt::CBRDFChrome::CBRDFChrome(ptr_sampler_t pSampler)
	: IBxDF(BxDFType::reflection | BxDFType::glossy)
	, m_pSampler(pSampler)
{}

float  rt::CBRDFChrome::f(const Vec3f& wo, const Vec3f& wi) const 
{ 
	return 0; 
}

float rt::CBRDFChrome::Sample_f(const Vec3f& wo, Vec3f& wi) const 
{
	Vec2f sample = m_pSampler ? m_pSampler->getNextSample() : Vec2f(random::U<float>(), random::U<float>());
	Vec3f n = CSampler::uniformSampleHemisphere(sample, 25);
	wi = Reflect(wo, n);

	return wi[2] < 0 ? 0 : 1.0f;
}

size_t rt::CBRDFChrome::getNumSamples(void) const
{ 
	return m_pSampler ? m_pSampler->getNumSamples() : 1; 
}



