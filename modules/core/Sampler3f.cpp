#include "Sampler3f.h"
namespace rt {
	namespace {

		Vec3f conv2cartesian(const Vec2f& sample, float m) {
			/*
			Samples in spherical coordinates :
				theta = acos((1 - zeta_1)^(1/(m+1))
				phi = 2*pi*zeta_2
			Samples to cartesian coordinates:
				let A = (1 - zeta_1)^(1/(m+1))
				x = sin(theta)*cos(phi) = sqrt(1 - A^2)*cos(2*pi*zeta_2)
				y = sin(theta)*sin(phi) = sqrt(1 - A^2)*sin(2*pi*zeta_2)
				z = cos(theta)			= A

			*/
			float zeta_1 = sample[0];	// Uniform distributed random number 1 in [0,1]
			float zeta_2 = sample[1];	// Uniform distributed random number 2 in [0,1]
			float A = powf(1 - zeta_1, 1 / (m + 1));
			float x = cosf(2 * Pif * zeta_2) * sqrt(1 - A * A);
			float y = sinf(2 * Pif * zeta_2) * sqrt(1 - A * A);
			float z = A;
			Vec3f ret(x, y, z);
			return normalize(ret);
		}
		
		// Rotate V by pi about rotationAxis. 
		// Rodrigues rotation formular with theta = pi and adapted to unit vectors.
		// 		Ref: <a href="https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula">Wikipedia</a>
		// param rotationAxis unit vector for axis of rotation
		// param v unit vector
		// return Vec3f v rotated by pi about rotationAxis
		Vec3f rodriguesRotationEqn(Vec3f rotationAxis, Vec3f v) {
			return -1 * v + rotationAxis * (rotationAxis.dot(v) * 2);
		}

		// Vector use to rotate [0,0,1] by pi to get Normal using Rodrigue's Rotation Equation
		Vec3f getRotationAxis(Vec3f Normal) { 
			return normalize((Vec3f(0, 0, 1) + Normal) / 2); 
		}
	}
	
	Vec3f CSampler3f::getNextSample(Vec3f Normal) 
	{
		Vec3f rotationAxis	= getRotationAxis(Normal);
		Vec2f sample		= m_pSampler->getNextSample();
		Vec3f sample3f		= conv2cartesian(sample, m_m);
		return rodriguesRotationEqn(rotationAxis, sample3f);
	}
}