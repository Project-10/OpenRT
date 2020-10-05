// Basic ray structure
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"

namespace rt {
	class CScene;
	// ================================ Ray Structure ================================
	/**
	 * @brief Basic ray structure
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	struct Ray
	{
		Vec3f							org;												///< %Ray origin
		Vec3f							dir;												///< %Ray direction
		size_t 							counter;											///< Number of re-traces
		
		double							t		= std::numeric_limits<double>::infinity();	///< Current/maximum hit distance
		std::shared_ptr<const IPrim>	hit		= nullptr;									///< Pointer to currently closest primitive
		float							u		= 0;										///< Barycentric u coordinate
		float							v		= 0;										///< Barycentric v coordinate
		
		/**
		 * @brief Constructor
		 * @param _org %Ray origin
		 * @param _dir %Ray direction
		 * @param _counter Number of re-traces
		 */
		explicit Ray(Vec3f _org = Vec3f::all(0), Vec3f _dir = Vec3f::all(0), size_t _counter = 0)
			: org(_org)
			, dir(_dir)
			, counter(_counter)
		{}
		
		/**
		 * @brief Returns the hitpoint of the ray
		 * @details The hitpoint is calculated as \f$ \vec{o} + t\vec{d} \f$
		 * @return The hitpoint
		 */
		Vec3f 				hitPoint(void) const;
		/**
		 * @brief Creates and returns the reflected ray
		 * @details This function calculates the reflected ray at the hitpoint of the surface with the normal \b normal
		 * @param normal Normal vector at the ray's hitpoint
		 * @return The reflected ray
		 */
		Ray					reflected(Vec3f normal) const;
		/**
		 * @brief Creates and returns the refracted ray
		 * @details This function calculates the refracted ray at the hitpoint of the surface with the normal \b normal
		 * @param normal Normal vector at the ray's hitpoint
		 * @param k The refractive index
		 * @return The refracted ray
		 */
		std::optional<Ray>	refracted(Vec3f normal, float k) const;
		/**
		 * @brief Traces the given ray and shades it
		 * @details This function implicetly creates a new ray with the increased by one counter and traces it within the scene \b scene
		 * @note This is an auxiliary function to perform recursive ray-tracing
		 * @param scene The reference to the scene
		 * @return The color value of the shaded ray
		 */
		Vec3f				reTrace(const CScene& scene) const;
	};
}
