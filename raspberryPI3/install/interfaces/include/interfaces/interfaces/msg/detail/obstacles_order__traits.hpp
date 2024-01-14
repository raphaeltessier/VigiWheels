// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interfaces:msg/ObstaclesOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__TRAITS_HPP_
#define INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interfaces/msg/detail/obstacles_order__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ObstaclesOrder & msg,
  std::ostream & out)
{
  out << "{";
  // member: front_object
  {
    out << "front_object: ";
    rosidl_generator_traits::value_to_yaml(msg.front_object, out);
    out << ", ";
  }

  // member: rear_object
  {
    out << "rear_object: ";
    rosidl_generator_traits::value_to_yaml(msg.rear_object, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ObstaclesOrder & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: front_object
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "front_object: ";
    rosidl_generator_traits::value_to_yaml(msg.front_object, out);
    out << "\n";
  }

  // member: rear_object
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rear_object: ";
    rosidl_generator_traits::value_to_yaml(msg.rear_object, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ObstaclesOrder & msg, bool use_flow_style = false)
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
  const interfaces::msg::ObstaclesOrder & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::msg::ObstaclesOrder & msg)
{
  return interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::msg::ObstaclesOrder>()
{
  return "interfaces::msg::ObstaclesOrder";
}

template<>
inline const char * name<interfaces::msg::ObstaclesOrder>()
{
  return "interfaces/msg/ObstaclesOrder";
}

template<>
struct has_fixed_size<interfaces::msg::ObstaclesOrder>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<interfaces::msg::ObstaclesOrder>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<interfaces::msg::ObstaclesOrder>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__TRAITS_HPP_
