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

# ================================================= DEMO CORNELL BOX ============================================
add_executable(Demo_CornellBox "Demo CornellBox.cpp")
add_dependencies(Demo_CornellBox core)

source_group("Source Files" FILES "Demo CornellBox.cpp")

set_target_properties(Demo_CornellBox PROPERTIES PROJECT_LABEL "Demo CornellBox")						# in Visual Studio
set_target_properties(Demo_CornellBox PROPERTIES OUTPUT_NAME "Demo CornellBox")
set_target_properties(Demo_CornellBox PROPERTIES FOLDER "Demos")

# Properties->Linker->Input->Additional Dependencies
target_link_libraries(Demo_CornellBox ${OpenCV_LIBS} ${CORE_LIB})
#install
install(TARGETS Demo_CornellBox RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

function(create_demo target source)
	add_executable(${target} "${source}.cpp")
	add_dependencies(${target} core)

	source_group("Source Files" FILES "${source}.cpp")

	set_target_properties(${target} PROPERTIES PROJECT_LABEL "${source}")						# in Visual Studio
	set_target_properties(${target} PROPERTIES OUTPUT_NAME "${source}")
	set_target_properties(${target} PROPERTIES FOLDER "Demos")

	# Properties->Linker->Input->Additional Dependencies
	target_link_libraries(${target} ${OpenCV_LIBS} ${CORE_LIB})
	# --------
	#install
	install(TARGETS ${target} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endfunction()

create_demo(Demo_SpotLight "Demo SpotLight")
create_demo(Demo_SkyLight "Demo SkyLight")
