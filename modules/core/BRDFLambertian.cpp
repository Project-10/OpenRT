#include "BRDFLambertian.h"

rt::CBRDFLambertian::CBRDFLambertian(void) 
	: CBxDF(BxDFType::diffuse, 0) 
{}

float rt::CBRDFLambertian::f(const Vec3f&, const Vec3f&) const {
	return InvPif;
}
