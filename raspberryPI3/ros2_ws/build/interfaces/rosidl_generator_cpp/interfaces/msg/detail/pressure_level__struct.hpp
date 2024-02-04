// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/PressureLevel.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__PressureLevel __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__PressureLevel __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PressureLevel_
{
  using Type = PressureLevel_<ContainerAllocator>;

  explicit PressureLevel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->level = "";
    }
  }

  explicit PressureLevel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : level(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->level = "";
    }
  }

  // field types and members
  using _level_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _level_type level;

  // setters for named parameter idiom
  Type & set__level(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->level = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::PressureLevel_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::PressureLevel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::PressureLevel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::PressureLevel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::PressureLevel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::PressureLevel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::PressureLevel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::PressureLevel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::PressureLevel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::PressureLevel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__PressureLevel
    std::shared_ptr<interfaces::msg::PressureLevel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__PressureLevel
    std::shared_ptr<interfaces::msg::PressureLevel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PressureLevel_ & other) const
  {
    if (this->level != other.level) {
      return false;
    }
    return true;
  }
  bool operator!=(const PressureLevel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PressureLevel_

// alias to use template instance with default allocator
using PressureLevel =
  interfaces::msg::PressureLevel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__PRESSURE_LEVEL__STRUCT_HPP_
