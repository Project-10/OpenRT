#include "BRDFBlinn.h"

rt::CBRDFBlinn::CBRDFBlinn(float ke)
	: IBxDF(BxDFType::specular, 0)
	, m_ke(ke)
{}

float rt::CBRDFBlinn::f(const Vec3f& wo, const Vec3f& wi) const 
{
	const Vec3f halfway = normalize(wi + wo);
	float cosHalfwayNormal = CosTheta(halfway);
	float specular = std::powf(cosHalfwayNormal, m_ke);

	return specular;
}

float rt::CBRDFBlinn::Sample_f(const Vec3f&, Vec3f&) const {
	return 0;
}