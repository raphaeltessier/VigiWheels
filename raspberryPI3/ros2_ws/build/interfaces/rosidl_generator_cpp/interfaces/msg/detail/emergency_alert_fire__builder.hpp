// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/EmergencyAlertFire.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/emergency_alert_fire__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_EmergencyAlertFire_ir_rear_left
{
public:
  explicit Init_EmergencyAlertFire_ir_rear_left(::interfaces::msg::EmergencyAlertFire & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::EmergencyAlertFire ir_rear_left(::interfaces::msg::EmergencyAlertFire::_ir_rear_left_type arg)
  {
    msg_.ir_rear_left = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::EmergencyAlertFire msg_;
};

class Init_EmergencyAlertFire_ir_rear_right
{
public:
  explicit Init_EmergencyAlertFire_ir_rear_right(::interfaces::msg::EmergencyAlertFire & msg)
  : msg_(msg)
  {}
  Init_EmergencyAlertFire_ir_rear_left ir_rear_right(::interfaces::msg::EmergencyAlertFire::_ir_rear_right_type arg)
  {
    msg_.ir_rear_right = std::move(arg);
    return Init_EmergencyAlertFire_ir_rear_left(msg_);
  }

private:
  ::interfaces::msg::EmergencyAlertFire msg_;
};

class Init_EmergencyAlertFire_ir_front_left
{
public:
  explicit Init_EmergencyAlertFire_ir_front_left(::interfaces::msg::EmergencyAlertFire & msg)
  : msg_(msg)
  {}
  Init_EmergencyAlertFire_ir_rear_right ir_front_left(::interfaces::msg::EmergencyAlertFire::_ir_front_left_type arg)
  {
    msg_.ir_front_left = std::move(arg);
    return Init_EmergencyAlertFire_ir_rear_right(msg_);
  }

private:
  ::interfaces::msg::EmergencyAlertFire msg_;
};

class Init_EmergencyAlertFire_ir_front_right
{
public:
  explicit Init_EmergencyAlertFire_ir_front_right(::interfaces::msg::EmergencyAlertFire & msg)
  : msg_(msg)
  {}
  Init_EmergencyAlertFire_ir_front_left ir_front_right(::interfaces::msg::EmergencyAlertFire::_ir_front_right_type arg)
  {
    msg_.ir_front_right = std::move(arg);
    return Init_EmergencyAlertFire_ir_front_left(msg_);
  }

private:
  ::interfaces::msg::EmergencyAlertFire msg_;
};

class Init_EmergencyAlertFire_fire_detected
{
public:
  Init_EmergencyAlertFire_fire_detected()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EmergencyAlertFire_ir_front_right fire_detected(::interfaces::msg::EmergencyAlertFire::_fire_detected_type arg)
  {
    msg_.fire_detected = std::move(arg);
    return Init_EmergencyAlertFire_ir_front_right(msg_);
  }

private:
  ::interfaces::msg::EmergencyAlertFire msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::EmergencyAlertFire>()
{
  return interfaces::msg::builder::Init_EmergencyAlertFire_fire_detected();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__BUILDER_HPP_
