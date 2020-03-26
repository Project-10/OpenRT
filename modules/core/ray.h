// Basic ray structure
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"

namespace rt {
	/// Basic ray structure
	struct Ray
	{
		Vec3f							org;												///< Origin
		Vec3f							dir;												///< Direction
		size_t 							counter = 0;										///< Nummer of re-traced rays
		
		float							t		= std::numeric_limits<float>::infinity();	///< Current/maximum hit distance
		std::shared_ptr<const IPrim>	hit		= nullptr;									///< Pointer to currently closest primitive
		float							u = 0;												///< Barycentric u coordinate
		float							v = 0;												///< Barycentric v coordinate
		
		// Constructor
		explicit Ray(Vec3f _org = Vec3f::all(0), Vec3f _dir = Vec3f::all(0), size_t _counter = 0)
			: org(_org)
			, dir(_dir)
			, counter(_counter)
		{}
		/**
		 */
		inline Vec3f 				hitPoint(void) const { return org + dir * t; }
		/**
		 */
		inline Ray					reflected(Vec3f normal) const {
			return Ray(hitPoint(), normalize(dir - 2 * normal.dot(dir) * normal), counter + 1);
		}
		/**
		 */
		inline std::optional<Ray>	refracted(Vec3f normal, float k) const {
			float cos_alpha = -dir.dot(normal);
			float sin_2_alpha = 1.0f - cos_alpha * cos_alpha;
			float k_2_sin_2_alpha = k * k * sin_2_alpha;
			if (k_2_sin_2_alpha <= 1) {
				float cos_beta = sqrtf(1.0f - k * k * sin_2_alpha);
				return Ray(hitPoint(), normalize((k * cos_alpha - cos_beta) * normal + k * dir), counter + 1);
			} else
				return std::nullopt;
		}
		
	};
}
