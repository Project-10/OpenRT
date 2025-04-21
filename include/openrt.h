#pragma once

#include "core/Scene.h"

#include "core/CameraPerspective.h"
#include "core/CameraPerspectiveTarget.h"
#include "core/CameraOrthographic.h"
#include "core/CameraOrthographicTarget.h"
#include "core/CameraThinLens.h"
#include "core/CameraEnvironment.h"
#include "core/CameraEnvironmentTarget.h"

#include "core/LightOmni.h"
#include "core/LightSpot.h"
#include "core/LightSpotTarget.h"

#include "core/LightArea.h"
#include "core/LightSky.h"

#include "core/PrimSphere.h"
#include "core/PrimPlane.h"
#include "core/PrimDisc.h"
#include "core/PrimTriangle.h"
#include "core/PrimBoolean.h"
#include "core/TriangleBuilder.h"

#include "core/SolidQuad.h"
#include "core/SolidDisc.h"
#include "core/SolidBox.h"
#include "core/SolidCone.h"
#include "core/SolidCylinder.h"
#include "core/SolidSphere.h"
#include "core/SolidTorus.h"

#include "core/BRDFLambertian.h"
#include "core/BRDFOrenNayar.h"
#include "core/BRDFPhong.h"
#include "core/BRDFBlinn.h"
#include "core/BRDFSpecularReflection.h"
#include "core/BTDFSpecularTransmission.h"

#include "core/ShaderFlat.h"
#include "core/ShaderEyelight.h"
#include "core/ShaderDiffuse.h"
#include "core/ShaderPrincipled.h"
#include "core/ShaderShadow.h"
#include "core/ShaderChrome.h"
#include "core/ShaderSubsurfaceScattering.h"
#include "core/ShaderVolumeScatter.h"
#include "core/NewShader.h"
#include "core/ShaderPhong.h"
#include "core/ShaderBlinn.h"
#include "core/ShaderMirror.h"
#include "core/ShaderGlass.h"
#include "core/ShaderHemisphere.h"
#include "core/ShaderGlobal.h"

#include "core/Sampler.h"
#include "core/SamplerRandom.h"
#include "core/SamplerStratified.h"

#include "core/Transform.h"

#include "core/Texture.h"
#include "core/TextureStripes.h"
#include "core/TextureRings.h"
#include "core/TextureMarble.h"
#include "core/PerlinNoise.h"
#include "core/Gradient.h"

#include "core/LightSpot.h"

#ifdef WIN32
const std::string dataPath = "../../data/";
#else
const std::string dataPath = "../../../data/";
#endif

/**
@mainpage Introduction
@section sec_main Open-source Ray-Tracing (OpenRT) C++ library
is a C++ dynamic link library implementing various tasks in realistic image synthesis and rendering, including texturing, shading, aliasing, sampling, and many more. As there are two basic algorithms 
for image synthesis: <a href="https://en.wikipedia.org/wiki/Ray_tracing_(graphics)" target="_blank">ray tracing</a> and <a href="https://en.wikipedia.org/wiki/Rasterisation" target="_blank">rasterization</a>, 
OpenRT concentrates only on physical foundations of ray tracing.

These tasks are optimized for speed, @a i.e. high-efficient calculations. The code is written entirely in C++ and can be compiled with Microsoft Visual C++.

The OpenRT framework consist of the following essential blocks:

@subsection sec_main_camera Camera models
	- <b>Perspective Camera:</b> @ref rt::CCameraPerspective
	- <b>Orthographic Camera:</b> @ref rt::CCameraOrthographic

@subsection sec_main_light Light sources
	- <b>Omnidirectional point light source:</b> @ref rt::CLightOmni
	- <b>Directional spot light source:</b> @ref rt::CLightSpot
	- <b>Area light source:</b> @ref rt::CLightArea
	- <b>Skylight (ambient occlusion) light source:</b> @ref rt::CLightSky
	@todo Implement class CLightDirect

@subsection sec_main_geometry Geometry
@subsubsection sec_main_primitives Primitives
	- <b>Plane:</b> @ref rt::CPrimPlane
	- <b>Sphere:</b> @ref rt::CPrimSphere
	- <b>Triangle:</b> @ref rt::CPrimTriangle
@subsubsection sec_main_solids Solids
 - @b Quadrilateral: @ref rt::CSolidQuad
 - @b Box: @ref rt::CSolidBox
 - @b Sphere: @ref rt::CSolidSphere
 - @b Cone: @ref rt::CSolidCone
 - @b Cylinder: @ref rt::CSolidCylinder
 
@subsection sec_main_shaders Shaders
	- <b>Flat:</b> @ref rt::CShaderFlat
	- <b>Eye Light:</b> @ref rt::CShaderEyelight
	- <b>Phong:</b> @ref rt::CShaderPhong
	- <b>Blinn:</b> @ref rt::CShaderBlinn
	- <b>Chrome:</b> @ref rt::CShaderChrome
	- <b>Glass:</b> @ref rt::CShaderGlass
	- <b>Mirror:</b> @ref rt::CShaderMirror
	- <b>General Purpose Shader:</b> @ref rt::CShader
	- <b>Subsurface Scattering:</b> @ref rt::CShaderSubsurfaceScattering
*/

