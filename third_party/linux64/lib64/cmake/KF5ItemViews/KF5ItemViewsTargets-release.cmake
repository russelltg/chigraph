#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::ItemViews" for configuration "Release"
set_property(TARGET KF5::ItemViews APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(KF5::ItemViews PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib64/libKF5ItemViews.so.5.30.0"
  IMPORTED_SONAME_RELEASE "libKF5ItemViews.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::ItemViews )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::ItemViews "${_IMPORT_PREFIX}/lib64/libKF5ItemViews.so.5.30.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)