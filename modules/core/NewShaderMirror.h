// Phong shader class
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;

	class CNewShaderMirror : public CNewShader
	{
	public:
		DllExport CNewShaderMirror(const CScene& scene);
		DllExport virtual ~CNewShaderMirror(void) = default;
	};

}