/**
@defgroup moduleCore OpenRT Module
@section sec_openrt_core Core OpenRT Module

@defgroup moduleCamera Camera
@ingroup moduleCore
@brief Module containing variouse camera models

@defgroup moduleGeometry Geometry
@ingroup moduleCore
@brief Sub-module containing classes to describe scene geometry

@defgroup modulePrimitive
@ingroup moduleGeometry
@brief Atomic geometry
		
@defgroup moduleSolid
@ingroup moduleGeometry
@brief Compound geometry

@defgroup moduleShader Shading
@ingroup moduleCore
@brief A set of methods for shading the geometry

@defgroup moduleTexture Texturing
@ingroup moduleShader
@brief Bitmap and procedural texturing methods

@defgroup moduleLight Light
@ingroup moduleCore
@brief Module containing variouse light sources
*/

/**
@page s3 Installation
OpenRT is a cross-platform C++ library. The description here was tested on Windows 10 / Visual Studio 2019, macOS Catalina 10.15.6 / Xcode 11.4 and Ubuntu 18.04 / gcc 7.3.0. 
If you encounter errors after following the steps described below, feel free to contact us via our 
<a href="https://openrt.org/forum/viewforum.php?f=33">User Q&A forum</a> or <a href="https://github.com/Project-10/OpenRT/issues">Issues</a>. We'll do our best to help you out.<br>

OpenRT has only one dependency: it is based on <a href="https://www.opencv.org/">OpenCV</a> library.
In order to use the OpenRT library, the OpenCV library should be also installed.

@section sec_install_cv Installing OpenCV
- Download the latest version of the OpenCV library from <a href="https://www.opencv.org/releases.html" target="_blank">https://www.opencv.org/releases.html</a>
- Build and install the library. You may follow the following guidance:
	- <a href="https://docs.opencv.org/4.4.0/d3/d52/tutorial_windows_install.html" target="_blank">Installation in Windows guide</a> or
	- <a href="https://docs.opencv.org/4.4.0/d7/d9f/tutorial_linux_install.html" target="_blank">Installation in Linux guide</a>

@section sec_install_OpenRT Installing OpenRT
- Download either the latest stable OpenRT version from <a href="https://research.openrt.org/OpenRT/#downloads" target="_blank">Project X Research</a>
  or fork the latest snapshot from our <a href="https://github.com/Project-10/OpenRT" target="_blank">GitHub repository</a>
- Unpack it to your local folder (for example to disk @b C:\\ for Windows or to @b /Users/username/ for MacOS, so the library path will be @b C:\\OpenRT\\ or @b /Users/username/OpenRT/)
@subsection sec_install_OpenRT_win Installation in Windows and macOS
@subsubsection sec_install_OpenRT_win_source Building OpenRT from Source Using CMake GUI
In case you want to build the library (recommended), follow these instructions, otherwise - skip this step and proceed to @ref sec_install_OpenRT_win_built.
This step also assumes that you have downloaded the sources of the OpenRT library.
- Download and install <a href="https://cmake.org/download" target="_blank">CMake</a> for your operating system
- Run \b cmake-gui.exe in Windows or \b CMake.app in MacOS
- In the <i>"Where is the source code"</i> field choose the OpenRT source directory: \b OpenRT<br>
  In the <i>"Where to build the binaries"</i> field choose directory where Visual Studio or Xcode project files will be generated: \a e.g. \b OpenRT/build
- Press \a Configure button and choose <i>Visual Studio</i> for using 32-bit compiler, <i>Visual Studio Win64</i> for using 64-bit compiler or <i>Xcode</i> as building environment
- Be sure that the \a OpenCV_DIR is pointing to the OpenCV installation directory (\a e.g. \b OpenCV/build/install or \b /usr/local/share/OpenCV), where \b OpenCVConfig.cmake file is located
- (Optionally) you can change \a CMAKE_INSTALL_PREFIX to the directory where the OpenRT binaries will be installed (\a e.g. to \b OpenRT/build/install)
- Press one more time \a Configure and then \a Generate, so the IDE project files will be generated in the \b OpenRT/build
- Open the generated project by pressing the \a Open \a Project button or directly by opening file \b OpenRT/build/OpenRT.sln or \b OpenRT/build/OpenRT.xcodeproj
- Build \b ALL_BUILD and \b INSTALL projects first for \a Debug and then for \a Release configuration. That will copy OpenRT headers, binaries and demonstration applications to the install folder \b OpenRT/build/install
- Windows users may copy the OpenCV binaries into the install folder by executing script \b /OpenRT/build/install/bin/copyOpenCVDLL.bat
- (Optionally) you can copy the install folder with the ready-to-use OpenRT library (\a e.g. \b OpenRT/build/install) to any other folder

@subsubsection sec_install_OpenRT_win_built Using the Pre-built Libraries
This step assumes that you have downloaded OpenRT-package with the pre-build binaries. In such case the type and version of the downloaded binaries should correspond to your C++ compiler.
If it is not, please return to the @ref sec_install_OpenRT_win_source section and generate the binaries with your compiler. The content of the install folder (\a e.g. \b OpenRT/build/install) will
correspond to the downloaded pre-build OpenRT package.

@subsection sec_install_OpenRT_linux Installation in Linux
@subsubsection sec_install_OpenRT_linux_source Building OpenRT from Source Using Terminal
For installing the OpenRT library for Ubuntu we assume that the OpenCV library was already installed (@ref sec_install_cv), thus GCC, CMake and Git are also installed. In order to download and
install the latest version from master input the following commands in terminal:
 @code{.sh}
 cd ~/<my_working_directory>
 git clone https://github.com/Project-10/OpenRT.git
 cd OpenRT
 mkdir build
 cd build
 cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local
 make
 make install
 make clean
 @endcode


@section sec_install_OpenRT_after After Installation
As soon as the OpenRT library is installed, you can launch the demo applications from the \b /bin folder. If you have built the binaries from the sources, you can also start the demo projects
directly from your IDE.
The corresponding description may be found in @ref demo. Do not hesitate to modify these demo projects for your needs or start your own project based on our demo code.

If you wish to generate a new project, which will use OpenRT, or add OpenRT to an existing project we highly recommend you to use <a href="https://cmake.org" target="_blank">CMake</a> and follow the
<a href="https://openrt.org/forum/viewtopic.php?f=31&t=1028&sid=09c4a9156520f7cf81bd474ac278ed51" target="_blank">Using OpenRT library with CMake</a> guidance, where template \b CMakeLists.txt
file is provided.<br>
Alternatively, you can specify the following paths and library in your IDE manually:
- Add to Configuration Properties -> C/C++ -> General -> Additional Include Directories the path \b install_folder/include
- Add to Configuration Properties -> Linker -> General -> Additional Library Directories the path \b install_folder/lib for both Release and Debug configurations
- Add to Configuration Properties -> Linker -> Input -> Additional Dependencies the libraries \b core100.lib, and \b core100d.lib
  for Release and Debug configurations accordingly.
*/


