// Primitive Factory class
// Written by Sergey Kosov in 2025 for Project X
#pragma once

#include "ShaderDiffuse.h"
#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"
#include "PrimDisc.h"
#include "PrimBoolean.h"

namespace rt {
	// ================================ Sphere Primitive Class ================================
	/**
	 * @brief Primitive Factory class
	 * @ingroup modulePrimitive
	 * @author Sergey G. Kosov, sergey.kosov@project-10.de
	 */
	class CPrimFactory {
	public:
		/** 
		 * @brief Creates a primitive sphere 
		 * @param scene The reference to the scene
		 * @param origin Position of the center of the sphere
		 * @param radius Radius of the sphere
		 * @param color The color of the object
		 */
		DllExport static std::shared_ptr<CPrimSphere> createSphere(const CScene& scene, const Vec3f& origin = Vec3f::all(0), float radius = 1.0f, const Vec3f& color = Vec3f::all(1)) {
			auto shader = std::make_shared<CShaderDiffuse>(scene, color);
			return std::make_shared<CPrimSphere>(shader, origin, radius);
		}

		/** 
		 * @brief Creates a primitive plane 
		 * @param scene The reference to the scene
		 * @param origin Point on the plane
		 * @param normal Normal to the plane
		 * @param color The color of the object
		 */
		DllExport static std::shared_ptr<CPrimPlane> createPlane(const CScene& scene, const Vec3f& origin = Vec3f::all(0), const Vec3f& normal = Vec3f(0, 1, 0), const Vec3f& color = Vec3f::all(1)) {
			auto shader = std::make_shared<CShaderDiffuse>(scene, color);
			return std::make_shared<CPrimPlane>(shader, origin, normal);
		}

		/** 
		 * @brief Creates a primitive disc 
		 * @param scene The reference to the scene
		 * @param origin The center pointof the disc
		 * @param normal Normal to the disc
		 * @param radius Radius of the disc
		 * @param innerRadius The disc can also be generalized to an annulus by specifying an inner radius
		 * @param color The color of the object
		 */
		DllExport static std::shared_ptr<CPrimDisc> createDisc(const CScene& scene, const Vec3f& origin = Vec3f::all(0), const Vec3f& normal = Vec3f(0, 1, 0), float radius = 1.0f, float innerRadius = 0.0f, const Vec3f& color = Vec3f::all(1)) {
			auto shader = std::make_shared<CShaderDiffuse>(scene, color);
			return std::make_shared<CPrimDisc>(shader, origin, normal, radius, innerRadius);
		}

		/** 
		 * @brief Creates a boolean object
		 * @param A The first operand
		 * @param B THe second operand
		 * @param operation The boolean operation on operands \b A and \b B
		 * @param maxDepth The max depth of the BSP tree of the solids. Only used if BSP support is enabled
		 * @param maxPrimitives The max number of primitives in the leaf nodes of the BSP tree of the solids. Only used if BSP support is enabled
		 */
		DllExport static std::shared_ptr<CPrimBoolean> createBoolean(const CSolid& A, const CSolid& B, BoolOp operation, int maxDepth = 20, int maxPrimitives = 3) {
			return std::make_shared<CPrimBoolean>(A, B, operation, maxDepth, maxPrimitives);
		}

		/** 
		 * @brief Creates a primitive triangle 
		 * @param scene The reference to the scene
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 * @param ta Texture coordinate for the first vertex
		 * @param tb Texture coordinate for the second vertex
		 * @param tc Texture coordinate for the third vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 * @param color The color of the object
		 */
		DllExport static std::shared_ptr<CPrimTriangle> createTriangle(const CScene& scene, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec2f& ta = Vec2f::all(0), const Vec2f& tb = Vec2f::all(0), const Vec2f& tc = Vec2f::all(0), std::optional<Vec3f> na = std::nullopt, std::optional<Vec3f> nb = std::nullopt, std::optional<Vec3f> nc = std::nullopt, const Vec3f& color = Vec3f::all(1)) {
			auto shader = std::make_shared<CShaderDiffuse>(scene, color);
			return std::make_shared<CPrimTriangle>(shader, a, b, c, ta, tb, tc, na, nb, nc);
		}

		/**
		 * @brief Creates a primitive triangle
		 * @param scene The reference to the scene
		 * @param origin The pivot point (origin) of the triangle (or solid)
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 * @param ta Texture coordinate for the first vertex
		 * @param tb Texture coordinate for the second vertex
		 * @param tc Texture coordinate for the third vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 * @param color The color of the object
		 */
		DllExport static std::shared_ptr<CPrimTriangle> createTriangle(const CScene& scene, const Vec3f& origin, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec2f& ta = Vec2f::all(0), const Vec2f& tb = Vec2f::all(0), const Vec2f& tc = Vec2f::all(0), std::optional<Vec3f> na = std::nullopt, std::optional<Vec3f> nb = std::nullopt, std::optional<Vec3f> nc = std::nullopt, const Vec3f& color = Vec3f::all(1)) {
			auto shader = std::make_shared<CShaderDiffuse>(scene, color);
			return std::make_shared<CPrimTriangle>(shader, origin, a, b, c, ta, tb, tc, na, nb, nc);
		}
	};
}
