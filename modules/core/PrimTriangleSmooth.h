#pragma once

#include "PrimTriangle.h"
#include "IShader.h"

namespace rt {
	/**
	* @brief Triangle Geaometrical Primitive class with interpolation of normal
	*/
	class CPrimTriangleSmooth : public CPrimTriangle
	{
	public:
		/**
		 * @brief Constructor
		 * @param pShader Pointer to the shader to be applied for the prim
		 * @param a Position of the first vertex
		 * @param b Position of the second vertex
		 * @param c Position of the third vertex
		 * @param na Normal at vertex a
		 * @param nb Normal at vertex b
		 * @param nc Normal at vertex c
		 */
		DllExport CPrimTriangleSmooth(ptr_shader_t pShader, Vec3f a, Vec3f b, Vec3f c, Vec3f na, Vec3f nb, Vec3f nc)
			: CPrimTriangle(pShader, a, b, c)
			, m_na(na)
			, m_nb(nb)
			, m_nc(nc)
		{}
		DllExport virtual ~CPrimTriangleSmooth(void) = default;

		
		// TODO: check OpneCV affine3d class
		static void affineTransform(Vec3f& v, const Mat& t) {
			Vec4f V = Vec4f(v.val[0], v.val[1], v.val[2], 1);
			V = Vec4f(reinterpret_cast<float*>(Mat(t * Mat(V)).data));
			v = Vec3f(V.val[0], V.val[1], V.val[2]) / V.val[3];
		}
		
		
		DllExport virtual void transform(const Mat& t) override
		{
			//std::cout << "Point A: " << m_a << std::endl;
			//std::cout << "T Matrix: " << std::endl << t << std::endl;
			affineTransform(m_a, t);
			affineTransform(m_b, t);
			affineTransform(m_c, t);
			
			affineTransform(m_na, t);
			affineTransform(m_nb, t);
			affineTransform(m_nc, t);
			m_na = normalize(m_na);
			m_nb = normalize(m_nb);
			m_nc = normalize(m_nc);
			
			
			// TODO: can we also transform these values with t ?
			m_edge1 = m_b - m_a;
			m_edge2 = m_c - m_a;
			//m_normal = normalize(m_edge1.cross(m_edge2));
			// std::cout << "Point Y: " << y << std::endl;
		}
		
		DllExport virtual Vec3f getNormal(const Ray& ray) const override
		{
			// assume u/v coordinates in ray correspond to beta(u) and gamma(v) barycentric coordinates of 
			// hitpoint on triangle (have to be stored like this in the intersection code!)
			return  normalize(ray.u * m_nb + ray.v * m_nc + (1.0f - ray.u - ray.v) * m_na);
		}


	private:
		Vec3f m_na;		///< Normal at vertex a
		Vec3f m_nb;		///< Normal at vertex b
		Vec3f m_nc;		///< Normal at vertex c
	};

}
