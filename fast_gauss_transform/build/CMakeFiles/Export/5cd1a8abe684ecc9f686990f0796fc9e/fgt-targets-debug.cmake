#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Fgt::Library-C++" for configuration "Debug"
set_property(TARGET Fgt::Library-C++ APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Fgt::Library-C++ PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libfgt.0.4.11.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libfgt.0.dylib"
  )

list(APPEND _cmake_import_check_targets Fgt::Library-C++ )
list(APPEND _cmake_import_check_files_for_Fgt::Library-C++ "${_IMPORT_PREFIX}/lib/libfgt.0.4.11.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
