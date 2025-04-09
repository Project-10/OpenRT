#include "BRDFPhong.h"

namespace {
	Vec3f Reflect(const Vec3f& w, const Vec3f& n) {
		return -w + 2 * w.dot(n) * n;
	}
}

float rt::CBRDFPhong::f(const Vec3f& wo, const Vec3f& wi) const {
	// Only specular component

	const Vec3f n = Vec3f(0, 0, 1.0f);
	const Vec3f r = Reflect(wo, n);
	
	float cosLightReflect = std::max(0.0f, r.dot(wi));
	float specular = std::powf(cosLightReflect, m_ke);
	
	return specular;
}