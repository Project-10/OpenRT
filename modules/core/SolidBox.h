// Solid Box class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"
#include "SolidQuad.h"
#include "ShaderEyelight.h"		

namespace rt {
	class CSolidBox : public CSolid {
	public:
		DllExport CSolidBox(void) : CSolidBox(std::make_shared<CShaderEyelight>(), Vec3f::all(0), 1) {}
		DllExport CSolidBox(ptr_shader_t pShader, Vec3f org, float r) : CSolidBox(pShader, org, 2*r, 2*r, 2*r) {}
		DllExport CSolidBox(ptr_shader_t pShader, Vec3f org, float width, float height, float depth) : CSolid(org)
		{
			width /= 2; height /= 2; depth /= 2;

			add(std::make_shared<CSolidQuad>(pShader, org + Vec3f( width, -height, -depth), org + Vec3f( width,  height, -depth), org + Vec3f( width, height, depth), org + Vec3f( width, -height,  depth)));
			add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width, -height, -depth), org + Vec3f(-width, -height,  depth), org + Vec3f(-width, height, depth), org + Vec3f(-width,  height, -depth)));

			add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width,  height, -depth), org + Vec3f(-width,  height,  depth), org + Vec3f(width,  height, depth), org + Vec3f( width,  height, -depth)));
			add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width, -height, -depth), org + Vec3f( width, -height, -depth), org + Vec3f(width, -height, depth), org + Vec3f(-width, -height,  depth)));

			add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width, -height,  depth), org + Vec3f( width, -height,  depth), org + Vec3f(width, height,  depth), org + Vec3f(-width,  height,  depth)));
			add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width, -height, -depth), org + Vec3f(-width,  height, -depth), org + Vec3f(width, height, -depth), org + Vec3f( width, -height, -depth)));
		}
		DllExport virtual ~CSolidBox(void) = default;
	};
}
