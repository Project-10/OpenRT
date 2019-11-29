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
		
		DllExport CTransform 	scale(float s) const { return scale(Vec3f::all(s)); }
		DllExport CTransform	scale(float sx, float sy, float sz) const { return scale(Vec3f(sx, sy, sz)); }
		DllExport CTransform	scale(const Vec3f& S) const;
		
		DllExport CTransform	reflectX(void) const { return scale(Vec3f(-1, 1, 1)); }
		DllExport CTransform	reflectY(void) const { return scale(Vec3f(1, -1, 1)); }
		DllExport CTransform	reflectZ(void) const { return scale(Vec3f(1, 1, -1)); }
		DllExport CTransform	reflectO(void) const { return scale(Vec3f(-1, -1, -1)); }
		
		DllExport CTransform	translate(float tx, float ty, float tz) const { return translate(Vec3f(tx, ty, tz)); }
		DllExport CTransform	translate(const Vec3f& T) const;

		DllExport CTransform	rotate(const Vec3f& v, float theta) const;
			
		// TODO: check OpneCV affine3d class
		static Vec3f point(const Vec3f& p, const Mat& t);
		static Vec3f vector(Vec3f& v, const Mat& t);
	
	
	protected:
		DllExport CTransform(const Mat& t) : m_t(t) {}
	
	
	private:
		Mat m_t;
	};
}
