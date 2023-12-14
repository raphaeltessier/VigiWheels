#!/usr/bin/env python3
import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from ultralytics import YOLO
import math
from manometer_interfaces.msg import ManometerInfo


def round_up(value, decimal_places=2):
    return math.ceil(value * 10**decimal_places) / 10**decimal_places


class YOLOInferenceNode(Node):
    def __init__(self):
        super().__init__('yolo_inference')
        self.get_logger().info("mano inference launched")
        self.model = YOLO('/home/moad/Downloads/best.pt')
        self.bridge = CvBridge()
        self.subscription = self.create_subscription(Image, 'image_raw', self.image_callback, 10)
        self.manometer_pub = self.create_publisher(ManometerInfo, 'manometer_detected', 10)
        self.highest_probability = 0


    def image_callback(self, msg):
        
        frame = self.bridge.imgmsg_to_cv2(msg, 'bgr8')
        results = self.model(frame, imgsz=(640,640),conf=0.8)
        annotated_frame = results[0].plot()
        cv2.imshow("YOLOv8 Inference", annotated_frame)
        cv2.waitKey(1)
        
        #Publish wheter a manometer is detected or not

        manometer_detected_msg = ManometerInfo() # analyzing frame by frame

        for result in results:
            boxes = result.boxes.cpu().numpy()
            xyxy = boxes.xyxy
            
        if len(xyxy) != 0 :
         xyxy_list = xyxy.tolist()
         xyxy_1d_list = [i for k in xyxy_list for i in k]
         manometer_detected_msg.probability = round_up(float((boxes.conf[0])))

         if manometer_detected_msg.probability > self.highest_probability:
          self.highest_probability = manometer_detected_msg.probability
          manometer_detected_msg.x1 = xyxy_1d_list[0]
          manometer_detected_msg.y1 = xyxy_1d_list[1]
          manometer_detected_msg.x2 = xyxy_1d_list[2]
          manometer_detected_msg.y2 = xyxy_1d_list[3]
          self.manometer_pub.publish(manometer_detected_msg)

def main(args=None):
    rclpy.init(args=args)
    yolo_inference_node = YOLOInferenceNode()
    rclpy.spin(yolo_inference_node)
    yolo_inference_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()