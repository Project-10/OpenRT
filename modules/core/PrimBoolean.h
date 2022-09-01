// Boolean Geometry class
// Written by Otmane Sabir in 2020
#pragma once

#include "Prim.h"
#include "Solid.h"
#ifdef ENABLE_BSP
#include "BSPTree.h"
#endif

namespace rt {
    /// Binary boolean operators for constructive solid geometry class
	enum class BoolOp {
        Union,			///< Merger of two objects into one
		Intersection,	///< Portion common to both objects
		Substraction	///< Subtraction of one object from another
    };
	
	enum class IntersectionState;

	// ================================ Boolean Geometry Class ================================
	/**
	 * @brief Boolean Compound Primitive class
	 * @details This calss implements <a href="https://en.wikipedia.org/wiki/Constructive_solid_geometry" target="_blank">Constructive solid geometry (CSG)</a> technique for solid modeling. 
	 * CSG allows for creating complex surfaces or objects by using Boolean operators to combine simpler objects, potentially generating visually complex objects by combining a few primitive ones.
	 * @ingroup modulePrimitive
	 * @author Otmane Sabir, o.sabir@jacobs-university.de
	 */
	class CPrimBoolean : public CPrim {
    public:
        /*
		 * @brief Constructor
		 * @details This class stores the pointers to the underlying primitives of operands \b A and \b B
         * @param A The first operand
         * @param B THe second operand
         * @param operation The boolean operation on operands \b A and \b B
         * @param maxDepth The max depth of the BSP tree of the solids. Only used if BSP support is enabled
         * @param maxDepth The max number of primitives in the leaf nodes of the BSP tree of the solids. Only used if BSP support is enabled
		 */
        DllExport explicit CPrimBoolean(const CSolid& A, const CSolid& B, BoolOp operation, int maxDepth = 20, int maxPrimitives = 3);
        DllExport virtual ~CPrimBoolean(void) override = default;
        
		DllExport virtual bool			intersect(Ray &ray) const override;
		DllExport virtual bool			if_intersect(const Ray &ray) const override;
		DllExport virtual Vec3f			getOrigin(void) const override { return m_origin; }
		DllExport virtual Vec2f			getTextureCoords(const Ray &ray) const override;
		DllExport virtual CBoundingBox	getBoundingBox(void) const override { return m_boundingBox; }
		DllExport virtual void			flipNormal(void) override;

		
    private:
		DllExport virtual Vec3f			doGetNormal(const Ray &) const override;
		DllExport virtual void			doTransform(const Mat& T) override;
		
		std::optional<Ray>				computeUnion(const Ray &ray) const;			///< Helper method to perform union logic
		std::optional<Ray>				computeIntersection(const Ray& ray) const;	///< Helper method to perform intersection logic
		std::optional<Ray>				computeSubstraction(const Ray &ray) const;	///< Helper method to perform substraction logic
        void 							computeBoundingBox(void);					///< Helper method to recompute the composite
		IntersectionState 				classifyRay(const Ray& ray) const;			///< Helper method to classify if a ray is entering, exiting, or missing a solid

		
	private:
        std::vector<ptr_prim_t>			m_vpPrims1;			        ///< Vector of primitives of the first geometry
        std::vector<ptr_prim_t>			m_vpPrims2;					///< Vector of primitives of the second geometry
		Vec3f							m_origin;                   ///< Origin/Pivot of the geometry
		bool							m_flippedNormal = false; 	///< Flag indicating whether the normals were flipped
		BoolOp							m_operation;				///< Type of operation
        CBoundingBox                    m_boundingBox;              ///< Bounding box of this composite geometry
#ifdef ENABLE_BSP
		int								m_maxDepth;					///< The maximum allowed depth of the trees
		int								m_maxPrimitives;			///< The minimum number of primitives in a leaf-node
		std::unique_ptr<CBSPTree>		m_pBSPTree1		= nullptr;	///< Pointer to the spatial index structure for left geometry
        std::unique_ptr<CBSPTree>		m_pBSPTree2		= nullptr;	///< Pointer to the spatial index structure for right geometry
#endif
    };

}
