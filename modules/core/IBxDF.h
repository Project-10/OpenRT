// BRDF and BTDF functions Abstract Interface class
// Written by Sergey Kosov in 2025 for OpenRT.org
#pragma once

#include "types.h"

namespace rt {
	/// <summary>
	/// Types of the BxDF functions
	/// </summary>
	enum class BxDFType : byte {
		unset			= 0,		///< The default value
		reflection		= 1 << 0,	///< Recursive BRDF ray-tracing part
		transmission	= 1 << 1,	///< Recursive BSDF ray-tracing part
		diffuse			= 1 << 2,	///< Non-recursive BRDF part
		glossy			= 1 << 3,	///< Stochastic BxDF part
		specular		= 1 << 4	///< Non-recursive artificial specular part (Phong, Blinn, etc.)
	};

	inline BxDFType operator|(BxDFType lhs, BxDFType rhs) {
		return static_cast<BxDFType>(static_cast<byte>(lhs) | static_cast<byte>(rhs));
	}

	inline BxDFType& operator|=(BxDFType& lhs, BxDFType rhs) {
		lhs = static_cast<BxDFType>(static_cast<byte>(lhs) | static_cast<byte>(rhs));
		return lhs;
	}

	inline BxDFType operator&(BxDFType lhs, BxDFType rhs) {
		return static_cast<BxDFType>(static_cast<byte>(lhs) & static_cast<byte>(rhs));
	}


	// ================================ BxDF Interface Class ================================
	/**
	 * @brief Basic interface for the individual BRDF and BTDF functions 
	 * @details BRDFs and BTDFs share a common base class, BxDF. Because both have the exact same interface, 
	 * sharing the same base class reduces repeated code and allows some parts of the system to work with 
	 * BxDFs generically without distinguishing between BRDFs and BTDFs.
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class IBxDF
	{
	public:
		/**
		 * @brief Constructor
		 * @param type The type of the BxDF (@ref BxDFType)
		 * @param nSamples Number of samples for stochastic recursive ray-tracing (if applicable)
		 */
		DllExport IBxDF(BxDFType type, size_t nSamples) 
			: m_type(type)
			, m_nSamples(nSamples)
		{}
		DllExport IBxDF(const IBxDF&) = delete;
		DllExport virtual ~IBxDF(void) = default;
		DllExport const IBxDF& operator=(const IBxDF&) = delete;

		/**
		 * @brief Calculates value of the distribution function for the given pair of directions \b wo and \b wi
		 * @param wo Outgoing angle: the direction to the viewer (outgoing light)
		 * @param wi Incoming angle: the direction to the light source (incident light)
		 * @return The value of the distribution function for the given pair of directions.
		 */
		DllExport virtual float		f(const Vec3f& wo, const Vec3f& wi) const = 0;
		/**
		 * @brief Computes the direction of incident light \b wi given an outgoing direction \b wo and returns the value of the BxDF for the pair of directions.
		 * @details Not all BxDFs can be evaluated with the @ref f method. For example, perfectly specular objects like a mirror, glass, 
		 * or water only scatter light from a single incident direction into a single outgoing direction. Such BxDFs are best described 
		 * with delta distributions that are zero except for the single direction where light is scattered. These BxDFs need special 
		 * handling in OpenRT, so we also provide this method. 
		 * This method is used both for handling scattering that is described by delta distributions as well as for randomly sampling 
		 * directions from BxDFs that scatter light along multiple directions; 
		 * @param[in] wo Outgoing angle: the direction to the viewer (outgoing light)
		 * @param[out] wi Incoming angle: the direction to the light source (incident light)
		 * @param[in] s The index of the sample to be used
		 * @returns The value of the BxDF for the pair of directions
		 */
		DllExport virtual float		Sample_f(const Vec3f& wo, Vec3f& wi, size_t s) const = 0;
		/**
		 * @brief Returns recommended number of samples for the particular BxDF to be estimated
		 * @details The usual value here is 1 for the BxDFs, which have recursive ray-tracing part (i.e. use @ref Sample_f method)
		 * and 0 for the BxDFs, which do not have ray-tracing part. The value may be larger than 1 if the BxDF is based on 
		 * the stochastic recursive ray-tracing (e.g. Chrome BSDF, etc.)
		 * @return The recommended number of samples
		 */
		DllExport size_t			getNumSamples(void) const { return m_nSamples; }
		/**
		 * @brief Returns the type of the BxDF
		 * @return The type of the BxDF
		 */
		DllExport BxDFType			getType(void) const { return m_type; } 
		/**
		 * @brief The utility method which determines if the BxDF matches the user-supplied type flags
		 * @retval true The flags match
		 * @retval false The flags do not match
		 */
		DllExport bool				MatchesFlags(BxDFType flags) const { return (m_type & flags) == m_type; }


	private:
		BxDFType	m_type;			///< The type of the BxDF
		size_t		m_nSamples;		///< The number of samples needed for the stochastic recursive ray-tracing part of the BxDF to be evaluated
	};


	// ============================== Inline functions ==============================
	// A set of functions to operate in LCS
	inline float CosTheta(const Vec3f& w) {
		return w[2];
	}

	inline float Cos2Theta(const Vec3f& w) {
		return w[2] * w[2];
	}

	inline float AbsCosTheta(const Vec3f& w) {
		return std::fabs(w[2]);
	}

	inline float Sin2Theta(const Vec3f& w) {
		return std::max(0.0f, 1.0f - Cos2Theta(w));
	}

	inline float SinTheta(const Vec3f& w) {
		return std::sqrtf(Sin2Theta(w));
	}

	inline float TanTheta(const Vec3f& w) {
		return SinTheta(w) / CosTheta(w);
	}
	
	inline float Tan2Theta(const Vec3f& w) {
		return Sin2Theta(w) / Cos2Theta(w);
	}

	inline float CosPhi(const Vec3f& w) {
		float sinTheta = SinTheta(w);
		return (sinTheta == 0) ? 1.0f : std::clamp(w[0] / sinTheta, -1.0f, 1.0f);
	}

	inline float SinPhi(const Vec3f& w) {
		float sinTheta = SinTheta(w);
		return (sinTheta == 0) ? 0.0f : std::clamp(w[1] / sinTheta, -1.0f, 1.0f);
	}

	inline float Cos2Phi(const Vec3f& w) {
		return CosPhi(w) * CosPhi(w);
	}
	
	inline float Sin2Phi(const Vec3f& w) {
		return SinPhi(w) * SinPhi(w);
	}

	inline Vec3f Reflect(const Vec3f& w, const Vec3f& n) {
		return -w + 2 * w.dot(n) * n;
	}
}