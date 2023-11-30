// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interfaces:msg/EmergencyAlertFire.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__TRAITS_HPP_
#define INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interfaces/msg/detail/emergency_alert_fire__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const EmergencyAlertFire & msg,
  std::ostream & out)
{
  out << "{";
  // member: fire_detected
  {
    out << "fire_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.fire_detected, out);
    out << ", ";
  }

  // member: ir_front_right
  {
    out << "ir_front_right: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_front_right, out);
    out << ", ";
  }

  // member: ir_front_left
  {
    out << "ir_front_left: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_front_left, out);
    out << ", ";
  }

  // member: ir_rear_right
  {
    out << "ir_rear_right: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_rear_right, out);
    out << ", ";
  }

  // member: ir_rear_left
  {
    out << "ir_rear_left: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_rear_left, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EmergencyAlertFire & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: fire_detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fire_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.fire_detected, out);
    out << "\n";
  }

  // member: ir_front_right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ir_front_right: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_front_right, out);
    out << "\n";
  }

  // member: ir_front_left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ir_front_left: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_front_left, out);
    out << "\n";
  }

  // member: ir_rear_right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ir_rear_right: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_rear_right, out);
    out << "\n";
  }

  // member: ir_rear_left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ir_rear_left: ";
    rosidl_generator_traits::value_to_yaml(msg.ir_rear_left, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EmergencyAlertFire & msg, bool use_flow_style = false)
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
  const interfaces::msg::EmergencyAlertFire & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::msg::EmergencyAlertFire & msg)
{
  return interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::msg::EmergencyAlertFire>()
{
  return "interfaces::msg::EmergencyAlertFire";
}

template<>
inline const char * name<interfaces::msg::EmergencyAlertFire>()
{
  return "interfaces/msg/EmergencyAlertFire";
}

template<>
struct has_fixed_size<interfaces::msg::EmergencyAlertFire>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<interfaces::msg::EmergencyAlertFire>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<interfaces::msg::EmergencyAlertFire>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__TRAITS_HPP_
