// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/FireSensor.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__FIRE_SENSOR__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__FIRE_SENSOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/fire_sensor__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_FireSensor_smoke_sensor2
{
public:
  explicit Init_FireSensor_smoke_sensor2(::interfaces::msg::FireSensor & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::FireSensor smoke_sensor2(::interfaces::msg::FireSensor::_smoke_sensor2_type arg)
  {
    msg_.smoke_sensor2 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::FireSensor msg_;
};

class Init_FireSensor_smoke_sensor1
{
public:
  explicit Init_FireSensor_smoke_sensor1(::interfaces::msg::FireSensor & msg)
  : msg_(msg)
  {}
  Init_FireSensor_smoke_sensor2 smoke_sensor1(::interfaces::msg::FireSensor::_smoke_sensor1_type arg)
  {
    msg_.smoke_sensor1 = std::move(arg);
    return Init_FireSensor_smoke_sensor2(msg_);
  }

private:
  ::interfaces::msg::FireSensor msg_;
};

class Init_FireSensor_ir_sensor4
{
public:
  explicit Init_FireSensor_ir_sensor4(::interfaces::msg::FireSensor & msg)
  : msg_(msg)
  {}
  Init_FireSensor_smoke_sensor1 ir_sensor4(::interfaces::msg::FireSensor::_ir_sensor4_type arg)
  {
    msg_.ir_sensor4 = std::move(arg);
    return Init_FireSensor_smoke_sensor1(msg_);
  }

private:
  ::interfaces::msg::FireSensor msg_;
};

class Init_FireSensor_ir_sensor3
{
public:
  explicit Init_FireSensor_ir_sensor3(::interfaces::msg::FireSensor & msg)
  : msg_(msg)
  {}
  Init_FireSensor_ir_sensor4 ir_sensor3(::interfaces::msg::FireSensor::_ir_sensor3_type arg)
  {
    msg_.ir_sensor3 = std::move(arg);
    return Init_FireSensor_ir_sensor4(msg_);
  }

private:
  ::interfaces::msg::FireSensor msg_;
};

class Init_FireSensor_ir_sensor2
{
public:
  explicit Init_FireSensor_ir_sensor2(::interfaces::msg::FireSensor & msg)
  : msg_(msg)
  {}
  Init_FireSensor_ir_sensor3 ir_sensor2(::interfaces::msg::FireSensor::_ir_sensor2_type arg)
  {
    msg_.ir_sensor2 = std::move(arg);
    return Init_FireSensor_ir_sensor3(msg_);
  }

private:
  ::interfaces::msg::FireSensor msg_;
};

class Init_FireSensor_ir_sensor1
{
public:
  Init_FireSensor_ir_sensor1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FireSensor_ir_sensor2 ir_sensor1(::interfaces::msg::FireSensor::_ir_sensor1_type arg)
  {
    msg_.ir_sensor1 = std::move(arg);
    return Init_FireSensor_ir_sensor2(msg_);
  }

private:
  ::interfaces::msg::FireSensor msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::FireSensor>()
{
  return interfaces::msg::builder::Init_FireSensor_ir_sensor1();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__FIRE_SENSOR__BUILDER_HPP_
