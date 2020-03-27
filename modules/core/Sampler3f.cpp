#include "Sampler3f.h"
namespace rt {
    Vec3f CSampler3fCosine::getNextSample(Vec3f Normal) 
	{
		Vec3f k  = getRotationAxis(Normal);
		Vec2f seed2f = m_pSampler->getNextSample();
		Vec3f sample3f = conv2cartesian(seed2f[0], seed2f[1]);
		return rodriguesRotationEqn(k,sample3f);
	}

	Vec3f CSampler3fCosine::conv2cartesian(float zeta_1, float zeta_2)
	{
		/*
		Samples in sperical coordinates :
			theta = acos((1 - zeta_1)^(1/(m+1))
			phi = 2*pi*zeta_2
		Samples to cartesian coordinates:
			let A = (1 - zeta_1)^(1/(m+1)
			x = sin(theta)*cos(phi) = sqrt(1 - A^2)*cos(2*pi*zeta_2)
			y = sin(theta)*sin(phi) = sqrt(1 - A^2)*sin(2*pi*zeta_2)
			z = cos(theta)			= A

		*/
		float A = powf(1 - zeta_1,1/(m+1));
		float x = cosf(2 * Pif * zeta_2) * sqrt(1 - powf(A,2));
		float y = sinf(2 * Pif * zeta_2) * sqrt(1 - powf(A,2));
		float z = A;
		Vec3f ret(x, y, z);
		return normalize(ret);
	}

	float CSampler3fCosine::pdf(Vec3f sample)
	{
		float z = abs(sample[2]);
		float theta = acosf(z);
		return (1 / Pif) * (z)*sinf(theta);
	}


	std::pair<Vec3f, Vec3f> CSampler3fTangent::getRandomTangents(Vec3f normal)
		{
			std::pair<Vec3f, Vec3f> res;
			float s1 = random::U<float>();
			float s2 = random::U<float>();

			if (fabs(normal.val[0]) > 0.1f)
				res.first = Vec3f(-(s1 * normal.val[1] + s2 * normal.val[2]) / normal.val[0], s1, s2);
			else if (fabs(normal.val[1]) > 0.1f)
				res.first = Vec3f(s1, -(s1 * normal.val[0] + s2 * normal.val[2] / normal.val[1]), s2);
			else
				res.first = Vec3f(s1, s2, -(s1 * normal.val[0] + s2 * normal.val[1]) / normal.val[2]);

			res.second = normal.cross(res.first);
			res.first = normalize(res.first);
			res.second = normalize(res.second);
			return res;
		}

	Vec3f CSampler3fTangent::getNextSample(Vec3f Normal)
	{
		Vec2f sample = m_pSampler->getNextSample();
		std::pair<Vec3f, Vec3f> tangents = getRandomTangents(Normal);
		Vec3f disp = (m_s * sample.val[0] + m_d) * tangents.first + (m_s * sample.val[1] + m_d) * tangents.second;
		return normalize(Normal + disp);
	}
}