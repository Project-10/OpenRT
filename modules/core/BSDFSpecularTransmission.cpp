#include "BSDFSpecularTransmission.h"

float rt::CBRDFSpecularTransmission::Sample_f(const Vec3f& wo, Vec3f& wi) const
{
	if (m_refractiveIndex == 1) {
		wi = -wo;
		return 1.0f;
	}

	// TODO: complete this implementation
	Vec3f normal = Vec3f(0, 0, 1);
	bool inside = true; // TODO: or false
	float k = inside ? m_refractiveIndex : 1.0f / m_refractiveIndex;
	
	float cos_alpha = wo.dot(normal);
	float sin_2_alpha = 1.0f - cos_alpha * cos_alpha;
	float k_2_sin_2_alpha = k * k * sin_2_alpha;
	if (k_2_sin_2_alpha <= 1) {
		float cos_beta = sqrtf(1.0f - k * k * sin_2_alpha);
		wi = normalize((k * cos_alpha - cos_beta) * normal + k * (-wo));
	}
	else {
		wi = Vec3f(-wo[0], -wo[1], wo[2]);	// reflected direction
	}
	return 1.0f;
}
