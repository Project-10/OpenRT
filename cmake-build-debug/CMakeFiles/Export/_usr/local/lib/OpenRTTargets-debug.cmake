#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "core" for configuration "Debug"
set_property(TARGET core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(core PROPERTIES
  IMPORTED_LOCATION_DEBUG "/usr/local/lib/libopenrt_core100d.1.0.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libopenrt_core100d.1.0.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS core )
list(APPEND _IMPORT_CHECK_FILES_FOR_core "/usr/local/lib/libopenrt_core100d.1.0.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
