#pragma once

#include "IPrim.h"
#include "Solid.h"
#include "BSPTree.h"

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
        std::vector<ptr_prim_t> 			m_vPrims1;				///< Vector of primitives of the first geometry.
        std::vector<ptr_prim_t> 			m_vPrims2;				///< Vector of primitives of the second geometry.
		Vec3f			m_origin;           ///< Origin/Pivot of the geometry.
		BoolOp			m_operationType;	///< Type of operation.
        CBoundingBox 	m_boundingBox;		///< Bounding box of this composite geometry.
#ifdef ENABLE_BSP
        std::unique_ptr<CBSPTree>		m_pBSPTree1		= nullptr;	///< Pointer to the acceleration structure for left geometry
        std::unique_ptr<CBSPTree>		m_pBSPTree2		= nullptr;	///< Pointer to the acceleration structure for right geometry
#endif
    };

}
