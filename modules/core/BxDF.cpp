#include "BxDF.h"
#include "Sampler.h"
#include "macroses.h"

float rt::CBxDF::Sample_f(const Vec3f& wo, Vec3f& wi, size_t s) const {
	RT_WARNING("Default implementation of rt::CBxDF::Sample_f");
	
	// cosine-sample the hemisphere, flipping the directions if necessary
	Vec2f sample; // = m_pSampler ? m_pSampler->getNextSample(s) : Vec2f(random::U<float>(), random::U<float>());
	wi = CSampler::cosineSampleHemisphere(sample);
	if (wo[2] < 0) wi[2] *= -1.0f;
	
	float pdf = AbsCosTheta(wi) * InvPif;
	
	return f(wo, wi);
}