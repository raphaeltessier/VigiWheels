// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from interfaces:msg/EmergencyAlertFire.idl
// generated code does not contain a copyright notice
#include "interfaces/msg/detail/emergency_alert_fire__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "interfaces/msg/detail/emergency_alert_fire__struct.h"
#include "interfaces/msg/detail/emergency_alert_fire__functions.h"
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


using _EmergencyAlertFire__ros_msg_type = interfaces__msg__EmergencyAlertFire;

static bool _EmergencyAlertFire__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _EmergencyAlertFire__ros_msg_type * ros_message = static_cast<const _EmergencyAlertFire__ros_msg_type *>(untyped_ros_message);
  // Field name: fire_detected
  {
    cdr << (ros_message->fire_detected ? true : false);
  }

  // Field name: ir_front_right
  {
    cdr << (ros_message->ir_front_right ? true : false);
  }

  // Field name: ir_front_left
  {
    cdr << (ros_message->ir_front_left ? true : false);
  }

  // Field name: ir_rear_right
  {
    cdr << (ros_message->ir_rear_right ? true : false);
  }

  // Field name: ir_rear_left
  {
    cdr << (ros_message->ir_rear_left ? true : false);
  }

  return true;
}

static bool _EmergencyAlertFire__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _EmergencyAlertFire__ros_msg_type * ros_message = static_cast<_EmergencyAlertFire__ros_msg_type *>(untyped_ros_message);
  // Field name: fire_detected
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->fire_detected = tmp ? true : false;
  }

  // Field name: ir_front_right
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ir_front_right = tmp ? true : false;
  }

  // Field name: ir_front_left
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ir_front_left = tmp ? true : false;
  }

  // Field name: ir_rear_right
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ir_rear_right = tmp ? true : false;
  }

  // Field name: ir_rear_left
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ir_rear_left = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_interfaces
size_t get_serialized_size_interfaces__msg__EmergencyAlertFire(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _EmergencyAlertFire__ros_msg_type * ros_message = static_cast<const _EmergencyAlertFire__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name fire_detected
  {
    size_t item_size = sizeof(ros_message->fire_detected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ir_front_right
  {
    size_t item_size = sizeof(ros_message->ir_front_right);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ir_front_left
  {
    size_t item_size = sizeof(ros_message->ir_front_left);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ir_rear_right
  {
    size_t item_size = sizeof(ros_message->ir_rear_right);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ir_rear_left
  {
    size_t item_size = sizeof(ros_message->ir_rear_left);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _EmergencyAlertFire__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_interfaces__msg__EmergencyAlertFire(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_interfaces
size_t max_serialized_size_interfaces__msg__EmergencyAlertFire(
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

  // member: fire_detected
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ir_front_right
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ir_front_left
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ir_rear_right
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ir_rear_left
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _EmergencyAlertFire__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_interfaces__msg__EmergencyAlertFire(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_EmergencyAlertFire = {
  "interfaces::msg",
  "EmergencyAlertFire",
  _EmergencyAlertFire__cdr_serialize,
  _EmergencyAlertFire__cdr_deserialize,
  _EmergencyAlertFire__get_serialized_size,
  _EmergencyAlertFire__max_serialized_size
};

static rosidl_message_type_support_t _EmergencyAlertFire__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_EmergencyAlertFire,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, interfaces, msg, EmergencyAlertFire)() {
  return &_EmergencyAlertFire__type_support;
}

#if defined(__cplusplus)
}
#endif
