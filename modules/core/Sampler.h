// Sampler interface class
// Written by Sergey Kosov in 2019 for Project X
#pragma once

#include "types.h"

namespace rt {
	// ================================ Sampler Class ================================
	/**
	 * @brief Sampler abstract class
	 * @warning This class is not thread-safe
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
		* @details This function returns a pair of uniformly distributed random variables \f$(\xi_1, \xi_2)\f$ in square \f$[0; 1)^2\f$. 
		* Thus, it returs samples uniformly covering a unit square.
		* @return The next sample from a series
		*/
		DllExport Vec2f			getNextSample(void);
		/**
		* @brief Returns the number of samples in a series 
		* @return The number of samples in a series 
		*/
		DllExport size_t		getNumSamples(void) const { return MAX(1, m_vSamples.size()); }
		
		
		// ---------------- Static functions ----------------
		/**
		* @brief Transforms a uniform sampled square into a uniform sampled disc
		* @details This function uses the formulas \f[\begin{align} r&=\sqrt{\xi_1} \\ \theta&=2\pi\xi_2 \\ x&=r\cos{\theta} \\ y&=r\sin{\theta}\end{align}\f]
		* to transform between distributions.
		* @param sample The pair of random variables \f$(\xi_1, \xi_2)\f$ in square \f$[0; 1)^2\f$, \a e.g. achieved with getNextSample() method
		* @return A new pair of random variables \f$(x, y)\f$ sampling a unit disc with center in \f$(0, 0)\f$
		*/
		DllExport static Vec2f	uniformSampleDisk(const Vec2f& sample);
		/**
		* @brief Transforms a uniform sampled square into a uniform concentric sampled disc
		* @note Usually the resulting distribution achieved with this method is more uniform than the distribution achieved with uniformSampleDisk() method
		* @param sample The pair of random variables \f$(\xi_1, \xi_2)\f$ in square \f$[0; 1)^2\f$, \a e.g. achieved with getNextSample() method
		* @return A new pair of random variables \f$(x, y)\f$ sampling a unit disc with center in \f$(0, 0)\f$
		*/
		DllExport static Vec2f	concentricSampleDisk(const Vec2f& sample);
		/**
		* @brief Transforms a uniform sampled square into a uniform sampled hemisphere
		* @details This function uses the formulas \f[\begin{align} \phi&=\arccos{\xi_1} \\ \theta&=2\pi\xi_2 \\ x&=\sin{\phi}\cos{\theta} \\ y&=\sin{\phi}\sin{\theta} \\ z&=\cos{\phi} \end{align}\f]
		* to transform between distributions. The resulting probability of a sample is: \f[ p(\phi, \theta) = \frac{r}{\pi}\f].
		* @param sample The pair of random variables \f$(\xi_1, \xi_2)\f$ in square \f$[0; 1)^2\f$, \a e.g. achieved with getNextSample() method
		* @param m A coefficiet pushing the distribution toward the upper pole of the hemisphere. It modulates the z-value of resulting vector as \f$ z= \sqrt[\leftroot{-2}\uproot{2}{1+m}]{z} \f$
		* @return A new triple of random variables \f$(x, y, z)\f$ sampling a unit hemisphere with center in \f$(0, 0)\f$ 
		*/
		DllExport static Vec3f	uniformSampleHemisphere(const Vec2f& sample, float m = 0);
		/**
		* @brief Transforms a uniform sampled square into a uniform sampled n-sided regular polygon
		* @details This function samples from a triangle using the formula \f$P = (1 - sqrt(r1)) * A + (sqrt(r1) * (1 - r2)) * B + (sqrt(r1) * r2) * C \f$ 
		* (<a href="http://www.cs.princeton.edu/~funk/tog02.pdf">link</a>)
		* @param sample The pair of random variables \f$(\xi_1, \xi_2)\f$ in square \f$[0; 1)^2\f$
		* @param n Number of sides of the polygon 
		* @param m A random integer between 1 and n used to pick the triangle that the point will be sampled from 
		* @return A new pair of random variables \f$(x, y)\f$ 
		*/
		DllExport static Vec2f	uniformSampleRegularNgon(const Vec2f& sample, int n, int m);
		/**
		* @todo Implement this function
		*/
		DllExport static Vec3f	uniformSampleSphere(const Vec2f& sample);
		/**
		* @brief Transforms a uniform sampled square into a cosine-weighted sampled hemisphere@
		* @details In contrast to uniformSampleHemisphere() method, this function generates samples that are more likely to be close to the top of the hemisphere.
		* The resulting probability of a sample is \f[ p(\phi, \theta) = \cos{\phi}\frac{r}{\pi} \f].
		* @param sample The pair of random variables \f$(\xi_1, \xi_2)\f$ in square \f$[0; 1)^2\f$, \a e.g. achieved with getNextSample() method
		* @return A new triple of random variables \f$(x, y, z)\f$ sampling a unit hemisphere with center in \f$(0, 0)\f$ 
		*/
		DllExport static Vec3f	cosineSampleHemisphere(const Vec2f& sample);
		/**
		* @brief Transforms a 3D sample to World Coordinate System (WCS)
		* @details This finction transforms sampling from the coordinate system in which they were created to world space 
		* (in the shaded point local coordinate system whose up vector is aligned with \b normal)
		* @param sample The 3d of random variables, achieved with uniformSampleSphere() or uniformSampleHemisphere() methods
		* @param normal Normal to the surface in WCS
		* @return Sample
		*/
		DllExport static Vec3f	transformSampleToWCS(const Vec3f& sample, const Vec3f& normal);


	protected:
		/**
		* @brief Generates a new series of samples and fills \b samples container
		* @details Dependency Injection function that is called from getNextSample() and must be implemented in all derived classes
		* @param[in,out] samples The container for new samples
		*/
		virtual void generateSeries(std::vector<Vec2f>& samples) const = 0;

	
	private:
		std::vector<Vec2f> 			m_vSamples;					///< Samples container
		const bool					m_renewable;				///< Flag indicating whether the series should be renewed after exhaustion 
		bool						m_needGeneration = true;	///< Flag indicating whether the series of samples should be generated upon calling getNextSample() method
#ifdef ENABLE_PDP
		thread_local static size_t	m_idx;
#else
		size_t 						m_idx = 0;
#endif
	};
	using ptr_sampler_t = std::shared_ptr<CSampler>;
}
