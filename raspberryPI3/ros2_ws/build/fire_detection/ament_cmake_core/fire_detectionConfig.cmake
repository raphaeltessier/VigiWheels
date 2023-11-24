# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_fire_detection_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED fire_detection_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(fire_detection_FOUND FALSE)
  elseif(NOT fire_detection_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(fire_detection_FOUND FALSE)
  endif()
  return()
endif()
set(_fire_detection_CONFIG_INCLUDED TRUE)

# output package information
if(NOT fire_detection_FIND_QUIETLY)
  message(STATUS "Found fire_detection: 0.0.0 (${fire_detection_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'fire_detection' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${fire_detection_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(fire_detection_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${fire_detection_DIR}/${_extra}")
endforeach()
