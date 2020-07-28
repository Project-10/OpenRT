#pragma once

#include "core/Scene.h"

#include "core/CameraPerspective.h"
#include "core/CameraPerspectiveTarget.h"

#include "core/LightOmni.h"
#include "core/LightSpot.h"
#include "core/LightSpotTarget.h"

#include "core/LightArea.h"
#include "core/LightSky.h"

#include "core/PrimSphere.h"
#include "core/PrimPlane.h"
#include "core/PrimTriangle.h"

#include "core/SolidQuad.h"
#include "core/SolidBox.h"
#include "core/SolidCone.h"
#include "core/SolidCylinder.h"

#include "core/Shader.h"
#include "core/ShaderFlat.h"
#include "core/ShaderChrome.h"
#include "core/ShaderEyelight.h"

#include "core/Sampler.h"
#include "core/Sampler3f.h"

#include "core/Transform.h"

#include "core/Texture.h"

#include "core/LightSpot.h"

/**
@mainpage Introduction
@section sec_main Open-source Ray-Tracing (OpenRT) C++ library
is a C++ dynamic link library implementing various tasks in realistic image synthesis and rendering, including texturing, shading, aliasing, sampling, and many more. As there are two basic algorithms 
for image synthesis: <a href="https://en.wikipedia.org/wiki/Ray_tracing_(graphics)" target="_blank">ray tracing</a> and <a href="https://en.wikipedia.org/wiki/Rasterisation" target="_blank">rasterization</a>, 
OpenRT concentrates only on physical foundations of ray tracing.

These tasks are optimized for speed, @a i.e. high-efficient calculations. The code is written entirely in C++ and can be compiled with Microsoft Visual C++.

The OpenRT framework consist of the following essential blocks:

@subsubsection sec_main_camera Camera models
	- <b>Perspective Camera:</b> @ref rt::CCameraPerspective

@subsubsection sec_main_light Light sources
	- <b>Omnidirectional point light source:</b> @ref rt::CLightOmni
	- <b>Directional spot light source:</b> @ref rt::CLightSpot
	- <b>Area light source:</b> @ref rt::CLightArea
	- <b>Skylight (ambient occlusion) light source:</b> @ref rt::CLightSky

	@todo Implement class CLightDirect

*/


