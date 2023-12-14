// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/ManometerInfo.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__MANOMETER_INFO__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__MANOMETER_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/manometer_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_ManometerInfo_probability
{
public:
  explicit Init_ManometerInfo_probability(::interfaces::msg::ManometerInfo & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::ManometerInfo probability(::interfaces::msg::ManometerInfo::_probability_type arg)
  {
    msg_.probability = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::ManometerInfo msg_;
};

class Init_ManometerInfo_y2
{
public:
  explicit Init_ManometerInfo_y2(::interfaces::msg::ManometerInfo & msg)
  : msg_(msg)
  {}
  Init_ManometerInfo_probability y2(::interfaces::msg::ManometerInfo::_y2_type arg)
  {
    msg_.y2 = std::move(arg);
    return Init_ManometerInfo_probability(msg_);
  }

private:
  ::interfaces::msg::ManometerInfo msg_;
};

class Init_ManometerInfo_x2
{
public:
  explicit Init_ManometerInfo_x2(::interfaces::msg::ManometerInfo & msg)
  : msg_(msg)
  {}
  Init_ManometerInfo_y2 x2(::interfaces::msg::ManometerInfo::_x2_type arg)
  {
    msg_.x2 = std::move(arg);
    return Init_ManometerInfo_y2(msg_);
  }

private:
  ::interfaces::msg::ManometerInfo msg_;
};

class Init_ManometerInfo_y1
{
public:
  explicit Init_ManometerInfo_y1(::interfaces::msg::ManometerInfo & msg)
  : msg_(msg)
  {}
  Init_ManometerInfo_x2 y1(::interfaces::msg::ManometerInfo::_y1_type arg)
  {
    msg_.y1 = std::move(arg);
    return Init_ManometerInfo_x2(msg_);
  }

private:
  ::interfaces::msg::ManometerInfo msg_;
};

class Init_ManometerInfo_x1
{
public:
  Init_ManometerInfo_x1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManometerInfo_y1 x1(::interfaces::msg::ManometerInfo::_x1_type arg)
  {
    msg_.x1 = std::move(arg);
    return Init_ManometerInfo_y1(msg_);
  }

private:
  ::interfaces::msg::ManometerInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::ManometerInfo>()
{
  return interfaces::msg::builder::Init_ManometerInfo_x1();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__MANOMETER_INFO__BUILDER_HPP_
