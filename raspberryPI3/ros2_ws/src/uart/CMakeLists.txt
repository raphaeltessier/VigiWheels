cmake_minimum_required(VERSION 3.8)
project(uart)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(interfaces REQUIRED) 

add_executable(serial_reading_node src/serial_reading.cpp)
ament_target_dependencies(serial_reading_node rclcpp interfaces)

add_executable(serial_writing_node src/serial_writing.cpp)
ament_target_dependencies(serial_writing_node rclcpp interfaces)


install(TARGETS
  serial_reading_node
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  serial_writing_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
