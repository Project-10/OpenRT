# - Config file for the OpenRT package
# It defines the following variables
#  OpenRT_INCLUDE_DIRS - include directories for OpenRT
#  OpenRT_LIBRARIES    - libraries to link against
 
# Compute paths
get_filename_component(OpenRT_CMAKE_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
set(OpenRT_INCLUDE_DIRS /Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT;/Users/otmanesabir/Desktop/S5/Project&Thesis/OpenRT/cmake-build-debug)
 
# Our library dependencies (contains definitions for IMPORTED targets)
if(NOT TARGET OpenRT AND NOT OpenRT_BINARY_DIR)
  include(${OpenRT_CMAKE_DIR}/lib/OpenRTTargets.cmake)
endif()
 
# These are IMPORTED targets created by OpenRTTargets.cmake
set(OpenRT_LIBRARIES CORE)
