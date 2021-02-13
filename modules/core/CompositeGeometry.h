#pragma once

#include "IPrim.h"
#include "Solid.h"

namespace rt {
    enum class BoolOp {
        Intersection, Difference, Union
    };

    class CCompositeGeometry : public IPrim {
    public:
        /*
		 * @brief Constructor
		 * @details Class stores the copies of the solids in order to prevent changing the composite primitives after creation if the solids are chenged in user code
		 * @todo what to do if the shader was already assigned to a solid?
		 */
		DllExport explicit CCompositeGeometry(const CSolid& s1, const CSolid& s2, BoolOp operationType);
		DllExport virtual ~CCompositeGeometry(void) = default;

		DllExport virtual bool 			intersect(Ray& ray) const override;
		DllExport virtual bool 			if_intersect(const Ray& ray) const override;
		DllExport virtual void 			transform(const Mat& T) override;
		DllExport virtual Vec3f			getOrigin(void) const override { return m_origin; }
		DllExport virtual Vec3f 		getNormal(const Ray&) const override;
		DllExport virtual Vec2f			getTextureCoords(const Ray& ray) const override;
		DllExport virtual CBoundingBox	getBoundingBox(void) const override { return m_boundingBox; }
		
		
    private:
        std::vector<ptr_prim_t> 			m_vPrims1;				///<
        std::vector<ptr_prim_t> 			m_vPrims2;				///<
		Vec3f			m_origin;
		BoolOp			m_operationType;	///<
        CBoundingBox 	m_boundingBox;		///<
    };

}
