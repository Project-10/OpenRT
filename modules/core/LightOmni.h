// Omni Light Source class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ILight.h"

namespace rt {
	// ================================ Point Light Class ================================
	/**
	 * @brief Omnidirectional point light source class
	 * @ingroup moduleLight
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CLightOmni : public ILight
	{
	public:
		/**
		 * @brief Constructor
		 * @param intensity The emission color and strength of the light source
		 * @param org The position (origin) of the light source
		 * @param castShadow Flag indicatin whether the light source casts shadow
		 */
		DllExport CLightOmni(const Vec3f& intensity, const Vec3f& org, bool castShadow = true)
			: ILight(intensity, castShadow)
			, m_org(org)
		{}
		DllExport virtual ~CLightOmni(void) = default;

		DllExport virtual std::optional<Vec3f>	illuminate(Ray& ray) const override;
		DllExport virtual size_t				getNumSamples(void) const override { return 1; }
		
		// Accessors
		/**
		 * @brief Sets light source position (origin)
		 * @param org The position (origin) of the light source
		 */
		DllExport virtual void	setOrigin(const Vec3f& org) { m_org = org; }
		/**
		 * @brief Returns the position (origin) of the light source
		 * @return The position (origin) of the light source
		 */
		DllExport Vec3f			getOrigin(void) const { return m_org; }


	private:
		Vec3f m_org;		///< The light source origin
	};
}

