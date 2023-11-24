cmake_minimum_required(VERSION 3.8)
project(fire_detection)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_robot_interfaces REQUIRED) 


add_executable(serial_reading_node src/serial_reading.cpp)
ament_target_dependencies(serial_reading_node rclcpp example_interfaces my_robot_interfaces)

install(TARGETS
serial_reading_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
