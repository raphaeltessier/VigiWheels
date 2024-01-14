import cv2
import numpy as np
from ultralytics import YOLO
import asyncio
import websockets
import math
import json
model = YOLO("bestCUDA.pt") #Change to .pt custom

def img_to_bytes(img) : 
        _, bts = cv2.imencode('.jpg', img)
        bts = bts.tobytes()
        return bts

def bytes_to_img(data) : 
        buff = np.fromstring(data, np.uint8)
        buff = buff.reshape(1, -1)
        img = cv2.imdecode(buff, cv2.IMREAD_COLOR)
        return img

def detect_manometer(frame):
        results = model(frame,imgsz=(1280,720), device='0',conf=0.4)
        result = results[0]
        high_conf = 0
        max_conf=0
        max_rect = []
        verbose="NonDetected"
        #check all the result 
        for box in result.boxes:
                class_id = result.names[box.cls[0].item()]
                cords = box.xyxy[0].tolist()
                cords = [round_up(x) for x in cords]
                [x1,y1,x2,y2] = cords
                conf = round_up(float(box.conf[0]))
                #if conf > 0.5 : 
                        #cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                        #cv2.putText(frame, "{} : {}".format(class_id, conf), (x1, y1 - 10), cv2.FON>
                if conf > high_conf: 
                        high_conf = conf
                        max_rect = [x1,y1,x2,y2]
                verbose="AtleastOneDetection" 
        #cv2.rectangle(frame, (max_rect[0], max_rect[1]), (max_rect[2], max_rect[3]), (0, 0, 255), 2)
        return (verbose, max_rect, high_conf, frame)

def round_up(value, decimal_places=2):
        return math.ceil(value*10**decimal_places)/10**decimal_places

async def handle_websocket(websocket, path):
        # This function will be called whenever a new WebSocket connection is established
        print(f"Client connected to {path}")
        try:
                while True:
                        data = await websocket.recv()
                        img = bytes_to_img(data)
                        (ver, rect, conf, imageproc) = detect_manometer(img)
                        #message=rect
                        #message.append(conf)
                        print(ver)
                        await websocket.send(str(rect))
                        #cv2.imwrite("new_img.jpg", imageproc)
        except websockets.exceptions.ConnectionClosed:
                print(f"Client disconnected from {path}")

# Set up the WebSocket server
#start_server = websockets.serve(handle_websocket, "localhost", 9090)

start_server = websockets.serve(handle_websocket, "localhost", 9090,ping_timeout=None)

# Start the event loop
async def main():
    await start_server
    print("WebSocket server listening on port 9090...")
    await asyncio.Future()  # run forever

if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    try:
        loop.run_until_complete(main())
    finally:
        loop.run_until_complete(loop.shutdown_asyncgens())
        loop.close()

