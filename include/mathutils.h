#pragma once

#include "opencv2/opencv.hpp"

using namespace cv;

// Approximative pow() function
// Taken from: http://martin.ankerl.com/2012/01/25/optimized-approximative-pow-in-c-and-cpp/
inline double fastPow(double a, double b)
{
	union {
		double d;
		int x[2];
	} u = { a };
	u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
	u.x[0] = 0;
	return u.d;
}

//template<typename T>
//inline T SIGN(T a) {return (a >= 0) ? 1 : -1;}

// Compute a tangent vector for a given normalized vector
inline Vec3f tangent(const Vec3f& v, const Vec3f& aux = Vec3f(1.0f, .0f, .0f)) { 
	return (fabs(v.dot(aux)) < 0.999f) 
		? normalize(aux.cross(v)) 
		: normalize(Vec3f(aux[1], aux[0], aux[2]).cross(v));
}
