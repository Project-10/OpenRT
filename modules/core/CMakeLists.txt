file(GLOB CORE_INCLUDE  ${PROJECT_SOURCE_DIR}/include/openrt.h
                        ${PROJECT_SOURCE_DIR}/include/types.h
                        ${PROJECT_SOURCE_DIR}/include/macroses.h
						${PROJECT_SOURCE_DIR}/include/mathutils.h
						)
file(GLOB CORE_SOURCES "*.cpp")
file(GLOB CORE_HEADERS "*.h")

source_group("Include" FILES ${CORE_INCLUDE})
source_group("" FILES ${CORE_SOURCES} ${CORE_HEADERS})
source_group("Source Files\\Cameras" FILES "ICamera.h" )
source_group("Source Files\\Cameras\\perspective" FILES "CameraPerspective.h" "CameraPerspective.cpp"  "CameraPerspectiveTarget.h")
source_group("Source Files\\Cameras\\thin lens" FILES "CameraThinLens.h" "CameraThinLens.cpp")
source_group("Source Files\\Cameras\\orthographic" FILES "CameraOrthographic.h" "CameraOrthographic.cpp" "CameraOrthographicTarget.h")
source_group("Source Files\\Cameras\\environment" FILES "CameraEnvironment.h" "CameraEnvironment.cpp" "CameraEnvironmentTarget.h")
source_group("Source Files\\Lights" FILES "ILight.h")
source_group("Source Files\\Lights\\omni" FILES "LightOmni.h" "LightOmni.cpp")
source_group("Source Files\\Lights\\spot" FILES "LightSpot.h" "LightSpot.cpp" "LightSpotTarget.h")
source_group("Source Files\\Lights\\area" FILES "LightArea.h" "LightArea.cpp")
source_group("Source Files\\Lights\\sky" FILES "LightSky.h" "LightSky.cpp")
source_group("Source Files\\Geometry" FILES "TriangleBuilder.h")
source_group("Source Files\\Geometry\\Primitives" FILES "Prim.h" "Prim.cpp")
source_group("Source Files\\Geometry\\Primitives\\plane" FILES "PrimPlane.h" "PrimPlane.cpp")
source_group("Source Files\\Geometry\\Primitives\\disc" FILES "PrimDisc.h" "PrimDisc.cpp")
source_group("Source Files\\Geometry\\Primitives\\sphere" FILES "PrimSphere.h" "PrimSphere.cpp")
source_group("Source Files\\Geometry\\Primitives\\triangle" FILES "PrimTriangle.h" "PrimTriangle.cpp")
source_group("Source Files\\Geometry\\Primitives\\boolean" FILES "PrimBoolean.h" "PrimBoolean.cpp")
source_group("Source Files\\Geometry\\Solids" FILES "Solid.h" "Solid.cpp")
source_group("Source Files\\Geometry\\Solids\\quad" FILES "SolidQuad.h" "SolidQuad.cpp")
source_group("Source Files\\Geometry\\Solids\\disc" FILES "SolidDisc.h" "SolidDisc.cpp")
source_group("Source Files\\Geometry\\Solids\\box" FILES "SolidBox.h" "SolidBox.cpp")
source_group("Source Files\\Geometry\\Solids\\cone" FILES "SolidCone.h" "SolidCone.cpp")
source_group("Source Files\\Geometry\\Solids\\cylinder" FILES "SolidCylinder.h" "SolidCylinder.cpp")
source_group("Source Files\\Geometry\\Solids\\sphere" FILES "SolidSphere.h" "SolidSphere.cpp")
source_group("Source Files\\Geometry\\Solids\\torus" FILES "SolidTorus.h" "SolidTorus.cpp")
source_group("Source Files\\Shaders" FILES "IShader.h")
source_group("Source Files\\Shaders" FILES "Shader.h" "Shader.cpp")
source_group("Source Files\\Shaders" FILES "ShaderScene.h" "ShaderScene.cpp")
source_group("Source Files\\Shaders\\flat" FILES "ShaderFlat.h" "ShaderFlat.cpp")
source_group("Source Files\\Shaders\\eyelight" FILES "ShaderEyelight.h" "ShaderEyelight.cpp")
source_group("Source Files\\Shaders\\diffuse" FILES "ShaderDiffuse.h" "ShaderDiffuse.cpp")
source_group("Source Files\\Shaders\\shadow" FILES "ShaderShadow.h" "ShaderShadow.cpp")
source_group("Source Files\\Shaders\\glossy" FILES "ShaderGlossy.h" "ShaderGlossy.cpp")
source_group("Source Files\\Shaders\\new shader" FILES "NewShader.h" "NewShader.cpp")
source_group("Source Files\\Shaders\\mirror" FILES "ShaderMirror.h" "ShaderMirror.cpp")
source_group("Source Files\\Shaders\\phong" FILES "ShaderPhong.h" "ShaderPhong.cpp")
source_group("Source Files\\Shaders\\blinn" FILES "ShaderBlinn.h" "ShaderBlinn.cpp")
source_group("Source Files\\Shaders\\glass" FILES "ShaderGlass.h" "ShaderGlass.cpp")
source_group("Source Files\\Shaders\\volume scatter" FILES "ShaderVolumeScatter.h" "ShaderVolumeScatter.cpp")
source_group("Source Files\\Shaders\\subsurface scattering" FILES "ShaderSubsurfaceScattering.h" "ShaderSubsurfaceScattering.cpp")
source_group("Source Files\\Shaders\\principled" FILES "ShaderPrincipled.h" "ShaderPrincipled.cpp")
source_group("Source Files\\Shaders\\hemisphere" FILES "ShaderHemisphere.h" "ShaderHemisphere.cpp")
source_group("Source Files\\BxDFs" FILES "BxDF.h" "BxDF.cpp")
source_group("Source Files\\BxDFs\\lambertian" FILES "BRDFLambertian.h" "BRDFLambertian.cpp")
source_group("Source Files\\BxDFs\\oren-nayar" FILES "BRDFOrenNayar.h" "BRDFOrenNayar.cpp")
source_group("Source Files\\BxDFs\\phong" FILES "BRDFPhong.h" "BRDFPhong.cpp")
source_group("Source Files\\BxDFs\\blinn" FILES "BRDFBlinn.h" "BRDFBlinn.cpp")
source_group("Source Files\\BxDFs\\specular reflection" FILES "BRDFSpecularReflection.h" "BRDFSpecularReflection.cpp")
source_group("Source Files\\BxDFs\\specular transmission" FILES "BTDFSpecularTransmission.h" "BTDFSpecularTransmission.cpp")
source_group("Source Files\\BxDFs\\glossy" FILES "BRDFGlossy.h" "BRDFGlossy.cpp")
source_group("Source Files\\Scene" FILES "Scene.h" "Scene.cpp")
source_group("Source Files\\Common\\BSP Tree" FILES "BSPNode.h" "BSPNode.cpp" "BSPTree.h" "BSPTree.cpp" "BoundingBox.h" "BoundingBox.cpp")
source_group("Source Files\\Common\\Samplers" FILES "Sampler.h" "Sampler.cpp")
source_group("Source Files\\Common\\Samplers\\Random" FILES "SamplerRandom.h" "SamplerRandom.cpp")
source_group("Source Files\\Common\\Samplers\\Stratified" FILES "SamplerStratified.h" "SamplerStratified.cpp")
source_group("Source Files\\Common\\Transform" FILES "Transform.h" "Transform.cpp")
source_group("Source Files\\Common\\Gradient" FILES "Gradient.h" "Gradient.cpp")
source_group("Source Files\\Common\\Perlin Noise" FILES "PerlinNoise.cpp" "PerlinNoise.h")
source_group("Source Files\\Common\\Texture" FILES "Texture.h" "Texture.cpp")
source_group("Source Files\\Common\\Texture\\Stripes" FILES "TextureStripes.h" "TextureStripes.cpp")
source_group("Source Files\\Common\\Texture\\Rings" FILES "TextureRings.h" "TextureRings.cpp")
source_group("Source Files\\Common\\Texture\\Marble" FILES "TextureMarble.h" "TextureMarble.cpp")
source_group("Source Files\\Common\\Ray" FILES "Ray.h" "Ray.cpp")
source_group("Source Files\\Common\\Utilities" FILES "random.h" "timer.h" "tools.h")



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
