// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/EmergencyAlertFire.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__EmergencyAlertFire __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__EmergencyAlertFire __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EmergencyAlertFire_
{
  using Type = EmergencyAlertFire_<ContainerAllocator>;

  explicit EmergencyAlertFire_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->fire_detected = false;
      this->ir_front_right = false;
      this->ir_front_left = false;
      this->ir_rear_right = false;
      this->ir_rear_left = false;
      this->smoke_left = false;
      this->smoke_right = false;
    }
  }

  explicit EmergencyAlertFire_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->fire_detected = false;
      this->ir_front_right = false;
      this->ir_front_left = false;
      this->ir_rear_right = false;
      this->ir_rear_left = false;
      this->smoke_left = false;
      this->smoke_right = false;
    }
  }

  // field types and members
  using _fire_detected_type =
    bool;
  _fire_detected_type fire_detected;
  using _ir_front_right_type =
    bool;
  _ir_front_right_type ir_front_right;
  using _ir_front_left_type =
    bool;
  _ir_front_left_type ir_front_left;
  using _ir_rear_right_type =
    bool;
  _ir_rear_right_type ir_rear_right;
  using _ir_rear_left_type =
    bool;
  _ir_rear_left_type ir_rear_left;
  using _smoke_left_type =
    bool;
  _smoke_left_type smoke_left;
  using _smoke_right_type =
    bool;
  _smoke_right_type smoke_right;

  // setters for named parameter idiom
  Type & set__fire_detected(
    const bool & _arg)
  {
    this->fire_detected = _arg;
    return *this;
  }
  Type & set__ir_front_right(
    const bool & _arg)
  {
    this->ir_front_right = _arg;
    return *this;
  }
  Type & set__ir_front_left(
    const bool & _arg)
  {
    this->ir_front_left = _arg;
    return *this;
  }
  Type & set__ir_rear_right(
    const bool & _arg)
  {
    this->ir_rear_right = _arg;
    return *this;
  }
  Type & set__ir_rear_left(
    const bool & _arg)
  {
    this->ir_rear_left = _arg;
    return *this;
  }
  Type & set__smoke_left(
    const bool & _arg)
  {
    this->smoke_left = _arg;
    return *this;
  }
  Type & set__smoke_right(
    const bool & _arg)
  {
    this->smoke_right = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::EmergencyAlertFire_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::EmergencyAlertFire_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::EmergencyAlertFire_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::EmergencyAlertFire_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::EmergencyAlertFire_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::EmergencyAlertFire_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::EmergencyAlertFire_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::EmergencyAlertFire_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::EmergencyAlertFire_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::EmergencyAlertFire_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__EmergencyAlertFire
    std::shared_ptr<interfaces::msg::EmergencyAlertFire_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__EmergencyAlertFire
    std::shared_ptr<interfaces::msg::EmergencyAlertFire_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EmergencyAlertFire_ & other) const
  {
    if (this->fire_detected != other.fire_detected) {
      return false;
    }
    if (this->ir_front_right != other.ir_front_right) {
      return false;
    }
    if (this->ir_front_left != other.ir_front_left) {
      return false;
    }
    if (this->ir_rear_right != other.ir_rear_right) {
      return false;
    }
    if (this->ir_rear_left != other.ir_rear_left) {
      return false;
    }
    if (this->smoke_left != other.smoke_left) {
      return false;
    }
    if (this->smoke_right != other.smoke_right) {
      return false;
    }
    return true;
  }
  bool operator!=(const EmergencyAlertFire_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EmergencyAlertFire_

// alias to use template instance with default allocator
using EmergencyAlertFire =
  interfaces::msg::EmergencyAlertFire_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__EMERGENCY_ALERT_FIRE__STRUCT_HPP_
