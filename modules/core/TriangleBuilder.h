// Triangle Builder design pattern class
// Written by Sergey Kosov in 2025 for Project X
#pragma once

#include "PrimTriangle.h"

namespace rt {
	 /**
	 * @brief A builder class for creating CPrimTriangle objects conveniently.
	 * @ingroup modulePrimitive
	 * @author Sergey G.Kosov, sergey.kosov@project-10.de
	 */
	class CTriangleBuilder {
	public:		
		/**
		 * @brief Constructor for the triangle builder.
		 * @param pShader Pointer to the shader to be applied for the triangle.
		 * @param origin The pivot point (origin) of the triangle.
		 */
		explicit CTriangleBuilder(const ptr_shader_t pShader, std::optional<Vec3f> origin = std::nullopt)
			: m_pShader(pShader)
			, m_origin(origin)
		{}

		/**
		 * @brief Sets the pivot point (origin) of the triangle.
		 * @param origin The pivot point (origin) of the triangle.
		 * @return Reference to this CTriangleBuilder instance.
		 */
		CTriangleBuilder& setOrigin(const Vec3f& origin) { m_origin = origin; return *this; }
		/**
		 * @brief Sets the vertices of the triangle.
		 * @param a Position of the first vertex.
		 * @param b Position of the second vertex.
		 * @param c Position of the third vertex.
		 * @return Reference to this CTriangleBuilder instance.
		 */
		CTriangleBuilder& setVertices(const Vec3f& a, const Vec3f& b, const Vec3f& c) { m_a = a; m_b = b; m_c = c; return *this; }
		
		/**
		 * @brief Sets the texture coordinates of the triangle's vertices.
		 * @param ta Texture coordinates for the first vertex.
		 * @param tb Texture coordinates for the second vertex.
		 * @param tc Texture coordinates for the third vertex.
		 * @return Reference to this CTriangleBuilder instance.
		 */
		CTriangleBuilder& setTextureCoords(const Vec2f& ta, const Vec2f& tb, const Vec2f& tc) { m_ta = ta; m_tb = tb; m_tc = tc; return *this; }
		
		/**
		 * @brief Sets the normals for the triangle's vertices.
		 * @param na Normal for the first vertex.
		 * @param nb Normal for the second vertex.
		 * @param nc Normal for the third vertex.
		 * @return Reference to this CTriangleBuilder instance.
		 */
		CTriangleBuilder& setNormals(const Vec3f& na, const Vec3f& nb, const Vec3f& nc) { m_na = na; m_nb = nb; m_nc = nc; return *this; }
		
		/**
		 * @brief Builds a CPrimTriangle object with the current parameters.
		 * @return A shared pointer to the created CPrimTriangle object.
		 */
		std::shared_ptr<CPrimTriangle> build(void) const {
			return m_origin 
				? std::make_shared<CPrimTriangle>(m_pShader, m_origin.value(), m_a, m_b, m_c, m_ta, m_tb, m_tc, m_na, m_nb, m_nc)
				: std::make_shared<CPrimTriangle>(m_pShader, m_a, m_b, m_c, m_ta, m_tb, m_tc, m_na, m_nb, m_nc);
		}


	private:
		ptr_shader_t m_pShader;								///< Pointer to the shader, see @ref  IShader.
		std::optional<Vec3f> m_origin	= std::nullopt;		///< The pivot point (origin) of the triangle
		Vec3f m_a						= Vec3f(1, 0, 0);	///< Position of the first vertex
		Vec3f m_b						= Vec3f(0, 1, 0);	///< Position of the second vertex
		Vec3f m_c						= Vec3f(0, 0, 1);	///< Position of the third vertex
		Vec2f m_ta						= Vec2f::all(0);	///< Vertex a texture coordiante
		Vec2f m_tb						= Vec2f::all(0);	///< Vertex b texture coordiante
		Vec2f m_tc						= Vec2f::all(0);	///< Vertex c texture coordiante
		std::optional<Vec3f> m_na		= std::nullopt;		///< Normal at vertex a
		std::optional<Vec3f> m_nb		= std::nullopt;		///< Normal at vertex b
		std::optional<Vec3f> m_nc		= std::nullopt;		///< Normal at vertex c
	};
}