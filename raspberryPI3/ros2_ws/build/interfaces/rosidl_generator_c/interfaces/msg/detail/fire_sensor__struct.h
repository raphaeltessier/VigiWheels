// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/FireSensor.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__FIRE_SENSOR__STRUCT_H_
#define INTERFACES__MSG__DETAIL__FIRE_SENSOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/FireSensor in the package interfaces.
typedef struct interfaces__msg__FireSensor
{
  int16_t ir_sensor_1;
  int16_t ir_sensor_2;
} interfaces__msg__FireSensor;

// Struct for a sequence of interfaces__msg__FireSensor.
typedef struct interfaces__msg__FireSensor__Sequence
{
  interfaces__msg__FireSensor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__FireSensor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__FIRE_SENSOR__STRUCT_H_
