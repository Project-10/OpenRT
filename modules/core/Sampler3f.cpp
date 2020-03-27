#include "Sampler3f.h"
#include "macroses.h"

namespace rt 
{
	namespace {

		// Rotate V by pi about rotationAxis. 
		// Rodrigues rotation formular with theta = pi and adapted to unit vectors.
		// 		Ref: <a href="https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula">Wikipedia</a>
		// param rotationAxis unit vector for axis of rotation
		// param v unit vector
		// return Vec3f v rotated by pi about rotationAxis
		Vec3f rodriguesRotationEqn(Vec3f sample, Vec3f rotationAxis) {
			return -1 * sample + rotationAxis * (rotationAxis.dot(sample) * 2);
		}

		// Vector use to rotate [0,0,1] by pi to get Normal using Rodrigue's Rotation Equation
		Vec3f getRotationAxis(Vec3f Normal) {
			return normalize((Vec3f(0, 0, 1) + Normal) / 2);
		}
	}

	Vec3f CSampler3f::getHemisphereSample(const Vec2f& sample, const Vec3f& Normal, float m)
	{
		Vec3f hemisphereSample;
		switch (2) {
			case 0: hemisphereSample = CSampler::uniformSampleHemisphere(sample); break;
			case 1: hemisphereSample = CSampler::cosineSampleHemisphere(sample); break;
			case 2: hemisphereSample = CSampler::ourSampleHemisphere(sample, m); break;
		}
		Vec3f rotationAxis	= getRotationAxis(Normal);
		return rodriguesRotationEqn(hemisphereSample, rotationAxis);
	}
}