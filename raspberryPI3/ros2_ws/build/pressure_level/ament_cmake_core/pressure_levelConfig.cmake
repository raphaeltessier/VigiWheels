# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_pressure_level_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED pressure_level_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(pressure_level_FOUND FALSE)
  elseif(NOT pressure_level_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(pressure_level_FOUND FALSE)
  endif()
  return()
endif()
set(_pressure_level_CONFIG_INCLUDED TRUE)

# output package information
if(NOT pressure_level_FIND_QUIETLY)
  message(STATUS "Found pressure_level: 0.0.0 (${pressure_level_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'pressure_level' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${pressure_level_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(pressure_level_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${pressure_level_DIR}/${_extra}")
endforeach()
