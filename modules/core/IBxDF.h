// BRDF and BTDF functions Abstract Interface class
// Written by Sergey Kosov in 2025 for OpenRT.org
#pragma once

#include "types.h"
#include "Ray.h"

namespace rt {
	enum class BxDFType : byte {
		unset			= 0,
		reflection		= 1 << 0,
		transmission	= 1 << 1,
		diffuse			= 1 << 2,
		glossy			= 1 << 3,
		specular		= 1 << 4
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
	 * @brief Basic BRDF / BTDF functions abstract interface class
	 * @ingroup moduleBxDF
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class IBxDF
	{
	public:
		DllExport IBxDF(BxDFType type) : m_type(type) {}
		DllExport IBxDF(const IBxDF&) = delete;
		DllExport virtual ~IBxDF(void) = default;
		DllExport const IBxDF& operator=(const IBxDF&) = delete;

		/**
		 * @brief Calculates value of the distribution function for the given pair of directions \a wo and \a wi
		 * @param wo The direction ot the light source (incoming light)
		 * @param wi The direction to the viewer (outgoing light)
		 * @return The value of the distribution function for the given pair of directions
		 */
		DllExport virtual float		f(const Vec3f& wo, const Vec3f& wi) const = 0;

		// This method will be needed for 
		DllExport virtual float		Sample_f(const Vec3f& wo, Vec3f& wi) const = 0;

		/**
		 * @brief Returns recommended number of samples for the particular light source implementation
		 * @return The recommended number of samples
		 */
		DllExport virtual size_t	getNumSamples(void) const = 0;

		DllExport BxDFType	getType(void) const { return m_type; } 
		DllExport bool		MatchesFlags(BxDFType flags) const { return (m_type & flags) == m_type; }


		private:
			BxDFType	m_type;
	};
}