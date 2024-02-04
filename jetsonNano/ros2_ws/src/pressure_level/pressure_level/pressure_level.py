#!/usr/bin/env python3
import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import math
from interfaces.msg import PressureLevel
import time
import websockets.client
import asyncio
import math

def img_to_bytes(img) :
    _, bts = cv2.imencode('.jpg', img)
    bts = bts.tobytes()
    return bts


class PressureLevelNode(Node):
    def __init__(self):
        super().__init__('pressure_level')
        self.get_logger().info("pressure_level launched")
        self.subscription = self.create_subscription(Image, 'image_raw', self.image_callback,>
        self.manometer_level_pub = self.create_publisher(PressureLevel, 'pressure_level', 10)
        self.cv_image = []
        self.timer = self.create_timer(1, self.img_ai) #1 second
        self.new_image = False
        self.rectangle = []
        self.image_processed = False
        self.websocket_init = False

#here we define how to update the angle value of the tracking
    async def send_message(self):
        uri = "ws://localhost:9091"  # WebSocket server URI
        if self.new_image :
            self.image_processed = False
            bts = img_to_bytes(self.cv_image)

            async with websockets.client.connect(uri) as websocket:
                await websocket.send(bts)

                # Wait for a response from the server
                response = await websocket.recv()
                self.get_logger().info("resp : {} {} {}".format(response, type(response), res>
                self.rectangle = list(response)
                # Removing brackets and splitting by comma
                numbers_str = response.strip("[]").split(",")

                # Converting each substring to an integer
                self.rectangle = [(num.strip()) for num in numbers_str]
                self.get_logger().info("rect : {}".format(self.rectangle))
                  self.image_processed = True

    def image_callback(self,msg):
        bridge = CvBridge()
        self.cv_image = bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")

    def img_ai(self):
        if len(self.cv_image) != 0 :
            self.new_image = True
            asyncio.run(self.send_message())
            pressure_level_msg = PressureLevel()
            while not self.image_processed :
                time.sleep(0.0001)
            if len(self.rectangle) == 1:
                [pl] = self.rectangle
            #if self.rectangle != [0,0,0,0]: 
                height, width = self.cv_image.shape[:2]
                pressure_level_msg.level = pl
                self.manometer_level_pub.publish(pressure_level_msg)
        #frame = self.bridge.imgmsg_to_cv2(msg, 'bgr8')
        #results = self.model(frame, imgsz=(640,640),conf=0.8)
        #annotated_frame = results[0].plot()
        #cv2.imshow("YOLOv8 Inference", annotated_frame)
        #cv2.waitKey(1)

        #Publish wheter a manometer is detected or not

         # analyzing frame by frame

def main(args=None):
    rclpy.init(args=args)
    pressure_level_node = PressureLevelNode()
    rclpy.spin(pressure_level_node)
    pressure_level_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()




