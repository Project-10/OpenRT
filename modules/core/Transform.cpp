#include "Transform.h"

namespace rt {
	CTransform CTransform::scale(const Vec3f& S) const {
		Mat t = Mat::eye(4, 4, CV_32FC1);
		for (int i = 0; i < 3; i++)
			t.at<float>(i, i) = S[i];
		return CTransform(t * m_t);
	}

	CTransform CTransform::translate(const Vec3f& T) const {
		Mat t = Mat::eye(4, 4, CV_32FC1);
		for (int i = 0; i < 3; i++) 
			t.at<float>(i, 3) = T[i];
		return CTransform(t * m_t);
	}

	CTransform CTransform::rotate(const Vec3f& k, float theta) const
	{
		Mat t = Mat::eye(4, 4, CV_32FC1);
		theta *= Pif/180;
		float cos_theta = cosf(theta);
		float sin_theta = sinf(theta);
		float x = k[0];
		float y = k[1];
		float z = k[2];
		
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
		Vec4f P = Vec4f(p[0], p[1], p[2], 1);
		P = Vec4f(reinterpret_cast<float*>(Mat(t * Mat(P)).data));
		return Vec3f(P[0], P[1], P[2]) / P[3];
	}

	Vec3f CTransform::vector(const Vec3f& v, const Mat& t) {
		Vec4f V = Vec4f(v[0], v[1], v[2], 0);
		V = Vec4f(reinterpret_cast<float*>(Mat(t * Mat(V)).data));
		return Vec3f(V[0], V[1], V[2]);
	}
}
