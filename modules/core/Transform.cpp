#include "Transform.h"

namespace rt {
	CTransform CTransform::scale(const Vec3f& S) const {
		Mat t = Mat::eye(4, 4, CV_32FC1);
		for (int i = 0; i < 3; i++)
			t.at<float>(i, i) = S.val[i];
		return CTransform(t * m_t);
	}

	CTransform CTransform::translate(const Vec3f& T) const {
		Mat t = Mat::eye(4, 4, CV_32FC1);
		for (int i = 0; i < 3; i++) t.at<float>(i, 3) = T.val[i];
		return CTransform(t * m_t);
	}

	CTransform CTransform::rotate(const Vec3f& v, float theta) const
	{
		Mat t = Mat::eye(4, 4, CV_32FC1);
		
		float cos_theta = cosf(theta);
		float sin_theta = sinf(theta);
		float x = v.val[0];
		float y = v.val[1];
		float z = v.val[2];
		
		t.at<float>(0, 0) = cos_theta + (1 - cos_theta) * x * x;
		t.at<float>(0, 1) = (1 - cos_theta) * x * y - sin_theta * z;
		t.at<float>(0, 2) = (1 - cos_theta) * x * z + sin_theta * y;
		
		t.at<float>(1, 0) = (1 - cos_theta) * y * x + sin_theta * z;
		t.at<float>(1, 1) = cos_theta + (1 - cos_theta) * y * y;
		t.at<float>(1, 2) = (1 - cos_theta) * y * z - sin_theta * x;
		
		t.at<float>(2, 0) = (1 - cos_theta) * z * x - sin_theta * y;
		t.at<float>(2, 1) = (1 - cos_theta) * z * y + sin_theta * x;
		t.at<float>(2, 2) = cos_theta + (1 - cos_theta) * z * z;
		
		return CTransform(t * m_t);
	}

	Vec3f CTransform::point(const Vec3f& p, const Mat& t) {
		Vec4f P = Vec4f(p.val[0], p.val[1], p.val[2], 1);
		P = Vec4f(reinterpret_cast<float*>(Mat(t * Mat(P)).data));
		return Vec3f(P.val[0], P.val[1], P.val[2]) / P.val[3];
	}

	Vec3f CTransform::vector(const Vec3f& v, const Mat& t) {
		Vec4f V = Vec4f(v.val[0], v.val[1], v.val[2], 0);
		V = Vec4f(reinterpret_cast<float*>(Mat(t * Mat(V)).data));
		return Vec3f(V.val[0], V.val[1], V.val[2]);
	}
}
