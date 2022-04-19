
#include "Texture.h"
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

	Vec3f CTexture::getTexel(const Vec2f& uv) const
	{
		float t;
		float u = modff(uv.val[0] + Epsilon, &t);
		float v = modff(uv.val[1] + Epsilon, &t);

		if (u < 0) u += 1;
		if (v < 0) v += 1;
		
		if (empty()) {	// Empty texture generates chess pattern
			bool ax = u < 0.5f ? true : false;
			bool ay = v > 0.5f ? true : false;
		
			bool c = ax ^ ay;
			return c ? Vec3f::all(1) : Vec3f::all(0.5f);
		} else {
			// find texel indices
			int x = static_cast<int>(cols * u);
			int y = static_cast<int>(rows * v);

			return (*this).at<Vec3f>(y, x);
		}
	}
        
        bool CTexture::isProcedural(){
                return false;
            }

        Vec3f CTexture::getTextel3D(const Vec3f &ray) {
             RT_ASSERT_MSG(false, "This method should never be called. Aborting...");
         }
        
        
}
