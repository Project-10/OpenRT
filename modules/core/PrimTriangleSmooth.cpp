#include "PrimTriangleSmooth.h"
#include "ray.h"

namespace rt {
	void CPrimTriangleSmooth::transform(const Mat& T)
	{
		// Transform vertexes
		m_a = CTransform::point(m_a, T);
		m_b = CTransform::point(m_b, T);
		m_c = CTransform::point(m_c, T);

		// Transform normals
		Mat T1 = T.inv().t();
		m_na = normalize(CTransform::vector(m_na, T1));
		m_nb = normalize(CTransform::vector(m_nb, T1));
		m_nc = normalize(CTransform::vector(m_nc, T1));

		// Update edges
		m_edge1 = m_b - m_a;
		m_edge2 = m_c - m_a;
	}

	Vec3f CPrimTriangleSmooth::getNormal(const Ray& ray) const
	{
		// assume u/v coordinates in ray correspond to beta(u) and gamma(v) barycentric coordinates of 
		// hitpoint on triangle (have to be stored like this in the intersection code!)
		return  normalize(ray.u * m_nb + ray.v * m_nc + (1.0f - ray.u - ray.v) * m_na);
	}
}