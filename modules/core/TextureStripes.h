#pragma once

#include"Texture.h"


namespace rt {

	class CTextureStripes : public CTexture {
	public:
		DllExport CTextureStripes(float periods) : m_periods(periods) {}
		DllExport virtual ~CTextureStripes(void) = default;
    
		DllExport Vec3f getTexel(const Vec3f &uvw) const override;
		DllExport bool	isProcedural(void) const override { return true; }


	private:
		float m_periods;
	};
}
