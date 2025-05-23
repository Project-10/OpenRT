#include "BRDFGlossy.h"
#include "random.h"

// Constructor
rt::CBRDFGlossy::CBRDFGlossy(float roughness, ptr_sampler_t pSampler)
	: CBxDF(BxDFType::reflection | BxDFType::glossy, pSampler ? pSampler->getNumSamples() : 1)
	, m_roughness(roughness)
	, m_pSampler(pSampler)
{}

float  rt::CBRDFGlossy::f(const Vec3f& wo, const Vec3f& wi) const 
{ 
	return 0; 
}

float rt::CBRDFGlossy::Sample_f(const Vec3f& wo, Vec3f& wi, size_t s) const
{
	Vec2f sample = m_pSampler ? m_pSampler->getNextSample(s) : Vec2f(random::U<float>(), random::U<float>());
	Vec3f n = CSampler::uniformSampleHemisphere(sample, m_roughness);	// Randomly deviated normal
	wi = Reflect(wo, n);

	return wi[2] < Epsilon ? 0 : 1.0f;
}
