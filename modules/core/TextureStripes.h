#pragma once

#include"Texture.h"


namespace rt {

	class CTextureStripes : public CTexture {
	public:
		DllExport CTextureStripes(void) = default;
		DllExport virtual ~CTextureStripes(void) = default;
    
		DllExport Vec3f getTexel(const Vec3f &uvw) const override;
    
		DllExport bool isProcedural(void) const override { return true; }
	};
}
