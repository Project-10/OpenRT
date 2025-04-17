// Mirror shader class
// Written by Dr. Sergey G. Kosov in 2025 for Open RT
#include "NewShader.h"

#pragma once

namespace rt {
	class CScene;
	// ================================ Mirror Shader Class ================================
	/**
	 * @brief Mirror shader
	 * @ingroup moduleShader
	 * @author Sergey G. Kosov, sergey.kosov@openrt.org
	 */
	class CShaderMirror : public CNewShader
	{
	public:
		/**
		 * @brief Constructor
		 * @param scene The reference to the scene
		 */
		DllExport CShaderMirror(const CScene& scene);
		DllExport virtual ~CShaderMirror(void) = default;
	};

}