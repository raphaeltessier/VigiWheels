// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/ServoCamOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/servo_cam_order__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_ServoCamOrder_servo_cam_angle
{
public:
  Init_ServoCamOrder_servo_cam_angle()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::msg::ServoCamOrder servo_cam_angle(::interfaces::msg::ServoCamOrder::_servo_cam_angle_type arg)
  {
    msg_.servo_cam_angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::ServoCamOrder msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::ServoCamOrder>()
{
  return interfaces::msg::builder::Init_ServoCamOrder_servo_cam_angle();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__BUILDER_HPP_
