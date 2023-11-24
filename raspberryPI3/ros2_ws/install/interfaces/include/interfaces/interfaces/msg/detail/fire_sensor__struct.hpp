// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/FireSensor.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__FIRE_SENSOR__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__FIRE_SENSOR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__FireSensor __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__FireSensor __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FireSensor_
{
  using Type = FireSensor_<ContainerAllocator>;

  explicit FireSensor_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ir_sensor_1 = 0;
      this->ir_sensor_2 = 0;
    }
  }

  explicit FireSensor_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ir_sensor_1 = 0;
      this->ir_sensor_2 = 0;
    }
  }

  // field types and members
  using _ir_sensor_1_type =
    int16_t;
  _ir_sensor_1_type ir_sensor_1;
  using _ir_sensor_2_type =
    int16_t;
  _ir_sensor_2_type ir_sensor_2;

  // setters for named parameter idiom
  Type & set__ir_sensor_1(
    const int16_t & _arg)
  {
    this->ir_sensor_1 = _arg;
    return *this;
  }
  Type & set__ir_sensor_2(
    const int16_t & _arg)
  {
    this->ir_sensor_2 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::FireSensor_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::FireSensor_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::FireSensor_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::FireSensor_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::FireSensor_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::FireSensor_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::FireSensor_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::FireSensor_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::FireSensor_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::FireSensor_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__FireSensor
    std::shared_ptr<interfaces::msg::FireSensor_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__FireSensor
    std::shared_ptr<interfaces::msg::FireSensor_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FireSensor_ & other) const
  {
    if (this->ir_sensor_1 != other.ir_sensor_1) {
      return false;
    }
    if (this->ir_sensor_2 != other.ir_sensor_2) {
      return false;
    }
    return true;
  }
  bool operator!=(const FireSensor_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FireSensor_

// alias to use template instance with default allocator
using FireSensor =
  interfaces::msg::FireSensor_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__FIRE_SENSOR__STRUCT_HPP_
