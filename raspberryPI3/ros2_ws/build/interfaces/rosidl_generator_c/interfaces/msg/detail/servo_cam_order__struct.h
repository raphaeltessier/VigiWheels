// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/ServoCamOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__STRUCT_H_
#define INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ServoCamOrder in the package interfaces.
typedef struct interfaces__msg__ServoCamOrder
{
  /// angle ° [0, 180]
  uint8_t servo_cam_angle;
} interfaces__msg__ServoCamOrder;

// Struct for a sequence of interfaces__msg__ServoCamOrder.
typedef struct interfaces__msg__ServoCamOrder__Sequence
{
  interfaces__msg__ServoCamOrder * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__ServoCamOrder__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__STRUCT_H_
