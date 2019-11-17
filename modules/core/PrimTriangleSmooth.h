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