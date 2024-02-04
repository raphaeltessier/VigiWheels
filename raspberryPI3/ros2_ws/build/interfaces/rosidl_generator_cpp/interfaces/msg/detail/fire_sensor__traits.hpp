// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interfaces:msg/FireSensor.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__FIRE_SENSOR__TRAITS_HPP_
#define INTERFACES__MSG__DETAIL__FIRE_SENSOR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interfaces/msg/detail/fire_sensor__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const FireSensor & msg,
  std::ostream & out)
{
  out << "{";
  // member: ir_sensor1
  {
    out << "ir_sensor1: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_sensor1, out);
    out << ", ";
  }

  // member: ir_sensor2
  {
    out << "ir_sensor2: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_sensor2, out);
    out << ", ";
  }

  // member: ir_sensor3
  {
    out << "ir_sensor3: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_sensor3, out);
    out << ", ";
  }

  // member: ir_sensor4
  {
    out << "ir_sensor4: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_sensor4, out);
    out << ", ";
  }

  // member: smoke_sensor1
  {
    out << "smoke_sensor1: ";
    rosidl_generator_traits::value_to_yaml(msg.smoke_sensor1, out);
    out << ", ";
  }

  // member: smoke_sensor2
  {
    out << "smoke_sensor2: ";
    rosidl_generator_traits::value_to_yaml(msg.smoke_sensor2, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FireSensor & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: ir_sensor1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ir_sensor1: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_sensor1, out);
    out << "\n";
  }

  // member: ir_sensor2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ir_sensor2: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_sensor2, out);
    out << "\n";
  }

  // member: ir_sensor3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ir_sensor3: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_sensor3, out);
    out << "\n";
  }

  // member: ir_sensor4
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ir_sensor4: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_sensor4, out);
    out << "\n";
  }

  // member: smoke_sensor1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "smoke_sensor1: ";
    rosidl_generator_traits::value_to_yaml(msg.smoke_sensor1, out);
    out << "\n";
  }

  // member: smoke_sensor2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "smoke_sensor2: ";
    rosidl_generator_traits::value_to_yaml(msg.smoke_sensor2, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FireSensor & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace interfaces

namespace rosidl_generator_traits
{

[[deprecated("use interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const interfaces::msg::FireSensor & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::msg::FireSensor & msg)
{
  return interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::msg::FireSensor>()
{
  return "interfaces::msg::FireSensor";
}

template<>
inline const char * name<interfaces::msg::FireSensor>()
{
  return "interfaces/msg/FireSensor";
}

template<>
struct has_fixed_size<interfaces::msg::FireSensor>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<interfaces::msg::FireSensor>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<interfaces::msg::FireSensor>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INTERFACES__MSG__DETAIL__FIRE_SENSOR__TRAITS_HPP_
