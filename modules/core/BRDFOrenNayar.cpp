#include "BRDFOrenNayar.h"

// Constructor
rt::CBRDFOrenNayar::CBRDFOrenNayar(float sig) : IBxDF(BxDFType::diffuse)
{
	float sigma = sig * Pif / 180;
	float sigma2 = sigma * sigma;
	m_A = 1.0f - (sigma2 / (2.0f * (sigma2 + 0.33f)));
	m_B = 0.45f * sigma2 / (sigma2 + 0.09f);
}

namespace {
	inline float CosTheta(const Vec3f& w) {
		return w[2];
	}

	inline float Cos2Theta(const Vec3f& w) {
		return w[2] * w[2];
	}

	inline float AbsCosTheta(const Vec3f& w) {
		return std::fabs(w[2]);
	}

	inline float Sin2Theta(const Vec3f& w) {
		return std::max(0.0f, 1.0f - Cos2Theta(w));
	}

	inline float SinTheta(const Vec3f& w) {
		return std::sqrtf(Sin2Theta(w));
	}

	inline float CosPhi(const Vec3f& w) {
		float sinTheta = SinTheta(w);
		return (sinTheta == 0) ? 1.0f : std::clamp(w[0] / sinTheta, -1.0f, 1.0f);
	}

	inline float SinPhi(const Vec3f& w) {
		float sinTheta = SinTheta(w);
		return (sinTheta == 0) ? 0.0f : std::clamp(w[1] / sinTheta, -1.0f, 1.0f);
	}
}

float rt::CBRDFOrenNayar::f(const Vec3f& wo, const Vec3f& wi) const {
	float sinThetaI = SinTheta(wi);
	float sinThetaO = SinTheta(wo);

	// Compute cosine term of Oren–Nayar model
	float maxCos = 0;
	if (sinThetaI > 1e-4f && sinThetaO > 1e-4f) {	// TODO: Try Epsilon
		float sinPhiI = SinPhi(wi), cosPhiI = CosPhi(wi);
		float sinPhiO = SinPhi(wo), cosPhiO = CosPhi(wo);
		float dCos = cosPhiI * cosPhiO + sinPhiI * sinPhiO;
		maxCos = std::max(0.0f, dCos);
	}

	// Compute sine and tangent terms of Oren–Nayar model
	float sinAlpha, tanBeta;
	if (AbsCosTheta(wi) > AbsCosTheta(wo)) {
		sinAlpha = sinThetaO;
		tanBeta = sinThetaI / AbsCosTheta(wi);
	}
	else {
		sinAlpha = sinThetaI;
		tanBeta = sinThetaO / AbsCosTheta(wo);
	}

	float OrenNayar = m_A + m_B * maxCos * sinAlpha * tanBeta;
	return OrenNayar * InvPif;
}