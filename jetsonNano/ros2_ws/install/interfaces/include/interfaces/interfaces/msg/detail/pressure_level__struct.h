// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/PressureLevel.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__STRUCT_H_
#define INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'level'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/PressureLevel in the package interfaces.
typedef struct interfaces__msg__PressureLevel
{
  rosidl_runtime_c__String level;
} interfaces__msg__PressureLevel;

// Struct for a sequence of interfaces__msg__PressureLevel.
typedef struct interfaces__msg__PressureLevel__Sequence
{
  interfaces__msg__PressureLevel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__PressureLevel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__STRUCT_H_
