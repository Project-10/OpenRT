// Basic ray structure
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"
#include "Prim.h"

namespace rt {
	/// Basic ray structure
	struct Ray
	{
		Vec3f					org;											///< Origin
		Vec3f					dir;											///< Direction
		float					t	= std::numeric_limits<float>::infinity();	///< Current/maximum hit distance
		std::shared_ptr<IPrim> 	hit = nullptr;									///< Pointer to currently closest primitive

		Ray(Vec3f _org = Vec3f::all(0), Vec3f _dir = Vec3f::all(0)) : org(_org), dir(_dir) {}
	};
}
