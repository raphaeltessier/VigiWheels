// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/ObstaclesOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/obstacles_order__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_ObstaclesOrder_rear_object
{
public:
  explicit Init_ObstaclesOrder_rear_object(::interfaces::msg::ObstaclesOrder & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::ObstaclesOrder rear_object(::interfaces::msg::ObstaclesOrder::_rear_object_type arg)
  {
    msg_.rear_object = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::ObstaclesOrder msg_;
};

class Init_ObstaclesOrder_front_object
{
public:
  Init_ObstaclesOrder_front_object()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObstaclesOrder_rear_object front_object(::interfaces::msg::ObstaclesOrder::_front_object_type arg)
  {
    msg_.front_object = std::move(arg);
    return Init_ObstaclesOrder_rear_object(msg_);
  }

private:
  ::interfaces::msg::ObstaclesOrder msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::ObstaclesOrder>()
{
  return interfaces::msg::builder::Init_ObstaclesOrder_front_object();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__OBSTACLES_ORDER__BUILDER_HPP_
