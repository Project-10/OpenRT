// Basic ray structure
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"
#include "Prim.h"

namespace rt {
	/// Basic ray structure
	struct Ray
	{
		Vec3f					org;		///< Origin
		Vec3f					dir;		///< Direction
		float					t;			///< Current/maximum hit distance
		std::shared_ptr<CPrim> 	hit;		///< Pointer to currently closest primitive
	};
}
