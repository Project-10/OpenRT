// Texture class based on OpenCV Mat
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "types.h"

namespace rt {
	struct Ray;
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
		 * @brief Returns the texture element (in most cases, the color)
		 * @param ray The ray, containing the information about hit object
		 * @return The texture elment (color)
		 */
		DllExport virtual Vec3f	getTexel(const Ray& ray) const;
	};

	using ptr_texture_t = std::shared_ptr<CTexture>;
}
