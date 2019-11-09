# Properties -> C/C++ -> General -> Additional Include Directories
include_directories(${PROJECT_SOURCE_DIR}/include 
					${PROJECT_SOURCE_DIR}/modules
					${OpenCV_INCLUDE_DIRS} 
				)

# Properties -> Linker -> General -> Additional Library Directories
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
				
# ================================================= DEMO PRIM =================================================
add_executable(Demo_Prim "Demo Prim.cpp")
add_dependencies(Demo_Prim core)

source_group("Source Files" FILES "Demo Prim.cpp")

set_target_properties(Demo_Prim PROPERTIES PROJECT_LABEL "Demo Prim")						# in Visual Studio
set_target_properties(Demo_Prim PROPERTIES OUTPUT_NAME "Demo Prim")
set_target_properties(Demo_Prim PROPERTIES FOLDER "Demos")

# Properties->Linker->Input->Additional Dependencies
target_link_libraries(Demo_Prim ${OpenCV_LIBS} ${CORE_LIB})

#install
install(TARGETS Demo_Prim RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# ================================================= DEMO AREA LIGHT ============================================
add_executable(Demo_AreaLight "Demo AreaLight.cpp")
add_dependencies(Demo_AreaLight core)

source_group("Source Files" FILES "Demo AreaLight.cpp")

set_target_properties(Demo_AreaLight PROPERTIES PROJECT_LABEL "Demo AreaLight")						# in Visual Studio
set_target_properties(Demo_AreaLight PROPERTIES OUTPUT_NAME "Demo AreaLight")
set_target_properties(Demo_AreaLight PROPERTIES FOLDER "Demos")

# Properties->Linker->Input->Additional Dependencies
target_link_libraries(Demo_AreaLight ${OpenCV_LIBS} ${CORE_LIB})

#install
install(TARGETS Demo_AreaLight RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
