/**
 * @file CosineSampler.h
 * @brief Cosine Hemisphere  Sampler
 * @version 0.1
 * @date 2020-03-11
 * 
 */
#pragma once
#include "types.h"
#include "random.h"
namespace rt {
	struct Sample
	{
		Vec3f sample;
		float pdf;
	};
	/*
	*@brief Returns Samples in 3d from the 2d CSampler Class
	*/
	class CSampler3f {
		public :
			DllExport CSampler3f(std::shared_ptr<CSampler> pSampler) : m_pSampler(pSampler) {}
			DllExport size_t getNumSamples(void) const {return m_pSampler->getNumSamples(); }
			DllExport virtual Vec3f getNextSample(Vec3f normal)=0;
		protected :
			std::shared_ptr<CSampler> m_pSampler;
	};

	/*
	*
	*@brief Samples unit hemisphere using cosine sampling and return samples rotated to a surface normal
	*/
	class CSampler3fCosine : public CSampler3f
	{
	public:
		DllExport CSampler3fCosine(float m = 1.0f,std::shared_ptr<CSampler> pSampler = std::make_shared<CSamplerRandom>(4, true))
			:CSampler3f(pSampler),m(m){}
		/**
		 * @brief Get the next sample rotated around the normal 
		 * @param Normal 
		 * @return Sample 
		 * 
		 */
		DllExport Vec3f getNextSample(Vec3f Normal) override;
		//The probability of a  sample being chosen
		float pdf(Vec3f sample);

	protected:
		 /**
		  * @brief utility function to convert sperical coordinate (samples) into cartesian coordinates
		  * 
		  * @param zeta_1 Uniform distributed random number 1 in [0,1]
		  * @param zeta_2 Uniform distributed random number 2 in [0,1]
		  * @return Vec3f  vector in Cartesian coordinates
		  */
		 Vec3f conv2cartesian(float zeta_1, float zeta_2);
		 //Rotate V by pi about axis k. 
		 /**
		  * @brief Rodrigues rotation formular with theta = pi and adapted to unit vectors. 
		  * 		Ref: <a href="https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula">Wikipedia</a> 
		  * 
		  * @param k unit vector for axis of rotation
		  * @param v unit vector 
		  * @return Vec3f v rotated by pi about axis k
		  */
		 Vec3f rodriguesRotationEqn(Vec3f k, Vec3f v) { return -1 * v + k * (k.dot(v) * 2); }
		 //Vector use to rotate [0,0,1] by pi to get Normal using Rodrigue's Rotation Equation
		Vec3f getRotationAxis(Vec3f Normal) { return normalize((Vec3f(0, 0, 1) + Normal) / 2); }

	private:
		float m;
	};

	Vec3f CSampler3fCosine::getNextSample(Vec3f Normal) 
	{
		Vec3f k  = getRotationAxis(Normal);
		Vec2f seed2f = m_pSampler->getNextSample();
		Vec3f sample3f = conv2cartesian(seed2f[0], seed2f[1]);
		//return Sample{ rodriguesRotationEqn(k,sample3f), pdf(sample3f) };
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

	class CSampler3fTangent : public CSampler3f
	{
		public :
			DllExport CSampler3fTangent( std::shared_ptr<CSampler> pSampler = std::make_shared<CSamplerStratified>(4, true, true))
			:CSampler3f(pSampler){}
			DllExport virtual Vec3f getNextSample(Vec3f Normal);
		protected :
			std::pair<Vec3f, Vec3f> getRandomTangents(Vec3f normal);

	};
		// TODO: Put in a utilities and merge with the code in CShaderChrome and Shader

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
		Vec3f disp = (2 * sample.val[0] - 1) * tangents.first + (2 * sample.val[1] - 1) * tangents.second;
		return normalize(Normal + disp);
	}
}