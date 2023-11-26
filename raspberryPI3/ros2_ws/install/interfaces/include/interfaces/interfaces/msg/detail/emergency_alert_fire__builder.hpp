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

class Init_EmergencyAlertFire_fire_detected
{
public:
  Init_EmergencyAlertFire_fire_detected()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::msg::EmergencyAlertFire fire_detected(::interfaces::msg::EmergencyAlertFire::_fire_detected_type arg)
  {
    msg_.fire_detected = std::move(arg);
    return std::move(msg_);
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
