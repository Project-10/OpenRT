
#include "Texture.h"
#include "Ray.h"
#include "macroses.h"
#include <math.h>

namespace rt{
	// Constructor
	CTexture::CTexture(const std::string& fileName) : CTexture(imread(fileName, 1))
	{
		RT_ASSERT_MSG(!empty(), "Can't read file %s", fileName.c_str());
	}

	// Constructor
	/// @todo Add support for 2-channel textures
	CTexture::CTexture(const Mat& img) : Mat(img)
	{
		if (!empty()) {
			RT_ASSERT_MSG(img.channels() == 3, "Can't create texture from %d-channels images. A 3-channels image is needed.", img.channels());
			if (img.type() != CV_32FC3)
				(*this).convertTo(*this, CV_32FC3, 1.0 / 255);
		}
	}

	Vec3f CTexture::getTexel(const Ray& ray) const
	{
		Vec2f uv = ray.hit ? ray.hit->getTextureCoords(ray) : ray.ndc;

		float u = fmodf(uv[0], 1);
		float v = fmodf(uv[1], 1);

		if (u < 0) u += 1;
		if (v < 0) v += 1;
		
		if (empty()) {	// Empty texture generates chess pattern
			bool ax = u < 0.5f ? true : false;
			bool ay = v > 0.5f ? true : false;
		
			bool c = ax ^ ay;
			return c ? RGB(255, 255, 255) : RGB(127, 127, 127);
		} else {
			// find texel indices
			float U = u * cols;
			float V = v * rows;

			int x = static_cast<int>(U);
			int y = static_cast<int>(V);

			if (false) {
				// --- Nearest neighbour ---
				return (*this).at<Vec3f>(y, x);
			}
			else {
				// --- Bi-linear ---
				float dx = U - x;
				float dy = V - y;

				Vec3f a, b;
				if (x + 1 >= cols) a = (*this).at<Vec3f>(y, x);
				else a = (1.0f - dx) * (*this).at<Vec3f>(y, x) + dx * (*this).at<Vec3f>(y, x + 1);

				if (y + 1 >= rows) return a;
				else {
					if (x + 1 >= cols) b = (*this).at<Vec3f>(y + 1, x);
					else b = (1.0f - dx) * (*this).at<Vec3f>(y + 1, x) + dx * (*this).at<Vec3f>(y + 1, x + 1);
				}
				return (1.0f - dy) * a + dy * b;;
			}
		}
	}
}
