#include "Sampler.h"
#include "macroses.h"

namespace rt {
	// ---------------- Static functions ----------------
	Vec2f CSampler::naiveSampleDisk(const Vec2f& sample) {
		float r = sample[0];
		float theta = 2 * Pif * sample[1];
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		return Vec2f(x, y);
	}
	
	// --------- from PBR book ---------
	Vec2f CSampler::uniformSampleDisk(const Vec2f& sample) {
		float r		= sqrtf(sample[0]);
		float theta = 2 * Pif * sample[1];
		float x		= r * cosf(theta);
		float y		= r * sinf(theta);
		return Vec2f(x, y);
	}

	// --------- from PBR book ---------
	Vec2f CSampler::concentricSampleDisk(const Vec2f& sample) {
		// Map uniform random numbers to [-1, 1]^2
		Vec2f s = 2 * sample - Vec2f::all(1);

		// Handle degeneracy at the origin
		if (s[0] == 0 && s[1] == 0) 
			return Vec2f::all(0);

		// Apply concentric mapping to point
		float theta, r;
		if (fabs(s[0]) > fabs(s[1])) {
			r = s[0];
			theta = 0.25f * Pif * s[1] / r;
		} else {
			r = s[1];
			theta = 0.5f * Pif - 0.25f * Pif * s[0] / r;
		}

		float x = r * cosf(theta);
		float y = r * sinf(theta);
		return Vec2f(x, y);
	}

	// --------- from PBR book ---------
	// ---------------------------------
	// float xi_1 = sample[0];
	// float xi_2 = sample[1];

	// float theta = acosf(xi_1);
	// float phi = 2 * Pif * xi_2;

	// float x = sinf(theta) * cosf(phi);
	// float y = sinf(theta) * sinf(phi);
	// float z = cosf(theta);
	Vec3f CSampler::uniformSampleHemisphere(const Vec2f& sample, float m)
	{
		float z = sample[0];
		z = powf(z, 1 / (m + 1));						// our improvement: to make the distribution more narrowed
		float r = sqrtf(max(0.0f, 1.0f - z * z));
		float phi = 2 * Pif * sample[1];
		float x = r * cosf(phi);
		float y = r * sinf(phi);
		return Vec3f(x, y, z);
	}

	// --------- from PBR book ---------
	Vec3f CSampler::uniformSampleSphere(const Vec2f& sample) 
	{
		RT_WARNING("This function is not implemented");
		return Vec3f();
	}

	// --------- from PBR book ---------
	Vec3f CSampler::cosineSampleHemisphere(const Vec2f& sample) 
	{
		Vec2f s = concentricSampleDisk(sample);
		float z = sqrtf(max(0.0f, 1.0f - s[0] * s[0] - s[1] * s[1]));
		return Vec3f(s[0], s[1], z);
	}

	Vec2f CSampler::uniformSampleRegularNgon(const Vec2f& s, size_t nSides, size_t side)
	{
		if (nSides == 0) return CSampler::concentricSampleDisk(s);
		
		RT_ASSERT(side > 0 && side <= nSides);
		
		float theta = 2 * Pif / nSides;
		Vec2f a(sinf(theta * (side - 1)), cosf(theta * (side - 1)));
		Vec2f b(sinf(theta * side), cosf(theta * side));
		Vec2f c = s[0] * a + (1.0f - s[0]) * b;
		return sqrtf(s[1]) * c;	
	}

	namespace {
		/**
		* @brief General Rodrigues' rotation formula
		* @details <a href="https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula">Rodrigues' rotation formula</a>
		* @param v Vector to be rotated
		* @param k The unit vector representing an axis of rotation
		* @param theta The rotation angle
		* @returns The rotated vector \b v
		*/
		Vec3f rodriguesRotation(const Vec3f& v, const Vec3f& k, float theta)
		{ 
			return v * cosf(theta) + k.cross(v) * sinf(theta) + k * k.dot(v) * (1.0f - cosf(theta));
		}

		/**
		* @brief Rodrigues' rotation formula for \f$ \theta = \pi \f$
		* @param v Vector to be rotated
		* @param k The unit vector representing an axis of rotation
		* @returns The rotated by Pi vector \b v
		*/
		Vec3f rodriguesRotationPi(const Vec3f& v, const Vec3f& k /* float theta = Pi */)
		{
			return -v + k * k.dot(v) * 2;
		}

	}

	Vec3f CSampler::transformSampleToWCS(const Vec3f& sample, const Vec3f& normal)
	{
		// Vector use to rotate [0,0,1] by pi to get Normal using Rodrigue's Rotation Equation
		Vec3f rotationAxis = normalize((Vec3f(0, 0, 1) + normal) / 2);
		return rodriguesRotationPi(sample, rotationAxis);
	}
}
