#include "PrimTriangle.h"
#include "Ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimTriangle::intersect(Ray& ray)
	{
		auto t = MoellerTrumbore(ray);
		if (t) {
			ray.t = t.value().val[0];
			ray.u = t.value().val[1];
			ray.v = t.value().val[2];
			ray.hit = shared_from_this();
			return true;
		}
		else
			return false;
	}

	void CPrimTriangle::transform(const Mat& T)
	{
		// Transform vertexes
		m_a = CTransform::point(m_a, T);
		m_b = CTransform::point(m_b, T);
		m_c = CTransform::point(m_c, T);

		// Transform normals
		Mat T1 = T.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, T1));
		if (m_na) m_na = normalize(CTransform::vector(m_na.value(), T1));
		if (m_nb) m_nb = normalize(CTransform::vector(m_nb.value(), T1));
		if (m_nc) m_nc = normalize(CTransform::vector(m_nc.value(), T1));

		// Update edges
		m_edge1 = m_b - m_a;
		m_edge2 = m_c - m_a;
	}
	
	Vec3f CPrimTriangle::getOrigin(void) const
	{
		return 0.33f * (m_a + m_b + m_c);
	}

	Vec3f CPrimTriangle::doGetNormal(const Ray& ray) const
	{
			return m_normal;
	}

	Vec3f CPrimTriangle::doGetShadingNormal(const Ray& ray) const
	{
		if (m_na && m_nb && m_nc)
			return (1.0f - ray.u - ray.v) * m_na.value() + ray.u * m_nb.value() + ray.v * m_nc.value();
		else
			return m_normal;
	}

	Vec2f CPrimTriangle::getTextureCoords(const Ray& ray) const
	{
		return (1.0f - ray.u - ray.v) * m_ta + ray.u * m_tb + ray.v * m_tc;
	}

	CBoundingBox CPrimTriangle::getBoundingBox(void) const
	{
		CBoundingBox res;
		res.extend(m_a);
		res.extend(m_b);
		res.extend(m_c);
		return res;
	}
	
	// ---------------------- private ----------------------
	std::optional<Vec3f> CPrimTriangle::MoellerTrumbore(const Ray& ray) const
	{
		const Vec3f pvec = ray.dir.cross(m_edge2);
		const float det = m_edge1.dot(pvec);
		if (fabs(det) < std::numeric_limits<float>::epsilon())
			return std::nullopt;

		const float inv_det = 1.0f / det;
		const Vec3f tvec = ray.org - m_a;
		float lambda = tvec.dot(pvec);
		lambda *= inv_det;
		if (lambda < 0.0f || lambda > 1.0f)
			return std::nullopt;

		const Vec3f qvec = tvec.cross(m_edge1);
		float mue = ray.dir.dot(qvec);
		mue *= inv_det;
		if (mue < 0.0f || mue + lambda > 1.0f)
			return std::nullopt;

		float t = m_edge2.dot(qvec);
		t *= inv_det;
		if (ray.t <= t || t < Epsilon)
			return std::nullopt;

		return Vec3f(t, lambda, mue);
	}
}

