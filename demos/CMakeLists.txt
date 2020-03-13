# Properties -> C/C++ -> General -> Additional Include Directories
include_directories(${PROJECT_SOURCE_DIR}/include 
					${PROJECT_SOURCE_DIR}/modules
					${OpenCV_INCLUDE_DIRS} 
				)

# Properties -> Linker -> General -> Additional Library Directories
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
				
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

#Add Demos
create_demo(Demo_Prim "Demo SpotLight")
create_demo(Demo_AreaLight "Demo AreaLight")
create_demo(Demo_CornellBox "Demo CornellBox")
create_demo(Demo_SpotLight "Demo SpotLight")
create_demo(Demo_SkyLight "Demo SkyLight")
