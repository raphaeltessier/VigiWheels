// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/PressureLevel.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/pressure_level__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_PressureLevel_level
{
public:
  Init_PressureLevel_level()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::msg::PressureLevel level(::interfaces::msg::PressureLevel::_level_type arg)
  {
    msg_.level = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::PressureLevel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::PressureLevel>()
{
  return interfaces::msg::builder::Init_PressureLevel_level();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__BUILDER_HPP_
