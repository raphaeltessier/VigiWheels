import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from ultralytics import YOLO
import math
from interfaces.msg import PressureLevel


class PressureLevelNode(Node):
    def __init__(self):
        super().__init__('pressure_level')
        self.get_logger().info("pressure level launched")
        self.model = YOLO('/home/moad/Downloads/Level.pt')
        self.bridge = CvBridge()
        self.subscription = self.create_subscription(Image,'image_raw', self.image_callback, 10)
        self.manometer_level_pub = self.create_publisher(PressureLevel, 'pressure_level', 10)


    def image_callback(self, msg):

        frame =  self.bridge.imgmsg_to_cv2(msg,'bgr8')
        results = self.model(frame, imgsz=(640,640),conf=0.6)
        annotated_frame = results[0].plot()
        cv2.imshow("Manometer Level Inference", annotated_frame)
        cv2.waitKey(1) 

        #Publish the Pressure Level

        pressure_level_msg = PressureLevel() # analyzing frame by frame
        for result in results:
         boxes = result.boxes.cpu().numpy()
         class_id = boxes.cls
         if len(class_id) != 0 : 
            class_id = class_id.tolist()
            pressure_level_msg.level = result.names[class_id[0]]
            self.manometer_level_pub.publish(pressure_level_msg)

def main(args=None):
    rclpy.init(args=args)
    pressure_level_node = PressureLevelNode()
    rclpy.spin(pressure_level_node)
    pressure_level_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()