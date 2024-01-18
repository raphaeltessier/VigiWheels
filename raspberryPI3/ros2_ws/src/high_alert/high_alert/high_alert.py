#!/usr/bin/env python3
import os
import rclpy
from rclpy.node import Node
from interfaces.msg import PressureLevel

def play_audio_mp3(file_path, file_name):
    os.system(f"ffplay -v 0 -nodisp -autoexit {file_path}/{file_name}")

class AlarmNode(Node):
    def __init__(self):
        super().__init__('alarm_node')
        self.get_logger().info("Alarm node launched")
        self.subscription = self.create_subscription(PressureLevel, 'pressure_level', self.pressure_callback, 10)

    def pressure_callback(self, msg):
        if msg.level == "High":
            # Use os.path.expanduser to get the full path to the home directory
            mp3_file = os.path.expanduser("~/ros2_moad/src/high_alert")
            mp3_name = "alarm.mp3"
            play_audio_mp3(mp3_file, mp3_name)

def main(args=None):
    rclpy.init(args=args)
    alarm_node = AlarmNode()
    rclpy.spin(alarm_node)
    alarm_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
