# Install script for directory: /Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libopenrt_core100d.1.0.0.dylib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib/libopenrt_core100d.1.0.0.dylib")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.1.0.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.1.0.0.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.1.0.0.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.1.0.0.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.1.0.0.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.1.0.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.1.0.0.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libopenrt_core100d.dylib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib/libopenrt_core100d.dylib")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/usr/local/lib/libopenrt_core100d.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/macroses.h;/usr/local/include/openrt.h;/usr/local/include/types.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include" TYPE FILE FILES
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/include/macroses.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/include/openrt.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/include/types.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/openrt/BSPNode.h;/usr/local/include/openrt/BSPTree.h;/usr/local/include/openrt/BoundingBox.h;/usr/local/include/openrt/CameraOrthographic.h;/usr/local/include/openrt/CameraOrthographicTarget.h;/usr/local/include/openrt/CameraPerspective.h;/usr/local/include/openrt/CameraPerspectiveTarget.h;/usr/local/include/openrt/CompositeGeometry.h;/usr/local/include/openrt/ICamera.h;/usr/local/include/openrt/ILight.h;/usr/local/include/openrt/IPrim.h;/usr/local/include/openrt/IShader.h;/usr/local/include/openrt/IntersectionRange.h;/usr/local/include/openrt/LightArea.h;/usr/local/include/openrt/LightOmni.h;/usr/local/include/openrt/LightSky.h;/usr/local/include/openrt/LightSpot.h;/usr/local/include/openrt/LightSpotTarget.h;/usr/local/include/openrt/PrimPlane.h;/usr/local/include/openrt/PrimSphere.h;/usr/local/include/openrt/PrimTriangle.h;/usr/local/include/openrt/Ray.h;/usr/local/include/openrt/Sampler.h;/usr/local/include/openrt/Sampler3f.h;/usr/local/include/openrt/Scene.h;/usr/local/include/openrt/Shader.h;/usr/local/include/openrt/ShaderChrome.h;/usr/local/include/openrt/ShaderEyelight.h;/usr/local/include/openrt/ShaderFlat.h;/usr/local/include/openrt/ShaderSSLT.h;/usr/local/include/openrt/Solid.h;/usr/local/include/openrt/SolidBox.h;/usr/local/include/openrt/SolidCone.h;/usr/local/include/openrt/SolidCylinder.h;/usr/local/include/openrt/SolidQuad.h;/usr/local/include/openrt/Texture.h;/usr/local/include/openrt/Transform.h;/usr/local/include/openrt/random.h;/usr/local/include/openrt/timer.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/openrt" TYPE FILE FILES
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/BSPNode.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/BSPTree.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/BoundingBox.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/CameraOrthographic.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/CameraOrthographicTarget.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/CameraPerspective.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/CameraPerspectiveTarget.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/CompositeGeometry.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/ICamera.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/ILight.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/IPrim.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/IShader.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/IntersectionRange.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/LightArea.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/LightOmni.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/LightSky.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/LightSpot.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/LightSpotTarget.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/PrimPlane.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/PrimSphere.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/PrimTriangle.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/Ray.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/Sampler.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/Sampler3f.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/Scene.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/Shader.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/ShaderChrome.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/ShaderEyelight.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/ShaderFlat.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/ShaderSSLT.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/Solid.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/SolidBox.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/SolidCone.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/SolidCylinder.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/SolidQuad.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/Texture.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/Transform.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/random.h"
    "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/modules/core/timer.h"
    )
endif()

