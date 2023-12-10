#!/usr/bin/env python3
import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from ultralytics import YOLO
from std_msgs.msg import Float32MultiArray



# This node detects manometers in real-time and publishes the
# coordinates (top left corner and bottom-right corner of the bounding box) in /manometer_detected topic
# To test it you need to launch the usb_cam node first and then this one

class YOLOInferenceNode(Node):
    def __init__(self):
        super().__init__('yolo_inference')
        self.get_logger().info("mano inference launched")
        self.model = YOLO('/home/moad/Downloads/best.pt')
        self.bridge = CvBridge()
        self.subscription = self.create_subscription(Image, 'image_raw', self.image_callback, 10)
        self.manometer_pub = self.create_publisher(Float32MultiArray, 'manometer_detected', 10)



    def image_callback(self, msg):
        # analyzing frame by frame
        frame = self.bridge.imgmsg_to_cv2(msg, 'bgr8')
        results = self.model(frame, imgsz=(640,640),conf=0.5)
        annotated_frame = results[0].plot()
        cv2.imshow("YOLOv8 Inference", annotated_frame)
        cv2.waitKey(1)
        
        
      

        manometer_detected_msg = Float32MultiArray() 
        #Publish wheter a manometer is detected or not
        for result in results:
            boxes = result.boxes.cpu().numpy()
            xyxy = boxes.xyxy
            
        if len(xyxy) != 0 :
         xyxy_list = xyxy.tolist()
         xyxy_1d_list = [i for k in xyxy_list for i in k]
         manometer_detected_msg.data = xyxy_1d_list
         self.manometer_pub.publish(manometer_detected_msg)

def main(args=None):
    rclpy.init(args=args)
    yolo_inference_node = YOLOInferenceNode()
    rclpy.spin(yolo_inference_node)
    yolo_inference_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()