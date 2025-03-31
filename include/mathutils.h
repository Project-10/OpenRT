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
inline Vec3f tangent(const Vec3f& v) { 
	return (fabs(v.dot(Vec3f(1, 0, 0))) < 0.999f) 
		? normalize(Vec3f(1, 0, 0).cross(v)) 
		: normalize(Vec3f(0, 0, 1).cross(v)); 
}
