// Phong BRDF class
// Written by Dr. Sergey G. Kosov in 2025 for OpenRT.org
#include "BxDF.h"

#pragma once

namespace rt {
	// ================================ Phong BRDF Interface Class ================================
	/**
	 * @brief Phong specular BRDF interface class
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CBRDFPhong : public CBxDF
	{
	public:
		/**
		 * @brief Constructor 
		 * @param ke The shininess exponent
		 */
		DllExport CBRDFPhong(float ke);
		DllExport virtual ~CBRDFPhong(void) = default;

		DllExport float		f(const Vec3f& wo, const Vec3f& wi) const override;


	private:
		float m_ke;    				///< The shininess exponent
	};
}