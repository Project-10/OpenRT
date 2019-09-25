#pragma once

#include <optional>
#include <vector>
#include <memory>
#include <thread>
#include <math.h>
#include "opencv2/opencv.hpp"

using namespace cv;

#ifdef _WIN32
	using byte	= unsigned __int8;
	using word	= unsigned __int16;
	using dword	= unsigned __int32;
	using qword	= unsigned __int64;
#else
	using byte	= uint8_t;
	using word	= uint16_t;
	using dword	= uint32_t;
	using qword	= uint64_t;
#endif

static const double	Pi	= 3.1415926;			///< Pi number
static const float	Pif	= 3.1415926f;			///< Pi number

static const float Epsilon = 1E-4;

#define RGB(r, g, b)  Vec3f((b), (g), (r))