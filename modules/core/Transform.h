// Affine transformation clall
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "types.h"

namespace rt {
	class CTransform {
	public:
		DllExport CTransform(void) : m_t(Mat::eye(4, 4, CV_32FC1)) {}
		DllExport ~CTransform(void) = default;
		
		DllExport Mat 			get(void) const { return m_t; }
		
		DllExport CTransform	scale(Vec3f S) const {
			Mat t = Mat::eye(4, 4, CV_32FC1);
			for (int i = 0; i < 3; i++)
				t.at<float>(i, i) = S.val[i];
			return CTransform(t * m_t);
		}
		DllExport CTransform 	scale(float s) const { return scale(Vec3f::all(s)); }
		DllExport CTransform	scale(float sx, float sy, float sz) const { return scale(Vec3f(sx, sy, sz)); }
		DllExport CTransform	reflectX(void) const { return scale(Vec3f(-1, 1, 1)); }
		DllExport CTransform	reflectY(void) const { return scale(Vec3f(1, -1, 1)); }
		DllExport CTransform	reflectZ(void) const { return scale(Vec3f(1, 1, -1)); }
		DllExport CTransform	reflectO(void) const { return scale(Vec3f(-1, -1, -1)); }
		DllExport CTransform	translate(Vec3f T) const {
			Mat t = Mat::eye(4, 4, CV_32FC1);
			for (int i = 0; i < 3; i++) t.at<float>(i, 3) = T.val[i];
			return CTransform(t * m_t);
		}
		DllExport CTransform	translate(float tx, float ty, float tz) const { return translate(Vec3f(tx, ty, tz)); }
		DllExport CTransform	rotate(Vec3f v, float theta) const {
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
		
	
	protected:
		DllExport CTransform(const Mat& t) : m_t(t) {}
	
	
	private:
		Mat m_t;
	};
}
