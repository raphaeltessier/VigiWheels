// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/ServoCamOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__ServoCamOrder __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__ServoCamOrder __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoCamOrder_
{
  using Type = ServoCamOrder_<ContainerAllocator>;

  explicit ServoCamOrder_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->servo_cam_angle = 90;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->servo_cam_angle = 0;
    }
  }

  explicit ServoCamOrder_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->servo_cam_angle = 90;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->servo_cam_angle = 0;
    }
  }

  // field types and members
  using _servo_cam_angle_type =
    uint8_t;
  _servo_cam_angle_type servo_cam_angle;

  // setters for named parameter idiom
  Type & set__servo_cam_angle(
    const uint8_t & _arg)
  {
    this->servo_cam_angle = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::ServoCamOrder_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::ServoCamOrder_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::ServoCamOrder_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::ServoCamOrder_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::ServoCamOrder_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::ServoCamOrder_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::ServoCamOrder_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::ServoCamOrder_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::ServoCamOrder_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::ServoCamOrder_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__ServoCamOrder
    std::shared_ptr<interfaces::msg::ServoCamOrder_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__ServoCamOrder
    std::shared_ptr<interfaces::msg::ServoCamOrder_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoCamOrder_ & other) const
  {
    if (this->servo_cam_angle != other.servo_cam_angle) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoCamOrder_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoCamOrder_

// alias to use template instance with default allocator
using ServoCamOrder =
  interfaces::msg::ServoCamOrder_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__SERVO_CAM_ORDER__STRUCT_HPP_
