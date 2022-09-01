// Texture class based on OpenCV Mat
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "types.h"

namespace rt {
	// ================================ Texture Class ================================
	/**
	 * @brief Texture class
	 * @ingroup moduleTexture
	 * @author Dr. Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CTexture : public Mat {
	public:
		/**
		 * @brief Default Constructor
		 */
		DllExport CTexture(void) : Mat() {}
		/**
		 * @brief Constructor
		 * @param fileName The path to the texture file
		 */
		DllExport CTexture(const std::string& fileName);
		/**
		 * @brief Constructor
		 * @param img The texture image
		 */
		DllExport CTexture(const Mat& img);
		DllExport CTexture(const CTexture&) = delete;
		DllExport ~CTexture(void) = default;
		DllExport const CTexture& operator=(const CTexture&) = delete;
		
		/**
		 * @brief Returns the texture element with coordinates \b (uv)
		 * @param uv The texel coordinates in the texture space, \f$ u,v\in [-1; 1 ] \f$
		 * @return The texture elment (color)
		 */
		DllExport Vec3f			getTexel(const Vec2f& uv) const;
		/**
		 * @brief Returns the color at given 3d point at the object
		 * @details This method is mostly used for procedural texturing. Argument \b uvw is a 3d point at the surface of the object and given in the object coordinate system.
		 * @param uvw The texel coordinates in the OCS
		 * @return The texture elment (color)
		 */
		DllExport virtual Vec3f	getTexel(const Vec3f& uvw) const;
		/**
		 * @brief Checks if we are dealing with Procedural textures
		 * @retval true If texture procedural
		 * @retval false Otherwise
		 */
		DllExport virtual bool	isProcedural(void) const { return false; }
	};

	using ptr_texture_t = std::shared_ptr<CTexture>;
}
