// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/CamPosOrder.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__CAM_POS_ORDER__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__CAM_POS_ORDER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__CamPosOrder __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__CamPosOrder __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CamPosOrder_
{
  using Type = CamPosOrder_<ContainerAllocator>;

  explicit CamPosOrder_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->mode = 0;
      this->cam_angle = 90;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->mode = 0;
      this->cam_angle = 0;
    }
  }

  explicit CamPosOrder_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->mode = 0;
      this->cam_angle = 90;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->mode = 0;
      this->cam_angle = 0;
    }
  }

  // field types and members
  using _mode_type =
    int8_t;
  _mode_type mode;
  using _cam_angle_type =
    int16_t;
  _cam_angle_type cam_angle;

  // setters for named parameter idiom
  Type & set__mode(
    const int8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__cam_angle(
    const int16_t & _arg)
  {
    this->cam_angle = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::CamPosOrder_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::CamPosOrder_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::CamPosOrder_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::CamPosOrder_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::CamPosOrder_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::CamPosOrder_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::CamPosOrder_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::CamPosOrder_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::CamPosOrder_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::CamPosOrder_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__CamPosOrder
    std::shared_ptr<interfaces::msg::CamPosOrder_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__CamPosOrder
    std::shared_ptr<interfaces::msg::CamPosOrder_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CamPosOrder_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->cam_angle != other.cam_angle) {
      return false;
    }
    return true;
  }
  bool operator!=(const CamPosOrder_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CamPosOrder_

// alias to use template instance with default allocator
using CamPosOrder =
  interfaces::msg::CamPosOrder_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__CAM_POS_ORDER__STRUCT_HPP_
