// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/CamPosOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__CAM_POS_ORDER__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__CAM_POS_ORDER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/cam_pos_order__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_CamPosOrder_turn_cam
{
public:
  explicit Init_CamPosOrder_turn_cam(::interfaces::msg::CamPosOrder & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::CamPosOrder turn_cam(::interfaces::msg::CamPosOrder::_turn_cam_type arg)
  {
    msg_.turn_cam = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::CamPosOrder msg_;
};

class Init_CamPosOrder_mode
{
public:
  Init_CamPosOrder_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CamPosOrder_turn_cam mode(::interfaces::msg::CamPosOrder::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_CamPosOrder_turn_cam(msg_);
  }

private:
  ::interfaces::msg::CamPosOrder msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::CamPosOrder>()
{
  return interfaces::msg::builder::Init_CamPosOrder_mode();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__CAM_POS_ORDER__BUILDER_HPP_
