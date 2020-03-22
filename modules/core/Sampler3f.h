/**
 * @file Sampler3f.h
 * @brief # dimensional samplers
 * @version 0.1
 * @date 2020-03-11
 * 
 */
#pragma once
#include "types.h"
#include "random.h"
#include "Sampler.h"
namespace rt {
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
		//NOTE For CLightSky, use m >> 1 to reduce noise
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

		class CSampler3fTangent : public CSampler3f
	{
		public :
			//NOTE set s = 2 and d = -1 to use with CLightSky
			DllExport CSampler3fTangent( std::shared_ptr<CSampler> pSampler = std::make_shared<CSamplerStratified>(4, true, true),float s = 1.0f,float d = 0.0f)
			:CSampler3f(pSampler)
			,m_s(s)
			,m_d(d){}

			DllExport CSampler3fTangent( int nSamples ,float s = 1.0f,float d = 0.0f)
			:CSampler3f(std::make_shared<CSamplerStratified>(nSamples, true, true))
			,m_s(s)
			,m_d(d){}

			DllExport virtual Vec3f getNextSample(Vec3f Normal);
		protected :
			std::pair<Vec3f, Vec3f> getRandomTangents(Vec3f normal);
		private :
			float m_s;
			float m_d;

	};
}