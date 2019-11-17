// Base solids class
// Written by Dr. Sergey G. Kosov in 2019 for Project X 
#pragma once

#include "ray.h"				// todo: delete it
#include "IPrim.h"
#include "PrimTriangle.h"		// TODO: move it


namespace rt {
	class CSolid {
	public:
		DllExport CSolid(void) = default;
		DllExport CSolid(const CSolid&) = delete;
		DllExport virtual ~CSolid(void) = default;
		DllExport CSolid& operator=(const CSolid&) = delete;

		DllExport const std::vector<ptr_prim_t>& getPrims(void) const { return m_vpPrims; }

	protected:
		DllExport void add(const ptr_prim_t pPrim) { 
			m_vpPrims.push_back(pPrim); 
			printf("num of prims now is %zu\n", m_vpPrims.size());
		}
		DllExport void add(const std::shared_ptr<CSolid> pSolid) { for (const auto pPrim : pSolid->getPrims()) add(pPrim); }


	private:
		std::vector<ptr_prim_t>	m_vpPrims;
	};


	class CSolidQuad : public CSolid {
	public:
		DllExport CSolidQuad(ptr_shader_t pShader, Vec3f a, Vec3f b, Vec3f c, Vec3f d) {
			add(std::make_shared<CPrimTriangle>(pShader, a, b, c));
			add(std::make_shared<CPrimTriangle>(pShader, a, c, d));
		}
		DllExport virtual ~CSolidQuad(void) = default;
	};


	class CSolidBox : public CSolid {
	public:
		DllExport CSolidBox(ptr_shader_t pShader, Vec3f org, float width, float height, float depth) 
		{
			//width /= 2; height /= 2; depth /= 2;
			
			width = 1;
			height = 1;
			depth = 1;

			float r = 1;

			add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(r, -r, -r), org + Vec3f(r, r, -r), org + Vec3f(r, r, r), org + Vec3f(r, -r, r)));

			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f( width, -height, -depth), org + Vec3f( width,  height, -depth), org + Vec3f( width, height, depth), org + Vec3f( width, -height,  depth)));
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width, -height, -depth), org + Vec3f(-width, -height,  depth), org + Vec3f(-width, height, depth), org + Vec3f(-width,  height, -depth)));

			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width,  height, -depth), org + Vec3f(-width,  height,  depth), org + Vec3f(width,  height, depth), org + Vec3f( width,  height, -depth)));
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width, -height, -depth), org + Vec3f( width, -height, -depth), org + Vec3f(width, -height, depth), org + Vec3f(-width, -height,  depth)));

			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width, -height,  depth), org + Vec3f( width, -height,  depth), org + Vec3f(width, height,  depth), org + Vec3f(-width,  height,  depth)));
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-width, -height, -depth), org + Vec3f(-width,  height, -depth), org + Vec3f(width, height, -depth), org + Vec3f( width, -height, -depth)));
		}
		
		DllExport CSolidBox(ptr_shader_t pShader, Vec3f org, float r1) 
		{
			CSolidBox(pShader, org, 1, 1, 1);
			
			//float r = 1;
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(r, -r, -r),  org + Vec3f(r, r, -r),  org + Vec3f(r, r, r),  org + Vec3f(r, -r, r)));
			
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-r, -r, -r), org + Vec3f(-r, -r, r), org + Vec3f(-r, r, r), org + Vec3f(-r, r, -r)));
			//
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-r, r, -r),  org + Vec3f(-r, r, r),  org + Vec3f(r, r, r),  org + Vec3f(r, r, -r)));
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-r, -r, -r), org + Vec3f(r, -r, -r), org + Vec3f(r, -r, r), org + Vec3f(-r, -r, r)));
			//
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-r, -r, r),  org + Vec3f(r, -r, r),  org + Vec3f(r, r, r),  org + Vec3f(-r, r, r)));
			//add(std::make_shared<CSolidQuad>(pShader, org + Vec3f(-r, -r, -r), org + Vec3f(-r, r, -r), org + Vec3f(r, r, -r), org + Vec3f(r, -r, -r)));
		}

		DllExport virtual ~CSolidBox(void) = default;
	};
}