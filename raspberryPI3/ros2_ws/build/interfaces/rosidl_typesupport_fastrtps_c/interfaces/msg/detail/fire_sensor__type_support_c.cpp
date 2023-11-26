// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from interfaces:msg/FireSensor.idl
// generated code does not contain a copyright notice
#include "interfaces/msg/detail/fire_sensor__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "interfaces/msg/detail/fire_sensor__struct.h"
#include "interfaces/msg/detail/fire_sensor__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _FireSensor__ros_msg_type = interfaces__msg__FireSensor;

static bool _FireSensor__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _FireSensor__ros_msg_type * ros_message = static_cast<const _FireSensor__ros_msg_type *>(untyped_ros_message);
  // Field name: ir_sensor1
  {
    cdr << ros_message->ir_sensor1;
  }

  // Field name: ir_sensor2
  {
    cdr << ros_message->ir_sensor2;
  }

  // Field name: ir_sensor3
  {
    cdr << ros_message->ir_sensor3;
  }

  // Field name: ir_sensor4
  {
    cdr << ros_message->ir_sensor4;
  }

  // Field name: smoke_sensor1
  {
    cdr << ros_message->smoke_sensor1;
  }

  // Field name: smoke_sensor2
  {
    cdr << ros_message->smoke_sensor2;
  }

  return true;
}

static bool _FireSensor__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _FireSensor__ros_msg_type * ros_message = static_cast<_FireSensor__ros_msg_type *>(untyped_ros_message);
  // Field name: ir_sensor1
  {
    cdr >> ros_message->ir_sensor1;
  }

  // Field name: ir_sensor2
  {
    cdr >> ros_message->ir_sensor2;
  }

  // Field name: ir_sensor3
  {
    cdr >> ros_message->ir_sensor3;
  }

  // Field name: ir_sensor4
  {
    cdr >> ros_message->ir_sensor4;
  }

  // Field name: smoke_sensor1
  {
    cdr >> ros_message->smoke_sensor1;
  }

  // Field name: smoke_sensor2
  {
    cdr >> ros_message->smoke_sensor2;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_interfaces
size_t get_serialized_size_interfaces__msg__FireSensor(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _FireSensor__ros_msg_type * ros_message = static_cast<const _FireSensor__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name ir_sensor1
  {
    size_t item_size = sizeof(ros_message->ir_sensor1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ir_sensor2
  {
    size_t item_size = sizeof(ros_message->ir_sensor2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ir_sensor3
  {
    size_t item_size = sizeof(ros_message->ir_sensor3);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ir_sensor4
  {
    size_t item_size = sizeof(ros_message->ir_sensor4);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name smoke_sensor1
  {
    size_t item_size = sizeof(ros_message->smoke_sensor1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name smoke_sensor2
  {
    size_t item_size = sizeof(ros_message->smoke_sensor2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _FireSensor__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_interfaces__msg__FireSensor(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_interfaces
size_t max_serialized_size_interfaces__msg__FireSensor(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: ir_sensor1
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: ir_sensor2
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: ir_sensor3
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: ir_sensor4
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: smoke_sensor1
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: smoke_sensor2
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  return current_alignment - initial_alignment;
}

static size_t _FireSensor__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_interfaces__msg__FireSensor(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_FireSensor = {
  "interfaces::msg",
  "FireSensor",
  _FireSensor__cdr_serialize,
  _FireSensor__cdr_deserialize,
  _FireSensor__get_serialized_size,
  _FireSensor__max_serialized_size
};

static rosidl_message_type_support_t _FireSensor__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_FireSensor,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, interfaces, msg, FireSensor)() {
  return &_FireSensor__type_support;
}

#if defined(__cplusplus)
}
#endif
