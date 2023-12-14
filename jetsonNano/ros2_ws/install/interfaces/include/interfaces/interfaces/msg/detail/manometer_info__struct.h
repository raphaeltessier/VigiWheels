// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/ManometerInfo.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__MANOMETER_INFO__STRUCT_H_
#define INTERFACES__MSG__DETAIL__MANOMETER_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ManometerInfo in the package interfaces.
/**
  * (x1,y1) (x2,y2) 
 */
typedef struct interfaces__msg__ManometerInfo
{
  float x1;
  float y1;
  float x2;
  float y2;
  float probability;
} interfaces__msg__ManometerInfo;

// Struct for a sequence of interfaces__msg__ManometerInfo.
typedef struct interfaces__msg__ManometerInfo__Sequence
{
  interfaces__msg__ManometerInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__ManometerInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__MANOMETER_INFO__STRUCT_H_
