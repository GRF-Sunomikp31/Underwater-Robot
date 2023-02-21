import sensor, image, time,pyb
import math
from pyb import UART
import json

point_threshold   = (37, 58, -15, 13, -20, 19)
tube_threshold   =(63, 96, -49, 9, -2, 17)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(n=800)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

uart = UART(3, 115200)
clock = time.clock()
while(True):
    clock.tick()
    img = sensor.snapshot()
    blobs = img.find_blobs([tube_threshold], pixels_threshold=2000)
    try_data=[]
    try_data.append(5)
    if blobs:
        for b in blobs:
            img.draw_rectangle(b[0:4])
            if b[5]>80:
                try_data.append(2)
            if b[5]<80:
                try_data.append(1)

    print(try_data)
            #data_json = json.dumps(try_data)
    uart.write(json.dumps(try_data))
    #prin·
