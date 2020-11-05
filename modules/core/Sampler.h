// Sampler interface class
// Written by Sergey Kosov in 2019 for Project X
#pragma once

#include "types.h"

namespace rt {
	// ================================ Sampler Class ================================
	/**
	 * @brief Sampler abstract class
	 * @note This class is not thread-safe
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CSampler {
	public:
		/**
		* @brief Constructor
		* @param nSamples Square root of number of samples in one series
		* @param isRenewable Flag indicating whether the series should be renewed after exhaustion 
		*/
		DllExport CSampler(size_t nSamples, bool isRenewable);
		DllExport CSampler(const CSampler&) = delete;
		DllExport virtual ~CSampler(void);
		DllExport const CSampler& operator=(const CSampler&) = delete;
		
		/**
		* @brief Returns the next sample from a series
		* @details This function returns two random numbers in range [0; 1)
		* @return The next sample from a series
		*/
		DllExport Vec2f			getNextSample(void);
		/**
		* @brief Returns the number of samples in a series 
		* @return The number of samples in a series 
		*/
		DllExport size_t		getNumSamples(void) const { return MAX(1, m_vSamples.size()); }
		
		// static auxiliary functions
		DllExport static Vec2f	uniformSampleDisk(const Vec2f& sample);
		DllExport static Vec2f	concentricSampleDisk(const Vec2f& sample);
		DllExport static Vec3f	uniformSampleHemisphere(const Vec2f& sample);
		DllExport static Vec3f	uniformSampleSphere(const Vec2f& sample);
		DllExport static Vec3f	cosineSampleHemisphere(const Vec2f& sample);
		DllExport static Vec3f	ourSampleHemisphere(const Vec2f& sample, float m);


	protected:
		/**
		* @brief Generates a new series of samples and fills \b samples container
		* @detail Dependnacy Injection 
		* @param[in] samples The container for new samples
		*/
		DllExport virtual void generateSeries(std::vector<Vec2f>& samples) const = 0;

	
	private:
		std::vector<Vec2f> 			m_vSamples;					///<
		const bool					m_renewable;				///< Flag indicating whether the series should be renewed after exhaustion 
		bool						m_needGeneration = true;	///< Flag indicating whether the series of samples should be generated upon calling getNextSample() method
#ifdef ENABLE_PDP
		thread_local static size_t	m_idx;
#else
		size_t 						m_idx = 0;
#endif
	};

	using ptr_sampler_t = std::shared_ptr<CSampler>;

	

	// ================================ Random Sampler Class ================================
	/**
	 * @brief Random Sampler class
	 * @details Generates random samples uniformly covering a region [0; 1) x [0; 1)
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CSamplerRandom : public CSampler {
	public:
		/**
		* @brief Constructor
		* @param nSamples Square root of number of samples in one series
		* @param isRenewable Flag indicating whether the series should be renewed after exhaustion
		*/
		DllExport CSamplerRandom(size_t nSamples, bool isRenewable = false) : CSampler(nSamples, isRenewable) {}
		DllExport virtual ~CSamplerRandom(void) = default;
	

	protected:
		DllExport virtual void generateSeries(std::vector<Vec2f>& samples) const override;
	};



	// ================================ Stratified Sampler Class ================================
	/**
	 * @brief Stratified Sampler class
	 * @note This class is not thread-safe
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CSamplerStratified : public CSampler {
	public:
		/**
		* @brief Constructor
		* @param nSamples Square root of number of samples in one series
		* @param isRenewable Flag indicating whether the series should be renewed after exhaustion
		*/
		DllExport CSamplerStratified(size_t nSamples, bool isRenewable = false, bool jitter = false)
			: CSampler(nSamples, isRenewable)
			, m_jitter(jitter)
		{}
		DllExport virtual ~CSamplerStratified(void) = default;
	
		
	protected:
		DllExport virtual void generateSeries(std::vector<Vec2f>& samples) const override;


	private:
		const bool m_jitter;
	};
}
