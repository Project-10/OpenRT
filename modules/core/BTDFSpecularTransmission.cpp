#include "BTDFSpecularTransmission.h"

// Constructor
 rt::CBTDFSpecularTransmission::CBTDFSpecularTransmission(float refractiveIndex)
	: IBxDF(BxDFType::transmission, 1)
	, m_refractiveIndex(refractiveIndex)
{ }

float rt::CBTDFSpecularTransmission::f(const Vec3f&, const Vec3f&) const 
{ 
	return 0; 
}

float rt::CBTDFSpecularTransmission::Sample_f(const Vec3f& wo, Vec3f& wi, size_t) const
{
	float cos_o = CosTheta(wo);

	float k = cos_o < 0 ? m_refractiveIndex : 1.0f / m_refractiveIndex;
	
	float sin2_o	= Sin2Theta(wo);	
	float sin2_i	= k * k * sin2_o;	
	if (sin2_i > 1)	{
		wi = Vec3f(-wo[0], -wo[1], wo[2]);
		return 1.0f;
	}
	float cos_i		= sqrtf(1.0f - sin2_i);
	if (cos_o < 0)
		cos_i = -cos_i;
	
	wi = normalize((k * cos_o - cos_i) * Vec3f(0, 0, 1) - k * wo);
	//wi = -k * wo;
	//wi[2] = -cos_i;
	//wi = Vec3f(-k * wo[0], -k * wo[1], -cos_i);

	return 1.0f;
}
