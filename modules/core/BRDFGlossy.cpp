#include "BRDFGlossy.h"
#include "random.h"

// Constructor
rt::CBRDFGlossy::CBRDFGlossy(float roughness, ptr_sampler_t pSampler)
	: IBxDF(BxDFType::reflection | BxDFType::glossy, m_pSampler ? m_pSampler->getNumSamples() : 1)
	, m_roughness(roughness)
	, m_pSampler(pSampler)
{}

float  rt::CBRDFGlossy::f(const Vec3f& wo, const Vec3f& wi) const 
{ 
	return 0; 
}

float rt::CBRDFGlossy::Sample_f(const Vec3f& wo, Vec3f& wi) const 
{
	float k = m_roughness * m_roughness * m_roughness;
	
	Vec2f sample = m_pSampler ? m_pSampler->getNextSample() : Vec2f(random::U<float>(), random::U<float>());
	Vec3f n = CSampler::uniformSampleHemisphere(sample, k);	// Randomly deviated normal
	wi = Reflect(wo, n);

	return wi[2] < Epsilon ? 0 : 1.0f;
}
