#include "BRDFLambertian.h"

float rt::CBRDFLambertian::f(const Vec3f&, const Vec3f&) const {
	return InvPif;
}