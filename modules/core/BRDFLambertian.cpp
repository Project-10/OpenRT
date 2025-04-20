#include "BRDFLambertian.h"

rt::CBRDFLambertian::CBRDFLambertian(void) 
	: IBxDF(BxDFType::diffuse, 0) 
{}

float rt::CBRDFLambertian::f(const Vec3f&, const Vec3f&) const {
	return InvPif;
}

float rt::CBRDFLambertian::Sample_f(const Vec3f&, Vec3f&) const {
	return 0;
}