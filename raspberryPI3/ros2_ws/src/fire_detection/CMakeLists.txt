cmake_minimum_required(VERSION 3.8)
project(fire_detection)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(interfaces REQUIRED) 

add_executable(processing_data_fire_node src/processing_data_fire.cpp)
ament_target_dependencies(processing_data_fire_node rclcpp interfaces)

install(TARGETS
  processing_data_fire_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
