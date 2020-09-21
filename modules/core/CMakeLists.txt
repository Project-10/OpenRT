file(GLOB CORE_INCLUDE  ${PROJECT_SOURCE_DIR}/include/openrt.h
                        ${PROJECT_SOURCE_DIR}/include/types.h
                        ${PROJECT_SOURCE_DIR}/include/macroses.h
						)
file(GLOB CORE_SOURCES "*.cpp")
file(GLOB CORE_HEADERS "*.h")

source_group("Include" FILES ${CORE_INCLUDE})
source_group("" FILES ${CORE_SOURCES} ${CORE_HEADERS}) 
source_group("Source Files\\Cameras" FILES "ICamera.h" )
source_group("Source Files\\Cameras\\perspective" FILES "CameraPerspective.h" "CameraPerspective.cpp"  "CameraPerspectiveTarget.h")
source_group("Source Files\\Lights" FILES "ILight.h")
source_group("Source Files\\Lights\\omni" FILES "LightOmni.h" "LightOmni.cpp")
source_group("Source Files\\Lights\\spot" FILES "LightSpot.h" "LightSpot.cpp" "LightSpotTarget.h")
source_group("Source Files\\Lights\\area" FILES "LightArea.h" "LightArea.cpp")
source_group("Source Files\\Lights\\sky" FILES "LightSky.h" "LightSky.cpp")
source_group("Source Files\\Geometry\\Primitives" FILES "IPrim.h")
source_group("Source Files\\Geometry\\Primitives\\plane" FILES "PrimPlane.h" "PrimPlane.cpp")
source_group("Source Files\\Geometry\\Primitives\\sphere" FILES "PrimSphere.h" "PrimSphere.cpp")
source_group("Source Files\\Geometry\\Primitives\\triangle" FILES "PrimTriangle.h" "PrimTriangle.cpp" "PrimTriangleSmooth.h" "PrimTriangleSmooth.cpp")
source_group("Source Files\\Geometry\\Solids" FILES "Solid.h" "Solid.cpp" "SolidQuad.h" "SolidBox.h" "SolidCone.h" "SolidCylinder.h")
source_group("Source Files\\Shaders" FILES "IShader.h" "Shader.h" "Shader.cpp" "ShaderFlat.h" "ShaderEyelight.h" "ShaderChrome.h" "ShaderSSLT.h" "ShaderSSLT.cpp")
source_group("Source Files\\Scene" FILES "Scene.h" "Scene.cpp")
source_group("Source Files\\Common\\BSP Tree" FILES "BSPNode.h" "BSPNode.cpp" "BSPTree.h" "BSPTree.cpp" "BoundingBox.h" "BoundingBox.cpp")
source_group("Source Files\\Common\\Samplers" FILES "Sampler.h" "Sampler.cpp" "Sampler3f.h" "Sampler3f.cpp")
source_group("Source Files\\Common\\Transform" FILES "Transform.h" "Transform.cpp")
source_group("Source Files\\Common\\Texture" FILES "Texture.h" "Texture.cpp")
source_group("Source Files\\Common\\Utilities" FILES "ray.h" "random.h" "timer.h")



# Properties -> C/C++ -> General -> Additional Include Directories
include_directories(${PROJECT_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS})

add_library(core SHARED ${CORE_INCLUDE} ${CORE_SOURCES} ${CORE_HEADERS})

# Properties -> Linker -> Input -> Additional Dependencies
target_link_libraries(core ${OpenCV_LIBS})

set_target_properties(core PROPERTIES OUTPUT_NAME openrt_core${OPENRT_VERSION_MAJOR}${OPENRT_VERSION_MINOR}${OPENRT_VERSION_PATCH})
set_target_properties(core PROPERTIES VERSION ${OPENRT_VERSION_MAJOR}.${OPENRT_VERSION_MINOR}.${OPENRT_VERSION_PATCH} SOVERSION ${OPENRT_VERSION_MAJOR}.${OPENRT_VERSION_MINOR}.${OPENRT_VERSION_PATCH})
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)

#install
install(TARGETS core 
	EXPORT OpenRTTargets
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin 
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${CORE_INCLUDE} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(FILES ${CORE_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/openrt)
 
# Creates folder "Modules" and adds target project 
set_target_properties(core PROPERTIES FOLDER "Modules")
