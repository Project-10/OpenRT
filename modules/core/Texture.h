// Texture class based on OpenCV Mat
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "types.h"
#include "macroses.h"

namespace rt {
	/**
	 * @brief Texture class
	 * @author Dr. Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CTexture : public Mat {
	public:
		/**
		 * @brief Default Constructor
		 */
		DllExport CTexture(void) : Mat()
		{}
		/**
		 * @brief Constructor
		 */
		DllExport CTexture(const std::string& fileName) : CTexture(imread(fileName))
		{
			RT_ASSERT_MSG(!empty(), "Can't read file %s", fileName.c_str());
		}
		/**
		 * @brief Constructor
		 */
		DllExport CTexture(const Mat& img) : Mat(img)
		{
			if (!empty()) {
				RT_ASSERT_MSG(img.channels() == 3, "Can't create texture from %d-channels images. A 3-channels image is needed.", img.channels());
				if (img.type() != CV_32FC3)
					(*this).convertTo(*this, CV_32FC3, 1.0 / 255);
			}
		}
		DllExport CTexture(const CTexture&) = delete;
		DllExport ~CTexture(void) = default;
		DllExport const CTexture& operator=(const CTexture&) = delete;
		
		/**
		 * @brief Returns the texture element with coordinates \b uv
		 * @param uv The element coordinates in the texture space
		 * @return The texture elment (color)
		 */
		DllExport Vec3f getTexel(const Vec2f& uv) const;
	};

using ptr_texture_t = std::shared_ptr<CTexture>;
}
