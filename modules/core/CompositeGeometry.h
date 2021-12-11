#pragma once

#include "IPrim.h"
#include "Solid.h"
#include "BSPTree.h"

namespace rt {
    enum class BoolOp {
        Intersection, Difference, Union
    };

    enum class IntersectionState {
        Enter, Exit, Miss
    };

    /**
	
	*/
	class CCompositeGeometry : public IPrim {
    public:
        /*
		 * @brief Constructor
		 * @details Class stores the copies of the solids in order to prevent changing the composite primitives after creation if the solids are chenged in user code
         * @param s1 First solid in the composite geometry.
         * @param s2 Second solid in the composite geometry.
         * @param operationType The type of operation this composite will be performing.
         * @param maxDepth The max depth of the BSP tree of the solids. Only used if BSP support is enabled.
         * @param maxDepth The max number of primitives in the leaf nodes of the BSP tree of the solids. Only used if BSP support is enabled.
		 */
        DllExport explicit CCompositeGeometry(const CSolid& s1, const CSolid& s2, BoolOp operationType, int maxDepth = 3, int maxPrimitives = 20);
        DllExport virtual ~CCompositeGeometry(void) override = default;
        
		DllExport virtual bool			intersect(Ray &ray) const override;
        DllExport virtual bool			if_intersect(const Ray &ray) const override;
        DllExport virtual void			transform(const Mat &T) override;
        DllExport virtual Vec3f			getOrigin(void) const override { return m_origin; }
		DllExport virtual Vec2f			getTextureCoords(const Ray &ray) const override;
        DllExport virtual CBoundingBox	getBoundingBox(void) const override { return m_boundingBox; }
		DllExport virtual void			flipNormal(void) override;

		
    private:
		DllExport virtual Vec3f			doGetNormal(const Ray &) const override;
		
		std::optional<Ray>				computeUnion(const Ray &ray) const;             ///< Helper method to perform union logic.
		std::optional<Ray>				computeDifference(const Ray &ray) const;        ///< Helper method to perform difference logic.
		std::optional<Ray>				computeIntersection(const Ray &ray) const;      ///< Helper method to perform intersection logic.
        void 							computeBoundingBox(void);						///< Helper method to recompute the composite.
		IntersectionState 				classifyRay(const Ray& ray) const;				///< Helper method to classify if a ray is entering, exiting, or missing a solid.

		
	private:
        std::vector<ptr_prim_t>			m_vpPrims1;			        ///< Vector of primitives of the first geometry.
        std::vector<ptr_prim_t>			m_vpPrims2;					///< Vector of primitives of the second geometry.
		Vec3f							m_origin;                   ///< Origin/Pivot of the geometry.
		bool							m_flippedNormal = false; 	///< Flag indicating whether the normals were flipped
		BoolOp							m_operationType;            ///< Type of operation.
        CBoundingBox                    m_boundingBox;              ///< Bounding box of this composite geometry.
        size_t							MAX_INTERSECTIONS = 150;    ///< Limit of intersection checks performed with a single ray.
#ifdef ENABLE_BSP
		int								m_maxDepth;					///< The maximum allowed depth of the trees
		int								m_maxPrimitives;			///< The minimum number of primitives in a leaf-node
		std::unique_ptr<CBSPTree>		m_pBSPTree1		= nullptr;	///< Pointer to the spatial index structure for left geometry
        std::unique_ptr<CBSPTree>		m_pBSPTree2		= nullptr;	///< Pointer to the spatial index structure for right geometry
#endif
    };

}
