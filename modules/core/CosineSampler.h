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
	*
	*@brief Samples unit hemisphere using cosine sampling and return samples rotated to a surface normal
	*/
	class CosineSampler
	{
	public:
		DllExport CosineSampler(size_t nSamples, bool isRenewable)
			: m_nSamples(nSamples), m_renewable(isRenewable), m_vSamples(m_nSamples)
		{
			m_idx = 0;
		}
		DllExport virtual ~CosineSampler(void) {
			RT_ASSERT(m_idx == 0);
		}
		/**
		 * @brief Get the next sample rotated by pi about the rotationAxis 
		 * @param rotationAxis 
		 * @return Sample Sample and the probabilty of getting that sample
		 * 
		 */
		Sample getNextSample(Vec3f rotationAxis);
		//The probability of a  sample being chosen
		float pdf(Vec3f sample);
		//Vector use to rotate [0,0,1] by pi to get Normal using Rodrigue's Rotation Equation
		Vec3f getRotationAxis(Vec3f Normal) { return normalize((Vec3f(0, 0, 1) + Normal) / 2); }
		DllExport size_t getNumSamples(void) const { return m_nSamples; }


	protected:
		//generate samples on a unit hemishphere
		 void generate(void);
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

	private:
		size_t m_nSamples;
		bool m_renewable;
		bool m_needGeneration = true;
		std::vector<Vec3f> m_vSamples;
#ifdef ENABLE_PPL
		thread_local static size_t	m_idx;
#else
		size_t 						m_idx = 0;
#endif

	};

#ifdef ENABLE_PPL
	thread_local size_t CosineSampler::m_idx = 0;
#endif
	Sample CosineSampler::getNextSample(Vec3f k) 
	{
		if (m_vSamples.empty())
			return Sample{ Vec3f::all(0.5f) ,0};

		if (m_idx == 0 && m_needGeneration) {
			m_needGeneration = m_renewable;
			generate();
		}

		Vec3f res = m_vSamples[m_idx];

		if (m_idx < m_vSamples.size() - 1) 	m_idx++;
		else 								m_idx = 0;

		return Sample{ rodriguesRotationEqn(k,res), pdf(res) };
	}

	void CosineSampler::generate(void)
	{
		for (auto& sample : m_vSamples)
		{
			float zeta_1 = random::U<float>();
			float zeta_2 = random::U<float>();
			sample = conv2cartesian(zeta_1, zeta_2);
		}

	}

	Vec3f CosineSampler::conv2cartesian(float zeta_1, float zeta_2)
	{
		float x = cosf(2 * Pif * zeta_2) * sqrt(zeta_1);
		float y = sinf(2 * Pif * zeta_2) * sqrt(zeta_1);
		float z = sqrt(1 - zeta_1);
		Vec3f ret(x, y, z);
		return normalize(ret);
	}

	float CosineSampler::pdf(Vec3f sample)
	{
		float z = abs(sample[2]);
		float theta = acosf(z);
		return (1 / Pif) * (z)*sinf(theta);
	}

}