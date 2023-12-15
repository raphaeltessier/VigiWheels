// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/CamPosOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__CAM_POS_ORDER__STRUCT_H_
#define INTERFACES__MSG__DETAIL__CAM_POS_ORDER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/CamPosOrder in the package interfaces.
typedef struct interfaces__msg__CamPosOrder
{
  /// 0 -> fixed ; 1 -> scan
  int8_t mode;
  int16_t cam_angle;
} interfaces__msg__CamPosOrder;

// Struct for a sequence of interfaces__msg__CamPosOrder.
typedef struct interfaces__msg__CamPosOrder__Sequence
{
  interfaces__msg__CamPosOrder * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__CamPosOrder__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__CAM_POS_ORDER__STRUCT_H_
