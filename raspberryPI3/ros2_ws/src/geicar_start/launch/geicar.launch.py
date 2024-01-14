from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import AnyLaunchDescriptionSource
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    ld = LaunchDescription()

    joystick_node = Node(
        package="joystick",
        executable="joystick_ros2.py",
        emulate_tty=True
    )

    joystick_to_cmd_node = Node(
        package="joystick",
        executable="joystick_to_cmd",
        emulate_tty=True
    )

    can_rx_node = Node(
        package="can",
        executable="can_rx_node",
        emulate_tty=True
    )

    can_tx_node = Node(
        package="can",
        executable="can_tx_node",
        emulate_tty=True
    )

    car_control_node = Node(
        package="car_control",
        executable="car_control_node",
        emulate_tty=True
    )

    obstacles_node = Node(
        package="obstacles",
        executable="obstacles",
        emulate_tty=True
    )

    servo_cam_node = Node(
        package="servo_cam",
        executable="servo_cam",
        emulate_tty=True
    )

    config_dir = os.path.join(get_package_share_directory('imu_filter_madgwick'), 'config')

    imu_filter_madgwick_node = Node(
        package="imu_filter_madgwick",
        executable="imu_filter_madgwick_node",
        parameters=[os.path.join(config_dir, 'imu_filter.yaml')],
        emulate_tty=True
    )


    system_check_node = Node(
        package="system_check",
        executable="system_check_node",
        emulate_tty=True
    )
    
    serial_writing_node = Node(
        package="uart",
        executable="serial_writing_node",
        emulate_tty=True
    )

    serial_reading_node = Node(
        package="uart",
        executable="serial_reading_node",
        emulate_tty=True
    )
    
    processing_data_fire_node = Node(
        package="fire_detection",
        executable="processing_data_fire_node",
        emulate_tty=True
    )

    path_recording_node = Node(
        package="path_recording",
        executable="path_recording",
        emulate_tty=True
    )


    path_recording_node = Node(
        package="path_recording",
        executable="path_recording",
        emulate_tty=True
    )

    rosbride_server_node = IncludeLaunchDescription(
        AnyLaunchDescriptionSource([get_package_share_directory('rosbridge_server'),'/launch/rosbridge_websocket_launch.xml']),
    )

    ld.add_action(joystick_node)
    ld.add_action(joystick_to_cmd_node)
    ld.add_action(can_rx_node)
    ld.add_action(can_tx_node)
    ld.add_action(car_control_node)
    ld.add_action(obstacles_node)
    ld.add_action(imu_filter_madgwick_node)
    ld.add_action(system_check_node)
    ld.add_action(servo_cam_node)
    ld.add_action(serial_writing_node)
    ld.add_action(serial_reading_node)
    ld.add_action(processing_data_fire_node)
    ld.add_action(path_recording_node)
    ld.add_action(rosbride_server_node)


    return ld
