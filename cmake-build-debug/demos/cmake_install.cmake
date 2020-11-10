# Install script for directory: /Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/demos

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
   "/usr/local/bin/Demo Prim")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/bin/Demo Prim")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/Demo Prim" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/Demo Prim")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo Prim")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo Prim")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo Prim")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo Prim")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo Prim")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/usr/local/bin/Demo Prim")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/Demo AreaLight")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/bin/Demo AreaLight")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/Demo AreaLight" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/Demo AreaLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo AreaLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo AreaLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo AreaLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo AreaLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo AreaLight")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/usr/local/bin/Demo AreaLight")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/Demo CornellBox")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/bin/Demo CornellBox")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/Demo CornellBox" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/Demo CornellBox")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CornellBox")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CornellBox")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CornellBox")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CornellBox")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CornellBox")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/usr/local/bin/Demo CornellBox")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/Demo SpotLight")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/bin/Demo SpotLight")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/Demo SpotLight" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/Demo SpotLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SpotLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SpotLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SpotLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SpotLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SpotLight")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/usr/local/bin/Demo SpotLight")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/Demo SkyLight")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/bin/Demo SkyLight")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/Demo SkyLight" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/Demo SkyLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SkyLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SkyLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SkyLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SkyLight")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SkyLight")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/usr/local/bin/Demo SkyLight")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/Demo SSLT")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/bin/Demo SSLT")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/Demo SSLT" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/Demo SSLT")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SSLT")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SSLT")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SSLT")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SSLT")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo SSLT")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/usr/local/bin/Demo SSLT")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/Demo CSG")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/bin/Demo CSG")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/Demo CSG" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/Demo CSG")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CSG")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CSG")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CSG")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/Cellar/opencv/4.5.0_3/lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CSG")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "../lib"
      "$ENV{DESTDIR}/usr/local/bin/Demo CSG")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Volumes/ExtremeSSD/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/usr/local/bin/Demo CSG")
    endif()
  endif()
endif()

