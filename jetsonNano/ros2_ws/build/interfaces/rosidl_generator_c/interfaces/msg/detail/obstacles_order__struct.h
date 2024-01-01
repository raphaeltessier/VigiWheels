// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/ObstaclesOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__STRUCT_H_
#define INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ObstaclesOrder in the package interfaces.
/**
  * General orders
 */
typedef struct interfaces__msg__ObstaclesOrder
{
  bool front_object;
  bool rear_object;
} interfaces__msg__ObstaclesOrder;

// Struct for a sequence of interfaces__msg__ObstaclesOrder.
typedef struct interfaces__msg__ObstaclesOrder__Sequence
{
  interfaces__msg__ObstaclesOrder * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__ObstaclesOrder__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__STRUCT_H_
