// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from interfaces:msg/FireSensor.idl
// generated code does not contain a copyright notice
#include "interfaces/msg/detail/fire_sensor__rosidl_typesupport_fastrtps_cpp.hpp"
#include "interfaces/msg/detail/fire_sensor__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_interfaces
cdr_serialize(
  const interfaces::msg::FireSensor & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: ir_sensor1
  cdr << ros_message.ir_sensor1;
  // Member: ir_sensor2
  cdr << (ros_message.ir_sensor2 ? true : false);
  // Member: ir_sensor3
  cdr << ros_message.ir_sensor3;
  // Member: ir_sensor4
  cdr << (ros_message.ir_sensor4 ? true : false);
  // Member: smoke_sensor1
  cdr << ros_message.smoke_sensor1;
  // Member: smoke_sensor2
  cdr << ros_message.smoke_sensor2;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  interfaces::msg::FireSensor & ros_message)
{
  // Member: ir_sensor1
  cdr >> ros_message.ir_sensor1;

  // Member: ir_sensor2
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ir_sensor2 = tmp ? true : false;
  }

  // Member: ir_sensor3
  cdr >> ros_message.ir_sensor3;

  // Member: ir_sensor4
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ir_sensor4 = tmp ? true : false;
  }

  // Member: smoke_sensor1
  cdr >> ros_message.smoke_sensor1;

  // Member: smoke_sensor2
  cdr >> ros_message.smoke_sensor2;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_interfaces
get_serialized_size(
  const interfaces::msg::FireSensor & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: ir_sensor1
  {
    size_t item_size = sizeof(ros_message.ir_sensor1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ir_sensor2
  {
    size_t item_size = sizeof(ros_message.ir_sensor2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ir_sensor3
  {
    size_t item_size = sizeof(ros_message.ir_sensor3);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ir_sensor4
  {
    size_t item_size = sizeof(ros_message.ir_sensor4);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: smoke_sensor1
  {
    size_t item_size = sizeof(ros_message.smoke_sensor1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: smoke_sensor2
  {
    size_t item_size = sizeof(ros_message.smoke_sensor2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_interfaces
max_serialized_size_FireSensor(
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


  // Member: ir_sensor1
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: ir_sensor2
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ir_sensor3
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: ir_sensor4
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: smoke_sensor1
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: smoke_sensor2
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  return current_alignment - initial_alignment;
}

static bool _FireSensor__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const interfaces::msg::FireSensor *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _FireSensor__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<interfaces::msg::FireSensor *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _FireSensor__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const interfaces::msg::FireSensor *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _FireSensor__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_FireSensor(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _FireSensor__callbacks = {
  "interfaces::msg",
  "FireSensor",
  _FireSensor__cdr_serialize,
  _FireSensor__cdr_deserialize,
  _FireSensor__get_serialized_size,
  _FireSensor__max_serialized_size
};

static rosidl_message_type_support_t _FireSensor__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_FireSensor__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<interfaces::msg::FireSensor>()
{
  return &interfaces::msg::typesupport_fastrtps_cpp::_FireSensor__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, interfaces, msg, FireSensor)() {
  return &interfaces::msg::typesupport_fastrtps_cpp::_FireSensor__handle;
}

#ifdef __cplusplus
}
#endif
