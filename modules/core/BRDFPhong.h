// Phong BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "IBxDF.h"

#pragma once

namespace rt {

	// ================================ Phong BRDF Interface Class ================================
	/**
	 * @brief Phong specular BRDF interface class
	 * @ingroup moduleBxDF
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFPhong : public IBxDF
	{
	public:
		DllExport CBRDFPhong(float ke) 
			: IBxDF(BxDFType::specular)
			, m_ke(ke) 
		{}
		DllExport virtual ~CBRDFPhong(void) = default;

		DllExport virtual float f(const Vec3f& wo, const Vec3f& wi) const override;


	private:
		float m_ke;    				///< The shininess exponent
	};
}